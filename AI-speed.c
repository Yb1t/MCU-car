#include "head.h"
uint count2 = 0;    //计时器2计数
uint line = 0;      //碰线计数
uint gear = 0;      //挡位
uint zkb1Gear = 50; //1档占空比
uint level;         //1档后占空比分级
bit atoDrive = 0;   //自动驾驶开关
bit atoGear = 0;    //自动档开关

//AI挂挡定时器初始化（使用定时器2）
void Timer2Init()
{
    //    T2CON = 0x00;//开机默认为0

    //初值50ms,50000/1.085~=46083,65536-46083=19453
    TH2 = 0x4b;
    TL2 = 0xfd;

    EA = 1;
    ET2 = 1;
    TR2 = 1;
}

//定时器2进入中断
void Time2Config() interrupt 5
{
    TF2 = 0; //定时器2需要软件复位溢出位

    //执行自动档识别切换
    if (atoGear)
    {
        count2++;

        //每50ms
        //碰线计数
        if (xxZ == 1 || xxY == 1)
        {
            line = 15;
        }
        else if (xxZ == 0 && xxY == 0 && line > 0)
        {
            line--;
        }

        //每1s(50ms*20)
        if (count2 >= 20)
        {
            //刷新距离
            distance = getDistance();
            //减1档
            if (gear > 1 && (line > 0 || distance < 200))
            {
                gearSwitch(gear - 1);
            }
            //加1档
            else if (line == 0 && distance > 200)
            {
                gearSwitch(gear + 1);
            }
            count2 = 0;
        }
    }
}

//挂档
void gearSwitch(uint signal)
{
    if (signal >= 0 && signal <= 5)
    {
        if (signal == 0)
        {
            zkbZ = zkbY = 0;
        }
        else
        {
            zkbZ = zkb1Gear + level * (signal - 1);
            zkbY = zkbZ - correct;
        }
        gear = signal;
        gearShowRefresh();
    }
}