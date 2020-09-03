#include "head.h"

//延时ms
void delayms(uint ms)
{
    uint j;
    while (ms > 0)
    {
        for (j = 110; j > 0; j--)
            ; //for里面什么也不做，仅不断减1，一次114~0循环用时约1s
        ms--;
    }
}

//延时20us
void delay20us()
{ //晶振频率11.0592，一个周期1.085us，20个周期稍微比20us大
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
}

//清除数码管
void clean()
{
    a = b = c = d = e = f = g = 1;
}

//蜂鸣器
void fmq(uint ms)
{
    beep = ~beep;
    delayms(ms);
    beep = ~beep;
}
