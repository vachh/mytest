using System.IO;
using System;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;

public static class ConfigLoader
{

#if UNITY_IOS
    private static bool IsIos = true;
#else
    private static bool IsIos = false;
#endif

    public static void Load(string path, Action<string> succCall){
        
        var firstLoadPath = path; 
        var secondLoadPath = path; 
        if(IsIos){
            var fileName = Path.GetFileNameWithoutExtension(path);
            firstLoadPath = $"{fileName}_ios.json";
        }

        Action<AsyncOperationHandle, TextAsset> succLoadCall = (hand, rs)=>{
            succCall.InvokeSafe(rs.text);
            
            if(!Application.isPlaying)
                return;
            GTimer.ins.addDelay(()=>{
                Addressables.Release(hand);
            }, 10f, "release Json Hand");
        };

		AddressableManager.ins.LoadAssetAsync<TextAsset>(firstLoadPath, succLoadCall, ()=>{
            if(IsIos)
                AddressableManager.ins.LoadAssetAsync<TextAsset>(secondLoadPath, succLoadCall);
        }, null, IsIos ? false : true);
	}

    public static void LoadJson<T>(string path, Action<T> endCall){
        Load(path, (str) =>{
            var rs = Newtonsoft.Json.JsonConvert.DeserializeObject<T>(str);
            endCall.InvokeSafe(rs);
        });
    }

}
