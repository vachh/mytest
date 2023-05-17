using System;
using System.Collections.Generic;
using UnityEngine;

public class EEvent<T1, T2, T3> : EEventBase<Action<T1, T2, T3>>
{
    private static EEvent<T1, T2, T3> instance;
    public static EEvent<T1, T2, T3> ins
    {
        get{
            if(instance == null)
                instance = new EEvent<T1, T2, T3>();
            return instance;
        }
    }

    private Type[] paramTypes = { typeof(T1), typeof(T2), typeof(T3)};
    protected override Type[] GetParamTypes() => paramTypes;

    public void Send(EventType key, T1 param1, T2 param2, T3 param3)
    {
        send(key, action => action.InvokeSafe(param1, param2, param3));
    }

    //直接调用，没有安全检测，用于性能优先
    public void SendQuick(EventType key, T1 param1, T2 param2, T3 param3)
    {
        send(key, action => action.Invoke(param1, param2, param3));
    }
}