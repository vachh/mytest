using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class EquipAttackChoosePanel : BasePop
{

    public EquipAttackItem item;
    public Transform content;
    public Transform chooseItem;
    public GameObject tipObject;
    public Button clsoeBtn;
    public Button applyBtn;
    public EquipAttachSet equipAttachSet;

    private cfg_equipAttach cfgChoose;
    private int lastId = 0;
    private Dictionary<int, AttachData> caches = new Dictionary<int, AttachData>();

    protected override void setup()
    {
        item.gameObject.SetActive(false);
        clsoeBtn.onClick.AddListener(close);
        applyBtn.onClick.AddListener(()=>{
            if(cfgChoose != null && lastId != cfgChoose.id && caches.ContainsKey(cfgChoose.id)){
                lastId = cfgChoose.id;
                EquipAttachManager.ins.SetEquipAttach(cfgChoose, caches[cfgChoose.id]);
                setTipState();
            }
        });
    }

    public void Show(int equipType, List<cfg_equipAttach> datas){
        
        StartCoroutine(IEShow(equipType, datas));
    }

    private class ChooseData{
        public cfg_equipAttach cfg;
        public bool unlock;
        public int sortId;
    }

    private IEnumerator IEShow(int equipType, List<cfg_equipAttach> datas){
        
        chooseItem.gameObject.SetActive(false);

        var chooseDatas = new List<ChooseData>();
        foreach (var cfg in datas)
        {
            var isUnlock = DB.Hero.isUnlockEquipAttach(cfg.type, cfg.id);
            chooseDatas.Add(new ChooseData(){
                cfg = cfg,
                unlock = isUnlock,
                sortId = isUnlock ? cfg.id: cfg.id + 100000,
            });
        }

        chooseDatas.Sort((a, b)=> a.sortId.CompareTo(b.sortId));

        for (int i = 0; i < chooseDatas.Count; i++)
        {
            var chooseData = chooseDatas[i];
            var cfg = chooseData.cfg;
            var itemCopy = Instantiate(item, content);
            itemCopy.gameObject.SetActive(true);
            itemCopy.Init(chooseData.cfg, chooseData.unlock, chooseAction);
            if(EquipAttachManager.ins.IsEquipAttach(cfg.type, cfg.id)){
                chooseAction(itemCopy.transform, cfg);
                lastId = cfg.id;
            }

            if(i % 10 == 0)
                yield return 0;
        }

        setTipState();
    }

    private void chooseAction(Transform transform, cfg_equipAttach cfg){
        chooseItem.gameObject.SetActive(true);
        chooseItem.SetParent(transform);
        chooseItem.localPosition = Vector3.zero;
        chooseItem.localScale = Vector3.one;

        cfgChoose = cfg;
        setTipState();
        if(caches.ContainsKey(cfg.id)){
            equipAttachSet.ChangeAttach(caches[cfg.id]);
        }else{
            var newData = new AttachData(){
                _type = cfg.type,
                id = cfg.id,
                attachName = cfg.attachName,
                slotName = cfg.slotName,
            };
            StartCoroutine(loadAttachDataSprite(cfg, newData));
        }
    }

    private void setTipState(){
        var showTip = cfgChoose != null && cfgChoose.id == lastId;
        tipObject.SetActive(showTip);
        applyBtn.gameObject.SetActive(cfgChoose != null && !showTip);
    }

    private IEnumerator loadAttachDataSprite(cfg_equipAttach cfg, AttachData newData){
        yield return cfg.skin.LoadSprite(gameObject, (spr)=>{
            newData.sprite = spr;
        });

        caches[cfg.id] = newData;
        equipAttachSet.ChangeAttach(newData);
    }
}
