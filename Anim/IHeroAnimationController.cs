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

public interface IHeroAnimationController
{
    public void PlayDefaultAnim();
    public void PlayAndEndPlayDefault(string animName, bool isLoop, Action onceEndCall = null);
    public void Play(string animName, bool isLoop, Action onceEndCall = null);
}
