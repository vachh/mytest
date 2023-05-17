using System;
using System.Collections.Generic;
using Spine.Unity;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine.U2D;
using UnityEngine.UI;

public class CommonResLoader : GSingleton<CommonResLoader>
{

    public override void setup()
    {

    }
    
    public void SetLoginSprite(string name, Image image)
    {   
        AddressableManager.ins.LoadSprite($"Assets/_Res/Textures/Login/{name}.png", image.gameObject, (spr)=>{
            image.sprite = spr;
        });
    }
}
