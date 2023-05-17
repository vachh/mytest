using System.IO;
using System;
using System.Collections.Generic;
using System.Text;
using UnityEngine;

public class EventType
{
    public Type[] types;
    private EventType(Type[] types)
    {
        this.types = types;
    }

    public static EventType Create(Type[] types)
    {
        var eventData = new EventType(types);
        return eventData;
    }
}

public abstract class EEventBase<TAction> where TAction : System.Delegate
{
    protected abstract Type[] GetParamTypes();
    private Dictionary<EventType, List<TAction>> saveActions = new Dictionary<EventType, List<TAction>>();

    public void On(EventType key, TAction action, GameObject gameObject = null)
    {   
        if(!checkType(key))
            return;
        var addTag = false;
        if (!saveActions.ContainsKey (key)) {
            saveActions[key] = new List<TAction> {action};
            addTag = true;
        }else if (saveActions[key].IndexOf(action) == -1){
            saveActions[key].Add (action);
            addTag = true;
        }

        if(addTag && gameObject != null){
            EEventAutoOff.Add(gameObject, key.ToString(), ()=>{
                Off(key, action);
            });
        }
    }

    public void Off(EventType key, TAction action)
    { 
        if (!saveActions.ContainsKey(key))
            return;
        saveActions[key].Remove(action);
        if (saveActions[key].Count == 0)
            saveActions.Remove (key);
    }

    protected void send(EventType key, Action<TAction> invokeAction)
    {
        if(!checkType(key))
            return;
        if (!saveActions.ContainsKey(key))
            return;

        var actionList = saveActions[key];
        for (var i = 0; i < actionList.Count; ++i){
            var action = actionList[i];
            invokeAction.Invoke(action);
        }
    }

    private bool checkType(EventType eventType)
    {
        var paramTypes = GetParamTypes();
        var needTypes = eventType.types;

        if (needTypes.Length != paramTypes.Length)
        {
            GDebug.LogError($"EventType count error, needType count: {GDebug.GetColorString(needTypes.Length)}, paramType count: {GDebug.GetColorString(paramTypes.Length)}");
            return false;
        }

        for (int i = 0; i < needTypes.Length; i++)
        {
            if (needTypes[i] != paramTypes[i])
            {
                GDebug.LogError($"EventType type error, needType: {GDebug.GetColorString(needTypes[i])}, paramType: {GDebug.GetColorString(paramTypes[i])}");
                return false;
            }
        }

        return true;
    }
}

