using System;
using System.Collections.Generic;
using System.Collections;
using Language;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine;

public class OperationHandleAutoRelease : MonoBehaviour
{   
    private class HandProxy{
        private Dictionary<string, List<AsyncOperationHandle>> hands;
        public HandProxy(){
            hands = new Dictionary<string, List<AsyncOperationHandle>>();
        }

        public void Add(string assetPath, AsyncOperationHandle hand){
            if(!hands.ContainsKey(assetPath))
                hands[assetPath] = new List<AsyncOperationHandle>();
            hands[assetPath].Add(hand);
        }

        public void Release(){
            //确保在主线程运行
            GTimer.ins.addFrameDelay(()=>{
                foreach (var item in hands)
                {
                    var assetPath = item.Key;
                    foreach (var handle in item.Value){
                        if(handle.IsValid()){
                            GDebug.Log($"OperationHandleAutoRelease: {assetPath}");
                            Addressables.Release(handle);
                        }
                    }
                    item.Value.Clear();
                }
                hands.Clear();
            }, 1, "OperationHandleAutoRelease");
        }

        ~HandProxy(){
            //手机上不在主线程调用
            Release();
        }
    }

    private HandProxy proxy;
    [SerializeField] private List<string> assetPaths;
    
    private void add(string assetPath, AsyncOperationHandle hand){
        if(!assetPaths.Contains(assetPath))
            assetPaths.Add(assetPath);
        proxy.Add(assetPath, hand);
    }

    public void Release(){
        proxy.Release();
    }

    public static OperationHandleAutoRelease Add(GameObject gameObject, string assetPath, AsyncOperationHandle hand){
        var com = gameObject.GetComponent<OperationHandleAutoRelease>();
        if(com == null){
            com = gameObject.AddComponent<OperationHandleAutoRelease>();
            com.proxy = new HandProxy();
            com.assetPaths = new List<string>();
        }
        com.add(assetPath, hand);
        return com;
    }
}
