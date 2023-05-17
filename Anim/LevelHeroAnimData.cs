using System.Net.Mime;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

//关卡怪物动画信息数据
public class LevelHeroAnimData : MonoBehaviour
{   
    [Header("命中帧时间")]
    public float hitTime = 0.5f;
    [Header("命中特效")]
    public string hitEffect = "Assets/_Res/PrefabsFight/Defense_eff.prefab";
    [Header("命中音效")]
    public string hitSound = "Fight_KnifeHit";
   
}