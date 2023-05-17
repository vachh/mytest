using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.AddressableAssets;
using UnityEngine.ResourceManagement.AsyncOperations;
using UnityEngine.U2D;


public class LoadCounter{

    private bool canLoadError;
    private int allCount; //总个数
    private int succCount; //成功个数
    private int failCount; //失败个数
    private bool endSucc;

    public LoadCounter(bool _canLoadError){
        canLoadError = _canLoadError;
    }

    public void addLoadCount(int count){
        allCount += count;
    }

    public float getSuccProgress(){
        if(allCount == 0){
            return 1;
        }
        return succCount / (float)allCount;
    }

    public void finishOne(bool succ){

        if(succ){
            succCount++;
        }else{
            failCount++;
        }

        if(canLoadError && succCount + failCount >= allCount){
            endSucc = true;
        }else if(succCount >= allCount){
            endSucc = true;
        }
    }

    public void log(string tag){
        //GDebug.Log($"<color=yellow>{tag}: allCount: {allCount} succCount:{ succCount} failCount:{ failCount}</color>");
    }

    public bool isEnd(){
        return allCount == 0 || endSucc;
    }

    public int getCount(){
        return allCount;
    }
}

