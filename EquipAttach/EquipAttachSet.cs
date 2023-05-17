using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using Cysharp.Threading.Tasks;

//装备附件设置
public class EquipAttachSet : HeroAnimLoadBase
{
    public int zIndex = 0;
    public bool StartLoad = true;
    public Vector3 localPos = Vector3.zero;
    private SkeletonGraphicChangeAttach skeletonGraphicChangeAttach;

    private Dictionary<int, AttachData> datas;
    private GameObject heroObject = null;
    private void Start(){
        gameObject.EEventOn<AttachData>(EEventName.Hero_equipAttachChange, ChangeAttach);
        if(StartLoad)
            Load("Assets/_Res/Heros/Hero1.prefab").Forget();
    }

    private void OnDestroy() {
        
    }

    public override async UniTask Load(string assetPath, bool isInvert = false){
        
        if(heroObject != null)
            return;
        Reset();
        var list = new List<UniTask>();
        var task = AddressableManager.ins.LoadGameObject(assetPath, gameObject, (obj)=>{
            heroObject = Instantiate(obj, transform);
            heroObject.transform.localPosition = localPos;
            heroObject.transform.SetSiblingIndex(zIndex);

            var scaleV3 = heroObject.transform.localScale;
            if(isInvert)
                scaleV3.x *= -1;

            skeletonGraphicChangeAttach = heroObject.GetComponent<SkeletonGraphicChangeAttach>() ?? heroObject.GetComponentInChildren<SkeletonGraphicChangeAttach>();
            heroObject.gameObject.SetActive(false);
        }).ToUniTask();
        
        list.Add(task);
        
        //GDebug.LogError(Time.frameCount);
        list.Add(EquipAttachManager.ins.GetAttachDatas(gameObject));
        
        
        await UniTask.WhenAll(list);
        //GDebug.LogError(Time.frameCount);
        heroObject.gameObject.SetActive(true);

        datas = EquipAttachManager.ins.Datas;
        skeletonGraphicChangeAttach.Apply(datas.Values.ToList(), true);
    }

    public override GameObject GetHeroAnimGameObject(){
        return heroObject;
    }

    public void ChangeAttach(AttachData newData){
        if(datas == null)
            return;

        datas[newData._type] = newData;
        skeletonGraphicChangeAttach.Apply(datas.Values.ToList(), false);
    }
}