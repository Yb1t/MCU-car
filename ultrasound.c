#include "head.h"

uint sendTime;     //发送时间
uint receiveTime;  //接收时间
uint distance = 0; //距离

//获取定时器2计时
uint getTime()
{
    uint time, timeTH2, timeTL2;
    timeTH2 = TH2;
    timeTL2 = TL2;
    timeTH2 <<= 8; //左移8位
    time = timeTH2 | timeTL2;
    return time;
}

//获取距离
uint getDistance()
{

    //控制端发送20us高电平
    TRIG = 1;
    delay20us();
    TRIG = 0;

    //等待接收端出现高电平
    while (!ECHO)
        ;
    //开始计时
    sendTime = getTime();

    //计时结束
    while (ECHO)
        ;
    receiveTime = getTime();

    
    return (receiveTime - sendTime) /59;
    //	Y m = （X s * 340） /2
    //  Y cm=(X us * 340*10^-6 m/us) / 2 * 100
    //  Y cm=X us * 0.017~=X/59
}
