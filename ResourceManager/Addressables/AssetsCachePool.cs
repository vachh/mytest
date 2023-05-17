using System.Data.Common;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine.UI;

public class AssetsCachePool<THandObj, TRes> where THandObj: UnityEngine.Object where TRes : UnityEngine.Object
{
    protected class HandData{
        public AsyncOperationHandle hand;
        public List<THandObj> refs;
        public TRes res;
    }

	protected Dictionary<string, HandData> caches;
    public AssetsCachePool()
    {
        caches = new Dictionary<string, HandData>();
    }

    private static int repeatIndex = 0;
    
    public void Add(string key, AsyncOperationHandle hand, THandObj handObj, TRes res)
	{   
        //重复记录任然要保存下来，不然清除不了
        if(caches.ContainsKey(key)){
            key = key + "_" + repeatIndex++;
            GDebug.Log("AbCachePool repeat set: " + key);
        }

        caches[key] = new HandData(){ 
            hand = hand,
            refs = new List<THandObj>(){ handObj },
            res = res,
        };
	}

    public void ClearCachePool()
    {
        var keys = caches.Keys.ToList();
        for (int i = 0; i < keys.Count; i++){   
            var data = caches[keys[i]];
            var needRemove = true;
            foreach (var item in data.refs){
                if(item != null){
                    needRemove = false;
                    break;
                }   
            }

            if(needRemove){
                remove(keys[i]);
            }
        }
    }

    public bool TryGet(string key, THandObj handObj, out TRes res)
    {
        if (caches.ContainsKey(key)){
            var data = caches[key];
            if(!data.refs.Contains(handObj)){
                data.refs.Add(handObj);
            }
            res = data.res;
            return true;
        }
        res = null;
        return false;
    }

    protected void remove(string key){
        var data = caches[key];
        if(data.hand.IsValid()){
            Addressables.Release(data.hand);
            GDebug.Log("AbCachePool Release hand:" + key);
        }
        caches.Remove(key);
    }
}