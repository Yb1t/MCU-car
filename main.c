#include "head.h"

void main()
{
	data_init();
    oledInit();
	oled_show_sign();
	boot();
	while (1)
	{
		motoControl();
		route();
		press_detect();
	}
}