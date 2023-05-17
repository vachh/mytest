using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.AddressableAssets.ResourceLocators;
using UnityEngine.ResourceManagement.AsyncOperations;

public class AbCatalogUpdate2 : MonoBehaviour
{

    private bool isUpdating = false;
    private AsyncOperationHandle<List<IResourceLocator>> updateHandle;
    private static Action endCall;

    public static void Check(Action _endCall){
        endCall = _endCall;
        //_endCall.Invoke();
        GUtils.GetDontDestroyObjectWithMono<AbCatalogUpdate2>();
    }

    private void Start() {
        StartCoroutine(checkUpdate());
    }

    private void Update() {
        if(isUpdating){
            //log("checkUpdate percent: " + updateHandle.PercentComplete);
        }
    }
    
    private long totalDownLoadSize;
    private long hasDownLoadSize;

    private List<object> mUpdateResKeys = new List<object>();

    
    private IEnumerator checkUpdate()
    {
        //初始化Addressable
        var init = Addressables.InitializeAsync();
        yield return init;
        //开始连接服务器检查更新
        AsyncOperationHandle<List<string>> checkHandle = Addressables.CheckForCatalogUpdates(false);
        yield return checkHandle;

        if (checkHandle.Status == AsyncOperationStatus.Succeeded)
        {
            List<string> catalogs = checkHandle.Result;
            foreach (var item in catalogs)
            {
                
            }
            if (catalogs != null && catalogs.Count > 0)
            {
                var updateHandle = Addressables.UpdateCatalogs(catalogs, false);
                yield return updateHandle;
                //"AddressablesMainContentCatalog"
                var x = updateHandle.Result;
                for (int i = 0; i < updateHandle.Result.Count; i++)
                {
                    foreach (var key in updateHandle.Result[i].Keys)
                    {
                        GDebug.LogError(key);
                        if(key.ToString().Contains(".bundle"))
                            continue;
                        var sizeHandle = Addressables.GetDownloadSizeAsync(key);
                        yield return sizeHandle;
                        if (sizeHandle.Status == UnityEngine.ResourceManagement.AsyncOperations.AsyncOperationStatus.Succeeded)
                        {
                            if (sizeHandle.Result > 0)
                            {
                                totalDownLoadSize += sizeHandle.Result;
                                mUpdateResKeys.Add(key);
                                log($"获取更新中: key: {key} size: {sizeHandle.Result}");
                            }
                        }
                    }
                    
                    //log("获取更新中..." + updateHandle.Result.Count);
                }
                log($"更新== Size: {(totalDownLoadSize / 1024f / 1024f).ToString("0.00")}M");
                Addressables.Release(updateHandle);
                hasDownLoadSize = 0;
                //ShowLoadingInfo("获取更新完成!", 1);
                //下载更新
                StartCoroutine(DownloadRes());
            }
            else
            {
                GDebug.Log("不需要更新!");
                //进入游戏
                endCall.Invoke();
            }
        }
        else
        {
            //ShowLoadingInfo("获取更新失败!");
            //获取失败后的操作处理
            //todo
            GDebug.LogError("获取更新失败!");
            endCall.Invoke();
        }
        Addressables.Release(checkHandle);

    }

    private IEnumerator DownloadRes()
    {
        //下载处理
        if (mUpdateResKeys.Count == 0)
            yield break;
        
            
        for (int i = 0; i < mUpdateResKeys.Count; i++)
        {
            var downloadHandle = Addressables.DownloadDependenciesAsync(mUpdateResKeys[i], false); 
            DownloadStatus downloadStatus = downloadHandle.GetDownloadStatus();
            while (!downloadHandle.IsDone && downloadHandle.Status != AsyncOperationStatus.Failed)
            {
                //是否显示下载具体大小
                //if (isShowDownloadSize)
                {
                    downloadStatus = downloadHandle.GetDownloadStatus();
                }
                //else
                {
                    log($"更新中 key: {mUpdateResKeys[i]}..." + downloadStatus.DownloadedBytes);
                }
                yield return null;
            }
            if (downloadHandle.Status == AsyncOperationStatus.Failed)
            {
                GDebug.LogError("更新失败： " + downloadHandle.Result);
                //下载失败相关处理
                endCall.Invoke();
                yield break;
            }
            hasDownLoadSize += downloadStatus.TotalBytes;
            Addressables.Release(downloadHandle);
            Addressables.ClearDependencyCacheAsync(mUpdateResKeys[i]);
        }
    
        //ShowLoadingInfo("下载完毕!", 1);
        endCall.Invoke();
    }

    private void log(string str){
        GDebug.LogError($"AbCatalogUpdate: {str}");
    }
}
