using System;
using System.Collections.Generic;
using UnityEngine;

public class EEvent : EEventBase<Action>
{
    private static EEvent instance;
    public static EEvent ins
    {
        get{
            if(instance == null)
                instance = new EEvent();
            return instance;
        }
    }

    private Type[] paramTypes = {};
    protected override Type[] GetParamTypes() => paramTypes;

    public void Send(EventType key)
    {
        send(key, action => action.InvokeSafe());
    }

    //直接调用，没有安全检测，用于性能优先
    public void SendQuick(EventType key)
    {
        send(key, action => action.Invoke());
    }
}

