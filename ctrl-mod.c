#include "head.h"

//控制模式切换
//0x05手动 0x06自动
void ctrlModSwitch(uint mod)
{
    switch (mod)
    {
    case 0x05://手动
        blutoothInit();  //通讯串口初始化配置（使用计数器1）

        break;
    case 0x06://自动
        speedTimerInit(); //AI挂挡定时器初始化（使用计数器1）

        break;
    default:
        break;
    }
}