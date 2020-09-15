#include "head.h"

//启动（进行初始化）
void boot()
{
	bluetoothInit(); //通讯串口初始化（使用定时器1）

	//等待接收启动命令
	while (SBUF != 0x0b && press != 0)
		;
	oled_show_index();
	//自检
	while (xxZ == 1 || xxY == 1 || bzZ == 0 || bzY == 0)
	{
		if (xxZ == 1 || xxY == 1)
		{
			fmq(50);
			oled_cover_square(STATUS1, 1, xunxian);
			delayms(500);
			oled_cover_square(STATUS1, 1, emp);
		}
		if (bzZ == 0 || bzY == 0)
		{
			fmq(50);
			oled_cover_square(STATUS2, 1, bizhang);
			delayms(500);
			oled_cover_square(STATUS2, 1, emp);
		}
		delayms(500);
	}
	if (ENbz)
	{
		oled_cover_square(STATUS2, 1, bizhang);
	}
	if (ENxx)
	{
		oled_cover_square(STATUS1, 1, xunxian);
	}
	if (atoDrive)
	{
		oled_cover_square(STATUS3, 1, atoD);
	}
	if (atoGear)
	{
		oled_cover_square(STATUS4, 1, atoG);
	}

	fmq(500); //障碍、离地检测完毕

	//定时器初始化
	pwmInit0();	  //pwm调速定时器初始化(使用定时器0)
	Timer2Init(); //AI挂挡定时器初始化（使用定时器2）
	// fmq(500);//定时器初始化完毕

	gear = 0;
	gearShowRefresh();
}

void powerOff()
{
	ISP_CONTR = 0x20; //软件复位，重新开始执行程序
}

void press_detect()
{
	if (press == 0)
	{
		delayms(2000);
		if (press == 0)
		{
			powerOff();
		}
	}
}
