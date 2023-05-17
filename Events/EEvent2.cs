using System;
using System.Collections.Generic;
using UnityEngine;

public class EEvent<T1, T2> : EEventBase<Action<T1, T2>>
{
    private static EEvent<T1, T2> instance;
    public static EEvent<T1, T2> ins
    {
        get{
            if(instance == null)
                instance = new EEvent<T1, T2>();
            return instance;
        }
    }

    private Type[] paramTypes = { typeof(T1), typeof(T2)};
    protected override Type[] GetParamTypes() => paramTypes;

    public void Send(EventType key, T1 param1, T2 param2)
    {
        send(key, action => action.InvokeSafe(param1, param2));
    }

    //直接调用，没有安全检测，用于性能优先
    public void SendQuick(EventType key, T1 param1, T2 param2)
    {
        send(key, action => action.Invoke(param1, param2));
    }
}