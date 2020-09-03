#include "head.h"

uint count3 = 0;

uint key; //蓝牙接收到的键值

//通讯串口初始化配置（使用计数器1）
void bluetoothInit()
{
    TMOD = 0x22; //0010 0010，两个8位自动重载

    //设置计数器1的初值，决定波特率
    TH1 = 0xfd;
    TL1 = 0xfd;

    ET1 = 0;     //!!!关键，T1中断（函数）禁止
    PCON = 0x00; //波特率倍增0x00不加倍	 0x80加倍
    SCON = 0x50; //设置工作方式1 开启接受允许
    EA = 1;      //开启总中断
    ES = 1;      //开启串口接受、发送中断
    TR1 = 1;     //计数器1开始运行
}

//串口中断(TI发送标志位，RI接受标志位)
void UART() interrupt 4
{

    //	count3++;
    //	if(count3==10000&&TI)
    //	{
    //		count3=0;
    //		SBUF=distance;
    //      while(!TI);
    //		TI=0;
    //	}

    if (RI)
    {
        key = SBUF;
        switch (key)
        {
        case 0x00:
            forward();
            break;
        case 0x01:
            back();
            break;
        case 0x02:
            left();
            break;
        case 0x03:
            right();
            break;
        case 0x04:
            stop();
            break;
        case 0x05:
            atoDrive = 0; //进入手动驾驶
            oled_cover_square(STATUS3, 1, emp);
            stop();
            break;
        case 0x06:
            atoDrive = 1; //进入自动驾驶
            oled_cover_square(STATUS3, 1, atoD);
            break;
        case 0x07:
            gearSwitch(gear + 1);
            break;
        case 0x08:
            gearSwitch(gear - 1);
            break;
        case 0x09:
            beep = ~beep;
            break;
        case 0x10:
            ENbz = 0;
            oled_cover_square(STATUS2, 1, emp);
            break;
        case 0x11:
            ENbz = 1;
            oled_cover_square(STATUS2, 1, bizhang);
            break;
        case 0x12:
            ENxx = 0;
            oled_cover_square(STATUS1, 1, emp);
            break;
        case 0x13:
            ENxx = 1;
            oled_cover_square(STATUS1, 1, xunxian);
            break;
        case 0x14:
            atoGear = 0;
            oled_cover_square(STATUS4, 1, emp);
            break;
        case 0x15:
            atoGear = 1;
            oled_cover_square(STATUS4, 1, atoG);
            break;
        case 0x0a:
            powerOff();
            break;
        case 0x0b:
            //启动
            break;
        case 0x0c:
            distance = getDistance();
            SBUF = distance;
            while (!TI)
                ;
            TI = 0;
            break;
        case 'h':
            distance = getDistance();
            TI = 1;
            printf("Distance:%d\n", distance);
            while (!TI)
                ;
            TI = 0;
            break;

        default:
            break;
        }
        while (!RI)
            ;
        RI = 0;
    }
}
