using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.U2D;
using System;
using System.Linq;
using Spine.Unity;
using DG.Tweening;
using Cysharp.Threading.Tasks;

public class HeroAnimationControllerProxy : MonoBehaviour
{
    public bool isSelfHero = false;
    public HeroAnimLoadBase animLoader;
    private IHeroAnimationController animationController;

    public void Reset(){
        animationController = animLoader.GetHeroAnimationController();
        animationController.PlayDefaultAnim();
    }

    public bool WalkingAnimation(Action endCallback){
        if(isSelfHero){
            animationController.Play("walking", true, endCallback);
            return true;
        }else{
            //怪物没有行走动画
            //frameAnimationController.Play("walk", true);
            return false;
        }
    }

    public bool AttackAnimation(Action endCallback, string attackName = "attack"){
        animationController.PlayAndEndPlayDefault(attackName, false, endCallback);
        return true;
    }

    // public float HurtAnimation(Action endCallback){
    //     if(isSelfHero){
    //         spineAnimationController.PlayAndEndPlayDefault("def", false, endCallback);
    //         return 0.45f;
    //     }else{
    //         var hitTime = frameAnimationController.PlayAndEndPlayDefault("block", false).GetAnimFrameFime(7);
    //         frameAnimationController.RegisterFrameEndAction(endCallback);
    //         return hitTime;
    //     }
    // }

    // public float DodgeAnimation(){
    //     if(isSelfHero){
    //         spineAnimationController.PlayAndEndPlayDefault("def", false);
    //         return 0.45f;
    //     }else{
    //         var hitTime = frameAnimationController.PlayAndEndPlayDefault("block", false).GetAnimFrameFime(7);
    //         return hitTime;
    //     }
    // }

    public bool DeadAnimation(){
        if(isSelfHero){
            animationController.Play("die", false);
            return true;
        }else{
            //怪物没有死亡动画
            //frameAnimationController.Play("die", false);
            return false;
        }
    }
}
