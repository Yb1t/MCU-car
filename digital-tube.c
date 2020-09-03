#include "head.h"

//倒计时3s
void countDown()
{
	//3
	NUM3;
	delayms(1000);
	clean();

	//2
	NUM2;
	delayms(1000);
	clean();

	//1
	NUM1;
	delayms(1000);
	clean();

	//0
	NUM0;
	delayms(1000);
	clean();
}

//挡位显示
void gearShowRefresh()
{
	clean();
	switch (gear)
	{
	case 0:
		NUM0;
		break;
	case 1:
		NUM1;
		break;
	case 2:
		NUM2;
		break;
	case 3:
		NUM3;
		break;
	case 4:
		NUM4;
		break;
	case 5:
		NUM5;
		break;
	}
}
