using System;
using System.Collections.Generic;
using UnityEngine;

public static class GDebug
{

#if !UNITY_EDITOR
    [System.Diagnostics.Conditional("TEST")]
#endif
    public static void Log(string str)
    {
        UnityEngine.Debug.Log($"{getFrameCount()}{str}");
    }

#if !UNITY_EDITOR
    [System.Diagnostics.Conditional("TEST")]
#endif
    public static void Log(object obj)
    {
        Log(obj.ToString());
    }

#if !UNITY_EDITOR
    [System.Diagnostics.Conditional("TEST")]
#endif
    public static void LogFormat(string str, params object[] args)
    {
        UnityEngine.Debug.LogFormat($"{getFrameCount()}{str}", args);
    }

#if !UNITY_EDITOR
    [System.Diagnostics.Conditional("TEST")]
#endif
    public static void LogY(string str)
    {
        UnityEngine.Debug.Log($"{getFrameCount()}<color=yellow>{str}</color>");
    }
#if !UNITY_EDITOR
    [System.Diagnostics.Conditional("TEST")]
#endif
    public static void LogY(object obj)
    {
        LogY(obj.ToString());
    }

#if !UNITY_EDITOR
    [System.Diagnostics.Conditional("TEST")]
#endif
    public static void LogE(string str)
    {
        UnityEngine.Debug.LogError($"{getFrameCount()}{str} {OutputCallStack("red")}");
    }
#if !UNITY_EDITOR
    [System.Diagnostics.Conditional("TEST")]
#endif
    public static void LogE(object obj)
    {
        LogE(obj.ToString());
    }

    public static void LogError(string str)
    {
        UnityEngine.Debug.LogError($"{getFrameCount()}{str} {OutputCallStack("red")}");
    }

    public static void LogError(object obj)
    {
        LogError(obj.ToString());
    }

    public static string GetColorString(object str, string color = "yellow"){
        return $"<color={color}>{str.ToString()}</color> ";
    }

    public static string OutputCallStack(string color = "yellow")
    {

#if UNITY_EDITOR || TEST
        //如果为 true，则捕获文件名、行号和列号；否则为 false。
        //调用GetFrame得到栈空间
        System.Diagnostics.StackTrace stack = new System.Diagnostics.StackTrace(true);
        System.Diagnostics.StackFrame[] stackFrames = stack.GetFrames();

        if(stackFrames != null && stackFrames.Length > 0){
            var frame = stackFrames[stackFrames.Length - 1];
            var file = System.IO.Path.GetFileName(frame.GetFileName());
            return GetColorString($"[ at {file}, line {frame.GetFileLineNumber()} ]", color); 
        }
#endif
        return "";
    }

    private static string getFrameCount(){
        // Time.frameCount 只能在主线程调用
        if(IsMainThread)
            return $"<color=yellow>[{Time.frameCount}]</color> ";
        return "<color=yellow>[child_thread]</color> ";
    }

    private static int mainThreadId = System.Threading.Thread.CurrentThread.ManagedThreadId;
    public static bool IsMainThread => System.Threading.Thread.CurrentThread.ManagedThreadId == mainThreadId;
}

