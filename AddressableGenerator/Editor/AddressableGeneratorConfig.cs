using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

namespace AddressableGenerator{
    public class AddressableGeneratorConfig : ScriptableObject
    {
        [Header("[根目录]:\n只会遍历到二级目录\n1级子目录, 使用 PackSeparately \n2级子目录, 使用 PackTogether\n")]
        public DefaultAsset RootPath;
        [Header("[强制使用 PackTogether 模式]")]
        public List<DefaultAsset> ForcePackTogetherPaths;
        [Header("[强制使用 PackSeparately 模式]")]
        public List<DefaultAsset> ForcePackSeparatelyPaths;
        [Header("[过滤的路径]")]
        public List<DefaultAsset> FilterPaths;


        [MenuItem("AddressableGenerator/Create config")]
        public static void CreateConfig()
        {
            var path = GetConfigPath();
            if(File.Exists(path)){
                Debug.LogError("已经存在");
                return;
            }
            Debug.LogError(path);

            //创建数据资源文件
            AddressableGeneratorConfig asset = ScriptableObject.CreateInstance<AddressableGeneratorConfig>();
            AssetDatabase.CreateAsset(asset, path);
            //保存创建的资源
            AssetDatabase.SaveAssets();
            //刷新界面
            AssetDatabase.Refresh();
        }

        public static AddressableGeneratorConfig GetConfig(){
            var config = AssetDatabase.LoadAssetAtPath(GetConfigPath(), typeof(AddressableGeneratorConfig)) as AddressableGeneratorConfig;
            return config;
        }

        private static string GetConfigPath(){
            var dir  = AddressableGeneratorUtils.GetScriptableObjectDir(new AddressableGeneratorConfig());
            var path = $"{dir}/AddressableGeneratorConfig.asset";
            Debug.Log($"ConfigPath: {path}");
            return path;
        }
    }
}


