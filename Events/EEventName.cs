
using System;
using System.Collections.Generic;

public static class EEventName
{
    private readonly static Type tInt = typeof(int);
    private readonly static Type tBool = typeof(bool);
    private readonly static Type tFloat = typeof(float);
    private readonly static Type tString = typeof(string);

    private readonly static Type[] arrEmpty = {};
    private readonly static Type[] arrInt = { tInt };
    private readonly static Type[] arrBool = { tBool };
    private readonly static Type[] arrFloat = { tFloat };
    private readonly static Type[] arrString = { tString };

    public readonly static EventType HideTestUI = EventType.Create(arrEmpty); //隐藏测试ui

    public readonly static EventType MyItemNotEnough = EventType.Create(new Type[]{typeof(MyItemType)}); //物品不够

    public readonly static EventType LevelPass = EventType.Create(arrEmpty); //升级了

    public readonly static EventType Battle_Pause = EventType.Create(arrBool); //游戏暂停
    public readonly static EventType Battle_CheckDeskCache = EventType.Create(arrEmpty); //检查桌子缓存
    public readonly static EventType Battle_ProductAdd = EventType.Create(new Type[]{tInt, tInt, tInt}); // 
    public readonly static EventType Battle_ProductDelete = EventType.Create(arrEmpty);
    public readonly static EventType Battle_equipBoxExpAddGM = EventType.Create(arrInt); //GM增加经验
    public readonly static EventType Battle_equipBoxExpAdd = EventType.Create(new Type[] {tInt, tInt}); //增加经验
    public readonly static EventType Battle_activeRefresh = EventType.Create(arrEmpty); //当前激活场景刷新

    public readonly static EventType IapInitSucc = EventType.Create(arrEmpty); //iap初始化成功
    public readonly static EventType IapBuyCallBack = EventType.Create(new Type[]{tBool, typeof(cfbt_stores)}); //商品购买

    public readonly static EventType RewardPopDestory = EventType.Create(arrEmpty); //充值界面关闭

    /////////////////////// login
    public readonly static EventType Guest_Login = EventType.Create(new Type[]{typeof(GuestLoginState)}); //游客登录
    public readonly static EventType LoginFinishReadData = EventType.Create(new Type[]{typeof(Dictionary<string, object>)}); //登录完成读取数据
    public readonly static EventType LoginOrDeleteAccount = EventType.Create(arrEmpty); //登录或删除账号刷新数据
    public readonly static EventType LogOutAccount = EventType.Create(arrEmpty); //退出登录


    public readonly static EventType OnTeacherFinishedClose = EventType.Create(arrInt);  //当引导关闭


    public readonly static EventType TopBarRefresh = EventType.Create(arrEmpty); //顶部状态栏刷新

    /////////////////////////
    public readonly static EventType Hero_EquipRefresh = EventType.Create(new Type[]{tInt, typeof(ProductData)}); //装备刷新
    public readonly static EventType Hero_equipAttachChange = EventType.Create(new Type[]{typeof(AttachData)}); //装备皮肤更新
    public readonly static EventType Hero_battleRoundRefresh = EventType.Create(arrInt); //战斗回合刷新

    public readonly static EventType Task_Refresh = EventType.Create(arrEmpty); //任务刷新
    public readonly static EventType Task_ProgressRefresh = EventType.Create(arrEmpty); //任务进度刷新

    public readonly static EventType FightNumChanged = EventType.Create(arrBool); //战斗力改变
}
