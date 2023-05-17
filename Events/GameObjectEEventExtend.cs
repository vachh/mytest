using System;
using System.Collections.Generic;
using UnityEngine;

public static class GameObjectEEventExtend{
    public static void EEventClear(this GameObject gameObject)
    {
        EEventAutoOff.TryClear(gameObject);
    }

    public static void EEventOn(this GameObject gameObject, EventType eventName, Action action )
    {
        EEvent.ins.On(eventName, action, gameObject);
    }

    public static void EEventOn<T1>(this GameObject gameObject, EventType eventName, Action<T1> action )
    {
        EEvent<T1>.ins.On(eventName, action, gameObject);
    }

    public static void EEventOn<T1, T2>(this GameObject gameObject, EventType eventName, Action<T1, T2> action )
    {
        EEvent<T1, T2>.ins.On(eventName, action, gameObject);
    }

    public static void EEventOn<T1, T2, T3>(this GameObject gameObject, EventType eventName, Action<T1, T2, T3> action )
    {
        EEvent<T1, T2, T3>.ins.On(eventName, action, gameObject);
    }
}

