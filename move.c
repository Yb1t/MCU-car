#include "head.h"

bit ENbz = 0;
bit ENxx = 0;

//运动导向
//（障0无1）（黑1白0）
void route()
{
    if (xxZ == 0 || xxY == 0)
    {
        //左右白（在地面）
        EA = 1;
        if (atoDrive)
        {
            if (ENbz == 1)
            {
                //含三种有障碍的情况
                //左边障碍
                if (bzZ == 0 && bzY == 1)
                {
                    right();
                }
                //右边障碍
                else if (bzZ == 1 && bzY == 0)
                {
                    left();
                }
                //前方障碍
                else if (bzZ == 0 && bzY == 0)
                {
                    //禁用中断(pwm)，全速进行
                    EA = 0;        //总中断禁止
                    ENA = ENB = 1; //左右电机允许
                    //后退200ms
                    back();
                    delayms(200);
                    //右转150ms
                    right();
                    delayms(150);
                    EA = 1; //总中断允许
                }
            }
            //无障碍，才开始直行、巡线
            if (bzZ == 1 && bzY == 1)
            {
                if (ENxx == 1)
                {
                    //左右白
                    if (xxZ == 0 && xxY == 0)
                    {
                        forward();
                    }
                    //左黑
                    else if (xxZ == 1 && xxY == 0)
                    {
                        left();
                    }
                    //右黑
                    else if (xxZ == 0 && xxY == 1)
                    {
                        right();
                    }
                }
                else if (ENxx == 0)
                {
                    forward();
                }
            }
        }
    }
    //左右黑(离开地面)
    else
    {
        EA = 0;
        gearSwitch(0);
        stop();
    }
}

//前进
void forward()
{
    L1 = 0;
    L2 = 1;
    R1 = 0;
    R2 = 1;
}

//后退
void back()
{
    L1 = 1;
    L2 = 0;
    R1 = 1;
    R2 = 0;
}

//左转
void left()
{
    L1 = 1;
    L2 = 0;
    R1 = 0;
    R2 = 1;
}

//右转
void right()
{
    L1 = 0;
    L2 = 1;
    R1 = 1;
    R2 = 0;
}

//停止
void stop()
{
    L1 = 0;
    L2 = 0;
    R1 = 0;
    R2 = 0;
}
