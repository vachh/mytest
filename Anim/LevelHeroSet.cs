using System.Net.Mime;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using Cysharp.Threading.Tasks;

//头像设置
public class LevelHeroSet : HeroAnimLoadBase
{
    public bool StartLoad;
    [Range(0.5f, 2f)]
    public int zIndex = 0;
    public bool isLevelPassRefresh = false;
    private GameObject heroObject = null;
    private bool needReload = false;
    private void Start() {
        
        if(StartLoad)
            refresh();
        if(isLevelPassRefresh)
            gameObject.EEventOn(EEventName.LevelPass, refresh);
    }

    private void OnDestroy() {

    }

    private void OnEnable() {
        if(needReload)
            refresh();
        needReload = false;
    }

    private void refresh(){
        if(gameObject != null && gameObject.activeInHierarchy){
            var path = LevelManager.ins.GetLevelHeroAsset(DB.User.Level);
            Load(path).Forget();
        }
        else{
            needReload = true;
        }
    }

    public override async UniTask Load(string assetPath, bool isInvert = false){
        if(heroObject != null)
            Destroy(heroObject);

        Reset();
        await AddressableManager.ins.LoadGameObject(assetPath, gameObject, (obj)=>{
            if(heroObject != null)
                Destroy(heroObject);

            heroObject = Instantiate(obj, transform);
            heroObject.transform.SetSiblingIndex(zIndex);
            
            var scaleV3 = heroObject.transform.localScale;
            if(isInvert)
                scaleV3.x *= -1;
            heroObject.transform.localScale = scaleV3;
        }).ToUniTask();
    }

    public override GameObject GetHeroAnimGameObject(){
        return heroObject;
    }
}