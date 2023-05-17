using System.Collections;
using System.Linq;
using System;
using System.Runtime;
using System.Collections.Generic;
using UnityEngine;
using Cysharp.Threading.Tasks;

public class EquipAttachManager : GSingleton<EquipAttachManager>
{
    private Dictionary<int, AttachData> datas = new Dictionary<int, AttachData>();
    public Dictionary<int, AttachData> Datas => datas;

    public override void setup(){}

    public cfg_equipAttach GetEquipAttachCfg(int id){
        return ConfigManager.cfg_equipAttachs[id];
    }

    public cfg_equipAttach GetEquipAttachCfgByType(int type){
        if(DB.Hero.EquipAttachs.TryGetValue(type, out var attach))
            return GetEquipAttachCfg(attach);
        return null;
    }


    public List<cfg_equipAttach> GetEquipAttachList(int type){
        return ConfigManager.cfg_equipAttachs.Values.ToList().Where(a=> a.type == type).ToList();
    }

    public bool IsEquipAttach(int type, int id){
        if(DB.Hero.EquipAttachs.ContainsKey(type)){
            return DB.Hero.EquipAttachs[type] == id;
        }
        return false;
    }

    public void SetEquipAttach(cfg_equipAttach cfg, AttachData newData){
        var oldId = 0;
        DB.Hero.EquipAttachs.TryGetValue(newData._type, out oldId);
        LogEvent.ins.Equip_Skin(oldId, newData.id);

        DB.Hero.SetEquipAttachs(newData._type, newData.id);
        datas[newData._type] = newData;
        if(newData.sprite == null)
            loadAttachDataSprite(cfg, newData).Forget();
        else
            EEvent<AttachData>.ins.Send(EEventName.Hero_equipAttachChange, newData);
    }

    private async UniTask loadAttachDataSprite(cfg_equipAttach cfg, AttachData newData){
        await cfg.skin.LoadSprite(BaseScene.canvasTrans.gameObject, (spr)=>{
            newData.sprite = spr;
        }).ToUniTask();

        EEvent<AttachData>.ins.Send(EEventName.Hero_equipAttachChange, newData);
    }

    public async UniTask GetAttachDatas(GameObject handObj){
        datas.Clear();
        var list = new List<UniTask>();
        foreach (var item in DB.Hero.EquipAttachs)
        {
            var type = item.Key;
            var id = item.Value;
            var cfg = GetEquipAttachCfg(id);
            var data = new AttachData(){
                id = id,
                attachName = cfg.attachName,
                slotName = cfg.slotName,
            };

            datas[type] = data;
            var task = cfg.skin.LoadSprite(handObj, (spr)=>{
                data.sprite = spr;
            }).ToUniTask();
            list.Add(task);
        }

        await UniTask.WhenAll(list);
    }

   
}