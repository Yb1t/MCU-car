#include "head.h"

uint count = 0;   //定时器中断次数计数
uint zkbZ = 0;    //左占空比初值,占空比越高，电机越快
uint zkbY = 0;    //右占空比初值
uint pwmT = 100;  //一个周期计数
uint correct = 10; //左右轮校正值（=左占空比-右占空比）
//注意：尽量使用正值，否则当满档为占空比100%时，zkbY = zkbZ - correct的值大于100，校正不起作用！

//定时器0初始化
void pwmInit0()
{
    TMOD = 0x22; //0000 0010,定时器0：8位自动重载

    //装初值，定时200us，200/1.085~=184，256-184=72
    TH0 = 72;
    TL0 = 72;

    EA = 1;  //总中断允许
    ET0 = 1; //定时器T0中断允许
    TR0 = 1; //打开定时器0，开始计时
}

//中断函数
void pwmConfig0() interrupt 1 //中断号根据中断源确定（注意优先级）
{
    //控制count在0~pwmT
    count++;
    if (count > pwmT)
        count = 0;
}

void motoControl()
{
    //左调速
    if (count < zkbZ)
    {
        ENA = 1;
    }
    else
    {
        ENA = 0;
    }
    //右调速
    if (count < zkbY)
    {
        ENB = 1;
    }
    else
    {
        ENB = 0;
    }
}