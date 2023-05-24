using System.IO;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEditor.AddressableAssets.Settings;
using UnityEditor.AddressableAssets;
using UnityEditor.AddressableAssets.Settings.GroupSchemas;
using static UnityEditor.AddressableAssets.Settings.GroupSchemas.BundledAssetGroupSchema;

namespace AddressableGenerator{
    public class AddressableGenerator : Editor
    {
 
        [MenuItem("AddressableGenerator/Generate")]
        private static void generate()
        {
            var config = AddressableGeneratorConfig.GetConfig();
            if(config == null){
                Debug.LogError("No Find AddressableGeneratorConfig.asset");
                return;
            }
            var rootPath = AddressableGeneratorUtils.GetAssetPathDir(config.RootPath);
            var forcePackTogetherGroups = AddressableGeneratorUtils.GetAssetDirNames(config.ForcePackTogetherPaths);
            var forcePackSeparatelyGroups = AddressableGeneratorUtils.GetAssetDirNames(config.ForcePackSeparatelyPaths);
            var filterPaths = AddressableGeneratorUtils.GetAssetDirNames(config.FilterPaths);

            var paths = getPathAndGroups(rootPath);
            var usePathCount = 0;
            foreach (var item in paths)
            {
                var path = item.Key;
                var isContinue = false;
                foreach (var name in filterPaths)
                {
                    if(path.EndsWith(name)){
                        isContinue = true;
                        break;
                    }
                }
                if(isContinue)
                    continue;

                usePathCount++;
                var mode = item.Value.Value;
                foreach (var name in forcePackTogetherGroups)
                {
                    if(path.EndsWith(name))
                        mode = BundlePackingMode.PackTogether;
                }

                foreach (var name in forcePackSeparatelyGroups)
                {
                    if(path.EndsWith(name))
                        mode = BundlePackingMode.PackSeparately;
                }
                
                addAddressables(path, item.Value.Key, mode);
            }
            Debug.LogError($"AddressableGenerator Generate 设置完成: {usePathCount}");
        }

        [MenuItem("AddressableGenerator/Remove")]
        private static void remove()
        {
            var config = AddressableGeneratorConfig.GetConfig();
            if(config == null){
                Debug.LogError("No Find AddressableGeneratorConfig.asset");
                return;
            }
            var rootPath = AddressableGeneratorUtils.GetAssetPathDir(config.RootPath);
            var paths = getPathAndGroups(rootPath);
            foreach (var item in paths)
            {
                removeGroup(item.Value.Key);
            }
            Debug.LogError($"AddressableGenerator Generate 移除完成: {paths.Count}");
        }

        private static Dictionary<string, KeyValuePair<string, BundlePackingMode>> getPathAndGroups(string rootPath){
            var rs = new Dictionary<string, KeyValuePair<string, BundlePackingMode>>();
            var subDirsList = AddressableGeneratorUtils.GetPathSubDirs(rootPath);
            for (int i = 0; i < subDirsList.Count; i++)
            {
                var path = subDirsList[i];
                var groupName = Path.GetFileNameWithoutExtension(path);
                var childList = AddressableGeneratorUtils.GetPathSubDirs(path);
                if(childList.Count > 0){
                    foreach (var childPath in childList)
                    {
                        var childGroupName = Path.GetFileNameWithoutExtension(childPath);
                        childGroupName = $"{groupName}_{childGroupName}";
                        rs.Add(childPath, new KeyValuePair<string, BundlePackingMode>(childGroupName , BundlePackingMode.PackTogether));
                    }
                }else{
                    rs.Add(path, new KeyValuePair<string, BundlePackingMode>(groupName , BundlePackingMode.PackSeparately));
                }
            }
            return rs;
        }

        private static void removeGroup(string groupName)
        {
            AddressableAssetGroup group = AddressableAssetSettingsDefaultObject.Settings.FindGroup(groupName);
            if(group != null){
                AddressableAssetSettingsDefaultObject.Settings.RemoveGroup(group);
            }
        }

        private static string getColorString(object str, string color = "yellow"){
            return $"<color={color}>{str}</color> ";
        }

        private static void addAddressables(string assetPath, string groupName, BundlePackingMode mode)
        {
            Debug.Log($"add groupName: {getColorString(groupName)} mode: {getColorString(mode)} assetPath: {assetPath}");
            AddressableAssetGroup group = AddressableAssetSettingsDefaultObject.Settings.FindGroup(groupName);
            if(group == null){
                group = AddressableAssetSettingsDefaultObject.Settings.CreateGroup(groupName, false, false, true, new List<AddressableAssetGroupSchema> { 
                    AddressableAssetSettingsDefaultObject.Settings.DefaultGroup.Schemas[0], 
                    AddressableAssetSettingsDefaultObject.Settings.DefaultGroup.Schemas[1] });
            
                var groupSchema = group.GetSchema<BundledAssetGroupSchema>();
                groupSchema.BundleMode = mode;
                groupSchema.RetryCount = 3;
                
                /* 微信小游戏设置
                https://github.com/wechat-miniprogram/minigame-unity-webgl-transform/blob/main/Design/OptimizationMemory.md
                避免使用Unity自带的文件缓存机制， 首资源包和AssetBundle都不应使用文件Cache；

                groupSchema.UseAssetBundleCache = false;
                groupSchema.UseAssetBundleCrc = false;
                groupSchema.UseAssetBundleCrcForCachedBundles = false;
                //*/
                
                groupSchema.UseAssetBundleCache = true;
                groupSchema.UseAssetBundleCrc = true;
                groupSchema.UseAssetBundleCrcForCachedBundles = true;

                groupSchema.IncludeGUIDInCatalog = false; //如果为 false 不能使用 AssetReference 加载
                groupSchema.IncludeLabelsInCatalog = false;

                groupSchema.BuildPath.SetVariableByName(AddressableAssetSettingsDefaultObject.Settings, "LocalBuildPath");
                groupSchema.LoadPath.SetVariableByName(AddressableAssetSettingsDefaultObject.Settings, "LocalLoadPath");

                AssetDatabase.SaveAssetIfDirty(groupSchema);
            }else{
                var groupSchema = group.GetSchema<BundledAssetGroupSchema>();
                groupSchema.BundleMode = mode;
                
                AssetDatabase.SaveAssetIfDirty(groupSchema);
            }
            
            var files = new List<string>();
            AddressableGeneratorUtils.GetPathFiles(assetPath, "", ".meta", ref files);
            for (var i = 0; i < files.Count; i++)
            {
                var p = files[i];
                p = p.Replace("\\", "/");
                p = p.Substring(p.IndexOf("Assets/"));
                string guid = AssetDatabase.AssetPathToGUID(p);
                var entry = group.GetAssetEntry(guid);
                if(entry == null){
                    entry = AddressableAssetSettingsDefaultObject.Settings.CreateOrMoveEntry(guid, group);
                }
                entry.SetAddress(p);
            }

            AssetDatabase.SaveAssetIfDirty(group);
        }
    }
}

