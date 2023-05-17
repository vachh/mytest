using System.IO;
using System;
using System.Collections.Generic;
using UnityEngine;

public class PrefabsCache : GSingleton<PrefabsCache>
{
    private List<string> paths = new List<string>(){
        "Assets/_Res/PrefabsCache/Battle.prefab",
        "Assets/_Res/PrefabsCache/Choose.prefab",
        "Assets/_Res/PrefabsCache/GiftPopItemCell.prefab",
        "Assets/_Res/PrefabsCache/MapTile.prefab",
        "Assets/_Res/PrefabsCache/Product.prefab",
        "Assets/_Res/PrefabsCache/ProductRewardCell.prefab",
        "Assets/_Res/PrefabsCache/RewardFly.prefab",
        "Assets/_Res/PrefabsCache/WordFly.prefab",
        "Assets/_Res/PrefabsCache/MaskPop.prefab",
    };

    private Action endCall;
    private int allLoadCount;

    private Dictionary<string, GameObject> caches = new Dictionary<string, GameObject>();

    public GameObject GetGameObject(string name)
    {   
        GameObject obj = caches[name];
        if(obj == null){
            GDebug.LogError("no this object:" + name);
            return null;
        }

        return obj;
    }

    public GameObject GetInstantiateGameObject(string name, Transform parent, string objName = null)
    {   
        GameObject obj = caches[name];
        if(obj == null){
            GDebug.LogError("no this object:" + name);
            return null;
        }

        obj = UnityEngine.Object.Instantiate(obj, parent);
        obj.name = objName == null ? name : objName;
        return obj;
    }

    public void Load(Action endCall)
    {
        this.endCall = endCall;

        allLoadCount = paths.Count;
        var copyPaths = new List<string>(paths);
        for (int i = 0; i < copyPaths.Count; i++)
        {
            loadOne(copyPaths[i]);
        }
    }

    private void loadOne(string path)
    { 
        AddressableManager.ins.LoadAssetAsync<GameObject>(path, (hand, obj)=>{
            finishOne(true, path, obj);
        }, ()=>{
            finishOne(false, path, null);
        });
    }

    private void finishOne(bool succ, string path, GameObject obj)
    {
        if (!succ){
            var msg = "load fail: " + path;
            GDebug.LogError(msg);
        }else{
            var name = Path.GetFileNameWithoutExtension(path);
            caches[name] = obj;
        }

        paths.Remove(path);
        if(paths.Count == 0)
            endCall.InvokeSafe();
    }
}
