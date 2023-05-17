using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Newtonsoft.Json;

[Serializable]
public class SpriteRef
{
    public string p;
    
    //是否无效
    public bool isInvalid(){
        return string.IsNullOrEmpty(p);
    }

    public void setSprite(Image image){
        if(isInvalid() || image == null){
            return;
        }
        AddressableManager.ins.LoadSprite(p, image.gameObject, (spr)=>{
            image.sprite = spr;
        });
    }

    public IEnumerator LoadSprite(GameObject handObj, Action<Sprite> endCall){
        if(isInvalid() || handObj == null){
            yield break;
        }

        yield return AddressableManager.ins.LoadSprite(p, handObj, (spr)=>{
            endCall(spr);
        });
    }
}