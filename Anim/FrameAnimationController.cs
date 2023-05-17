using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.U2D;
using System;
using System.Linq;

public class FrameAnimationController : MonoBehaviour, IHeroAnimationController
{
    [Serializable]
    public class AnimationInfo{
        public string animName;
        public SpriteAtlas spriteAtlas;
        public int frame = 20;
        [Header("sprite命名前缀")]
        public string spriteNamePre;
        [Header("sprite命名index偏移")]
        public int spriteNameIndexOffset;

        public Dictionary<int, List<Action>> frameActions = new Dictionary<int, List<Action>>();
        public Sprite GetSprite(int index){
            return spriteAtlas.GetSprite(spriteNamePre + (index + spriteNameIndexOffset));
        }

        public float GetFrameFime(int frameCount){
            return 1f / this.frame * frameCount;
        }
    }
    [SerializeField] private List<AnimationInfo> animationList;
    [SerializeField] private Image animImage;
    [Header("默认播放动画")]
    [SerializeField] private string defaultAnim;
    [Header("是否循环")]
    [SerializeField] private bool startLoop;

    [Header("赋值")]
    [SerializeField] private string animNameNow;
    [SerializeField] private bool isPause;
    [SerializeField] private float timer;  
    [SerializeField] private float frameTime;
    [SerializeField] private int frameIndex;
    [SerializeField] private bool isLoop;
    private AnimationInfo animInfoNow;
    private void Awake()
    {
        var tmp = animationList.First();
        animImage.sprite = tmp.GetSprite(0);
        isPause = false;
        timer = 0;
        frameTime = 0;
        frameIndex = 0;
        animNameNow = "";
        
        PlayDefaultAnim();
    }

    private int testIndex = 0;
    [EditorButton]
    private void testPlay(bool isLoop){
        testIndex++;
        if(testIndex >= animationList.Count)
            testIndex = 0;

        PlayAndEndPlayDefault(animationList[testIndex].animName, isLoop);
    }

    public void PlayDefaultAnim(){
        if(!string.IsNullOrEmpty(defaultAnim))
            Play(defaultAnim, startLoop);
    }

    public void PlayAndEndPlayDefault(string animName, bool isLoop, Action onceEndCall = null){
        Play(animName, isLoop);
        RegisterFrameEndAction(PlayDefaultAnim);
    }

    public void Play(string animName, bool isLoop, Action onceEndCall = null){
        animInfoNow = animationList.FirstOrDefault(x => x.animName == animName);
        if(animInfoNow == null){
            GDebug.LogError($"no find this animation: {animName}");
            return;
        }


        this.animNameNow = animInfoNow.animName;
        this.isLoop = isLoop;

        //GDebug.LogError("animInfoNow: " + animNameNow);

        timer = 0;
        frameTime = 1f / animInfoNow.frame;
        frameIndex = 0;
        animImage.sprite = animInfoNow.GetSprite(frameIndex);
        animInfoNow.frameActions.Clear();

        if(onceEndCall != null)
            RegisterFrameEndAction(onceEndCall);
    }

    public float GetAnimFrameFime(int frameCount){
        if(animInfoNow != null)
            return animInfoNow.GetFrameFime(frameCount);
        return 0f;
    }

    //注册帧事件
    public FrameAnimationController RegisterFrameAction(int frame, Action action){
        if(animInfoNow == null)
            return this;
        if(!animInfoNow.frameActions.ContainsKey(frame))
            animInfoNow.frameActions[frame] = new List<Action>();
        if(!animInfoNow.frameActions[frame].Contains(action))
            animInfoNow.frameActions[frame].Add(action);
        return this;
    }

    public FrameAnimationController RegisterFrameEndAction(Action action){
        if(animInfoNow == null)
            return this;
        return RegisterFrameAction(animInfoNow.spriteAtlas.spriteCount - 1, action);
    }

    public void SetPause(bool isPause){
        this.isPause = isPause;
    }
    
    private void Update()
    {
        if(isPause || animInfoNow == null)
            return;

        timer += Time.deltaTime;
        if (timer >= frameTime)
        {
            timer -= frameTime;
            frameIndex++;
            if (frameIndex >= animInfoNow.spriteAtlas.spriteCount)
            {
                if(isLoop)
                    frameIndex = 0;
                else{
                    var tmp = --frameIndex;
                    if(animInfoNow.frameActions.ContainsKey(tmp)){
                        foreach (var item in animInfoNow.frameActions[tmp])
                        {
                            item.InvokeSafe();
                        }
                    }
                    animInfoNow = null;
                    return;
                }
            }

            animImage.sprite = animInfoNow.GetSprite(frameIndex);
            if(animInfoNow.frameActions.ContainsKey(frameIndex)){
                foreach (var item in animInfoNow.frameActions[frameIndex])
                {
                    item.InvokeSafe();
                }
            }
        }
    }
}
