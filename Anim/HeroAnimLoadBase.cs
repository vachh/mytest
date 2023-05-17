using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using Cysharp.Threading.Tasks;

//角色动画加载
public abstract class HeroAnimLoadBase : MonoBehaviour
{
    private IHeroAnimationController heroAnimationController = null;
    private LevelHeroAnimData levelHeroAnimData = null;
    private FightEffectPosition fightEffectPosition = null;
    private Graphic graphic = null;
    
    public abstract GameObject GetHeroAnimGameObject();

    public abstract UniTask Load(string assetPath, bool isInvert = false);

    public void Reset(){
        heroAnimationController = null;
        levelHeroAnimData = null;
        fightEffectPosition = null;
        graphic = null;
    }

    public IHeroAnimationController GetHeroAnimationController()
    {
        return heroAnimationController ??= GetHeroAnimGameObject().GetComponent<IHeroAnimationController>();;
    }

    public LevelHeroAnimData GetLevelHeroAnimData()
    {
        return levelHeroAnimData ??= GetHeroAnimGameObject().GetComponent<LevelHeroAnimData>();
    }

    public FightEffectPosition GetFightEffectPosition()
    {
        return fightEffectPosition ??= GetHeroAnimGameObject().GetComponent<FightEffectPosition>();
    }

    public Transform GetFightEffectParent()
    {
        return GetHeroAnimGameObject().transform;
    }

    public Graphic GetGraphic()
    {
        return graphic ??= GetHeroAnimGameObject().GetComponentInChildren<Graphic>();
    }
}