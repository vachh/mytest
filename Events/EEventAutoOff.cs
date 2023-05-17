using System;
using System.Collections.Generic;
using UnityEngine;

public class EEventAutoOff : MonoBehaviour
{  
    [Serializable]
    private struct EventData{
        public string eventName;
        public string objectName;
        public Action action;
    }

    [SerializeField] private List<EventData> actions;

    private void Awake() {
        actions = new List<EventData>();
    }

    private void OnDestroy() {
        clear();
    }

    private void add(string objectName, string eventName, Action action){
        actions.Add(new EventData(){
            objectName = objectName,
            eventName = eventName,
            action = action
        });
    }

    private void clear(){
        for (int i = 0; i < actions.Count; i++)
        {
            var data = actions[i];
            GDebug.Log($"{data.objectName} {data.eventName} Off");
            data.action.InvokeSafe();
        }
    }

    public static void TryClear(GameObject gameObject){
        var com = gameObject.GetComponent<EEventAutoOff>();
        if(com != null){
            com.clear();
        }
    }

    public static void Add(GameObject gameObject, string eventName, Action action)
    {
        var com = gameObject.GetComponent<EEventAutoOff>();
        if(com == null){
            com = gameObject.AddComponent<EEventAutoOff>();
        }
        com.add(gameObject.name, eventName, action);
    }
}
