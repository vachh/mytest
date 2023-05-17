using System;
using System.Collections.Generic;
using UnityEngine;

public class EEvent<T1> : EEventBase<Action<T1>>
{
    //静态变量，在泛型的不同类型中，不共享值
    private static EEvent<T1> instance;
    public static EEvent<T1> ins
    {
        get{
            if(instance == null)
                instance = new EEvent<T1>();
            return instance;
        }
    }

    private Type[] paramTypes = { typeof(T1) };
    protected override Type[] GetParamTypes() => paramTypes;
    
    public void Send(EventType key, T1 param)
    {
        send(key, action => action.InvokeSafe(param));
    }

    //直接调用，没有安全检测，用于性能优先
    public void SendQuick(EventType key, T1 param)
    {
        send(key, action => action.Invoke(param));
    }
}