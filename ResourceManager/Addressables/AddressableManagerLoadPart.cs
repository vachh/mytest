using System;
using System.Collections;
using System.Collections.Generic;
using Spine.Unity;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine.U2D;

public partial class AddressableManager
{
    private AssetsCachePool<GameObject, Sprite> spriteCaches = new AssetsCachePool<GameObject, Sprite>();
    private AssetsCachePool<GameObject, SpriteAtlas> spriteAtlasCaches = new AssetsCachePool<GameObject, SpriteAtlas>();
    private AssetsCachePool<GameObject, GameObject> gameObjectCaches = new AssetsCachePool<GameObject, GameObject>();
    private AsyncOperationHandle operationHandleDefault = new AsyncOperationHandle();
    public void CleanCache()
    {
        GTimer.ins.addFrameDelay(() =>
        {
            spriteCaches.ClearCachePool();
            spriteAtlasCaches.ClearCachePool();
            gameObjectCaches.ClearCachePool();
            Resources.UnloadUnusedAssets();
        }, 2, "AbLoadManager CleanCache");
    }

    public void LoadAudio(string path, Action<AudioClip> endCall){
        LoadAssetAsync<AudioClip>(path, (hand, rs) =>
        {
            endCall.InvokeSafe(rs);
        });
    }

    public AsyncOperationHandle LoadSpriteBySpriteatlas(string path, string spriteName, GameObject handObj, Action<Sprite> call, Action failCall = null, Action<float> proCall = null)
    {
        Func<bool> checkCache = ()=>{
            if (spriteAtlasCaches.TryGet(path, handObj, out var cacheSpriteAtlas)){
                var spr = cacheSpriteAtlas.GetSprite(spriteName);
                if(spr != null){
                    call.InvokeSafe(spr);
                    return true;
                }
            }
            return false;
        };

        if(checkCache())
            return operationHandleDefault;

        return LoadAssetAsync<SpriteAtlas>(path, (hand, spriteAtlas) =>
        {
            if(handObj == null || checkCache() || spriteAtlas == null)
            {
                Addressables.Release(hand);
                return;
            }

            var sprite = spriteAtlas.GetSprite(spriteName);
            if (sprite == null)
            {
                GDebug.LogError(path + ", no find this spr: " + spriteName);
                Addressables.Release(hand);
                return;
            }
            
            spriteAtlasCaches.Add(path, hand, handObj, spriteAtlas);
            call.InvokeSafe(sprite);
        }, failCall, proCall);
    }

    public AsyncOperationHandle LoadSprite(string path, GameObject handObj, Action<Sprite> call, Action failCall = null, Action<float> proCall = null)
    {
        Func<bool> checkCache = ()=>{
            if(spriteCaches.TryGet(path, handObj,out var sprite)){
                call.InvokeSafe(sprite);
                return true;
            }
            return false;
        };

        if(checkCache())
            return operationHandleDefault;

        return LoadAssetAsync<Sprite>(path, (hand, spr) =>
        {
            if(handObj == null || checkCache() || spr == null){
                Addressables.Release(hand);
                return;
            }

            spriteCaches.Add(path, hand, handObj, spr);
            call.InvokeSafe(spr);
            
        }, failCall, proCall);
    }

    private static AsyncOperationHandle tmphand = new AsyncOperationHandle();
    private static Dictionary<string, int> loadingNames = new Dictionary<string, int>();
    public void LoadOnlyOneGameObject(string name, Action<bool, AsyncOperationHandle, GameObject> call)
    {
        if(loadingNames.ContainsKey(name))
            return;
        loadingNames[name] = 0;
        LoadAssetAsync<GameObject>(name, (hand, obj)=>{
            loadingNames.Remove(name);
            call.InvokeSafe(true, hand, obj);
        }); 
    }

    public void LoadGameObjectAndInstantiate(string name, Transform parent, Action<GameObject> endcall = null)
    {   
        AddressableManager.ins.LoadGameObject(name, parent.gameObject, (obj)=>{
            obj.name = name;
            obj = UnityEngine.Object.Instantiate(obj, parent);
            endcall.InvokeSafe(obj);
        });
    }

    public AsyncOperationHandle LoadGameObject(string path, GameObject handObj, Action<GameObject> call, Action failCall = null, Action<float> progressCall = null)
    {
        Func<bool> checkCache = ()=>{
            if(gameObjectCaches.TryGet(path, handObj,out var sprite)){
                call.InvokeSafe(sprite);
                return true;
            }
            return false;
        };

        if(checkCache())
            return operationHandleDefault;

        return LoadAssetAsync<GameObject>(path, (hand, obj) =>
        {
            if (handObj == null || checkCache() || obj == null)
            {
                Addressables.Release(hand);
                return;
            }

            gameObjectCaches.Add(path, hand, handObj, obj);
            call.InvokeSafe(obj);
        }, failCall, progressCall);
    }
}
