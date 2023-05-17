using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class EquipAttackItem : MonoBehaviour
{

    public Image icon;
    public GameObject lockObject;
    public Button button;
    private cfg_equipAttach cfg;
    private Action<Transform, cfg_equipAttach> chooseAction;

    private void Start() {
        button.onClick.AddListener(()=>{
            chooseAction.InvokeSafe(transform, cfg);
        });
    }

    public void Init(cfg_equipAttach cfg, bool isUnlock, Action<Transform, cfg_equipAttach> chooseAction){
        lockObject.SetActive(!isUnlock);
        button.interactable = isUnlock;
        if(cfg.productIconId > 0){
            BattleResLoader.ins.SetProductIconById(cfg.productIconId, icon);
        }else{
            cfg.skin.setSprite(icon);
        }

        this.cfg = cfg;
        this.chooseAction = chooseAction;
    }


}
