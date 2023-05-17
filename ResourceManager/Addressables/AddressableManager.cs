using System.Collections;
using System;
using System.Collections.Generic;
using Spine.Unity;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.AddressableAssets.ResourceLocators;
using UnityEngine.ResourceManagement.AsyncOperations;

public partial class AddressableManager : GSingleton<AddressableManager>
{
    public override void setup()
    {

    }

    //！！！如果遇到莫名其妙的加载不到资源，检查下 Play Mode Script 是不是选的第三个模式，改为第一个模式即可
    public AsyncOperationHandle LoadAssetAsync<T>(string assetPath, Action<AsyncOperationHandle, T> succCall, Action failCall = null, Action<float> progressCall = null, bool logErr = true) where T : UnityEngine.Object
    {
        
#if UNITY_EDITOR || TEST
        //GDebug.Log(assetPath);
#endif

#if UNITY_EDITOR
        if(!Application.isPlaying){
            GDebug.Log($"getAssetsInEditor:{assetPath}");
            var res = getAssetsInEditor<T>(assetPath);
            if(res != null){
                succCall.InvokeSafe(new AsyncOperationHandle(), res);
            }else{
                failCall.InvokeSafe();
            }
            return new AsyncOperationHandle();
        }
#endif
        var loadHand = Addressables.LoadAssetAsync<T>(assetPath);
        loadHand.Completed += op =>
        {
            _abLoadEnd(assetPath, loadHand, succCall, failCall, logErr);
        };

        if(progressCall != null){
            BaseLayer.Layer.StartCoroutine(getPro(loadHand, progressCall));
        }
        return loadHand;
    }

#if UNITY_EDITOR
    private static T getAssetsInEditor<T>(string path) where T: UnityEngine.Object
    {
        return UnityEditor.AssetDatabase.LoadAssetAtPath(path, typeof(T)) as T;
    }
#endif

    private IEnumerator getPro(AsyncOperationHandle handle, Action<float> progressCall){
        while (!handle.IsDone)
        {
            GDebug.Log("进度: " + handle.PercentComplete);
            progressCall.InvokeSafe(handle.PercentComplete);
            yield return null;
        }
    }

    private void _abLoadEnd<T>(string assetName, AsyncOperationHandle<T> loadHand, Action<AsyncOperationHandle, T> call, Action failCall, bool logError)
    {
        if (loadHand.Status == AsyncOperationStatus.Succeeded)
        {
            var rs = loadHand.Result;
#if UNITY_EDITOR
            var obj = rs as GameObject;
            if (obj != null)
            {
                refreshRendShader(obj);
                refreshSpineUIShader(obj);
            }
#endif
            call.InvokeSafe(loadHand, rs);
        }
        else
        {
            if (logError)
            {
                GDebug.LogError("AddressablesLoad failed: " + assetName + " error:" + loadHand.OperationException);
            }
            else
            {
                GDebug.Log("AddressablesLoad failed: " + assetName);
            }
            Addressables.Release(loadHand);
            failCall.InvokeSafe();
        }
    }

    //重新设置下shader，某些版本，editor模式下，ab包加载出来有丢失
    private void refreshRendShader(GameObject obj)
    {

#if !UNITY_EDITOR
        return;
#endif
        Renderer[] rens = obj.GetComponentsInChildren<Renderer>(true);
        foreach (var r in rens)
        {
            var mats = r.sharedMaterials;
            foreach (var mat in mats)
            {
                if (mat != null)
                {
                    var shaderName = mat.shader.name;
                    var newShader = Shader.Find(shaderName);
                    if (newShader != null)
                        mat.shader = newShader;
                    else
                        GDebug.Log("no this shader: " + shaderName);
                }
            }
        }
    }

    private void refreshSpineUIShader(GameObject obj)
    {
#if !UNITY_EDITOR
        return;
#endif
        var rens = obj.GetComponentsInChildren<SkeletonGraphic>();
        foreach (var r in rens)
        {
            var mats = r.material;
            if (mats != null)
            {
                var shaderName = mats.shader.name;
                var newShader = Shader.Find(shaderName);
                if (newShader != null)
                    mats.shader = newShader;
                else
                    GDebug.Log("no this shader: " + shaderName);
            }
        }
    }
}
