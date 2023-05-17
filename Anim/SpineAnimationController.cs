using System.Collections.Specialized;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.U2D;
using System;
using System.Linq;
using Spine.Unity;
using Spine;

public class SpineAnimationController : MonoBehaviour, IHeroAnimationController
{
    public SkeletonGraphic skeletonGraphic;
    [SpineAnimation]
    public string startAnimationName;
    public bool startLoop = true;
    private void Start()
    {

    }

    public void PlayDefaultAnim(){
        Play(startAnimationName, startLoop);
    }

    public void PlayAndEndPlayDefault(string animName, bool isLoop, Action onceEndCall = null){
        Play(animName, isLoop, onceEndCall);
        skeletonGraphic.AnimationState.AddAnimation(0, startAnimationName, startLoop, 0);
    }

    public void Play(string animName, bool isLoop, Action onceEndCall = null){
        var trackEntry = skeletonGraphic.AnimationState.SetAnimation(0, animName, isLoop);
        trackEntry.Complete += (trackEntry)=>{
            onceEndCall.InvokeSafe();
        };
    }
}
