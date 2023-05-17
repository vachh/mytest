using System;
using System.Collections.Generic;
using Spine.Unity;
using UnityEngine;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine.U2D;
using UnityEngine.UI;

public class BattleResLoader : GSingleton<BattleResLoader>
{

    public override void setup()
    {

    }
    
    //设置产品Icon
    public void SetProductIconById(int id, Image img, bool nativeSize = false)
    {
        var cfg = ConfigManager.GetProduct(id, true);
        SetProductIcon(cfg.line, cfg.id, img);
    }

    //设置产品Icon
    public void SetProductIcon(int line, int id, Image imgOriginal, bool nativeSize = false)
    {
        if (imgOriginal == null)
        {
            return;
        }

        var path = $"Assets/_Res/Lines/Line{line}.spriteatlas";
        AddressableManager.ins.LoadSpriteBySpriteatlas(path, "" + id, imgOriginal.gameObject, (spr)=>{
            imgOriginal.sprite = spr;
            if (nativeSize)
            {
                imgOriginal.SetNativeSize();
            }
        });
    }
}
