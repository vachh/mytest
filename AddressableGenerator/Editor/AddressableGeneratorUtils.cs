using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

namespace AddressableGenerator{
    public static class AddressableGeneratorUtils
    {
        public static string GetScriptableObjectDir(ScriptableObject script)
        {
            MonoScript m_Script = MonoScript.FromScriptableObject(script);
            return GetAssetPathDir(m_Script);
        }

        public static List<string> GetAssetDirNames(List<DefaultAsset> assets){
            var rs = new List<string>();
            foreach (var item in assets)
            {
                var dir = GetAssetPathDir(item);
                var name = Path.GetFileNameWithoutExtension(dir);
                rs.Add(name);
            }

            return rs;
        }

        public static string GetAssetPathDir(Object asset)
        {
            string path = AssetDatabase.GetAssetPath(asset);
            if(!Directory.Exists(path))
                path = Path.GetDirectoryName(path);
            path = path.Substring(path.IndexOf("Assets"));
            return path;
        }

        //得到该目录下所有子目录名称
        public static List<string> GetPathSubDirs(string path)
        {
            var subDirsList = new List<string>();
            //C#遍历指定文件夹中的所有文件 
            DirectoryInfo theFolder = new DirectoryInfo(path);
            //子目录
            var subdirs = theFolder.GetDirectories();
            for (var i = 0; i < subdirs.Length; ++i)
            {
                subDirsList.Add(subdirs[i].FullName);
            }

            return subDirsList;
        }

        public static void GetPathFiles(string path, string formatSuffix, string exludeSuffix, ref List<string> fileList)
        {
            if (!System.IO.Directory.Exists(path)){
                return;
            }
            DirectoryInfo dir = new DirectoryInfo(path);
            FileInfo[] files = dir.GetFiles();
            DirectoryInfo[] dirs = dir.GetDirectories();

            foreach (FileInfo f in files)
            {
                if(!f.Name.Contains(exludeSuffix) && f.Name.Contains(formatSuffix))
                    fileList.Add(f.FullName);
            }

            //获取子文件夹内的文件列表 
            foreach (DirectoryInfo d in dirs)
            {
                GetPathFiles(d.FullName, formatSuffix, exludeSuffix, ref fileList);
            }
        }
    }
}


