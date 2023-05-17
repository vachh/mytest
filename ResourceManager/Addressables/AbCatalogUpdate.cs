using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.AddressableAssets.ResourceLocators;
using UnityEngine.ResourceManagement.AsyncOperations;

public class AbCatalogUpdate : MonoBehaviour
{

    private bool isUpdating = false;
    private static Action endCall;
    private static Action<string, float, float, bool> invokeAddProgress;
    private static string loadTag;
    private static float maxAddProgress;

    private static float progress = 0f;

    public static void Check(Action _endCall, Action<string, float, float, bool> _invokeAddProgress, string _tag, float _maxAddProgress){
        endCall = _endCall;
        invokeAddProgress = _invokeAddProgress;
        loadTag = _tag;
        progress = 0f;
        maxAddProgress = _maxAddProgress;
        GUtils.GetDontDestroyObjectWithMono<AbCatalogUpdate>();
    }

    private void Start() {
        StartCoroutine(checkUpdate());
    }

    private void Update() {        
        if(Time.frameCount % 2 == 0 && progress < 100){
            progress++;
            invokeAddProgress(loadTag, maxAddProgress, 1, false);
        }

    }

    private IEnumerator checkUpdate()
    {
        //初始化Addressable
        var init = Addressables.InitializeAsync();
        yield return init;
        //开始连接服务器检查更新
        AsyncOperationHandle<List<string>> checkHandle = Addressables.CheckForCatalogUpdates(false);
        //检查结束，验证结果 
        yield return checkHandle;
        if (checkHandle.Status == AsyncOperationStatus.Succeeded)
        {
            List<string> catalogs = checkHandle.Result;
            if (catalogs != null && catalogs.Count > 0)
            {
                foreach (var item in catalogs)
                {
                    log($"update item: {item}");
                }
                isUpdating = true;
                log("download CheckForCatalogUpdates start");
                var updateHandle = Addressables.UpdateCatalogs(catalogs, false);
                yield return updateHandle;
                if (updateHandle.Status == AsyncOperationStatus.Succeeded){
                    log("CheckForCatalogUpdates succ");
                }else{
                    log("CheckForCatalogUpdates failed");
                }
                
                Addressables.Release(updateHandle);
                isUpdating = false;
                log("download CheckForCatalogUpdates finish");
            }
        }else{
            log("failed");
        }

        Addressables.Release(checkHandle);
        log("AbCatalogUpdate end");
        //只是计算进度条，不算 loadCounter, 所以 finish 都为 false
        invokeAddProgress(loadTag, maxAddProgress,100 - progress, false);
        endCall.InvokeSafe();
        Destroy(gameObject);
    }

    private void log(string str){
        GDebug.Log($"AbCatalogUpdate: {str}");
    }
}
