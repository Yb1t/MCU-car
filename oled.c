#include "head.h"

void oled_show_sign()
{
	oled_clear();
	
	oled_cover_square(32,0,4,bigBenz);
}

void oled_show_index()
{
	oled_clear();
	
    // oled_cover_square(STATUS1, 1, xunxian);
    // oled_cover_square(STATUS2, 1, bizhang);
    // oled_cover_square(STATUS3, 1, atoD);
    // oled_cover_square(STATUS4, 1, atoG);
    oled_cover_square(STATUS5, 1, bluetooth);
    oled_cover_square(STATUS6, 1, power);

    oled_cover_square(48, 2, 2, benz);

    oled_cover_square(32 - 8, 6, 1, zen);
    oled_cover_square(48 - 8, 6, 1, me);
    oled_cover_square(64 - 8, 6, 1, zuo);
    oled_cover_square(80 - 8, 6, 1, dou);
    oled_cover_square(96 - 8, 6, 1, dui);
}

//起始信号
void I2C_start()
{
    SDA = 1;
    SCL = 1;
    SDA = 0;
    SCL = 0;
}

//终止信号
void I2C_stop()
{
    SDA = 0;
    SCL = 1;
    SDA = 1;
}

// iic发送单字节
void I2C_send_byte(uchar dat)
{
    uchar a = 0, b = 0;
    for (a = 0; a < 8; a++)//要发送8位，从最高位开始
    {
        dat <<= 1;
        SDA = CY; //起始信号之后SCL=0，所以可以直接改变SDA信号
        SCL = 1;
        SCL = 0;
    }
    SDA = 1;
    SCL = 1;
    SCL = 0;
}

//写使能函数
void oled_send_cmd(uchar cmd)
{
    I2C_start();
    I2C_send_byte(0x78); //发送写器件地址
    I2C_send_byte(0x00); //发送要写入内存地址
    I2C_send_byte(cmd);  //写入命令
    I2C_stop();
}

//写字节函数
void oled_send_data(uchar dat)
{
    I2C_start();
    I2C_send_byte(0x78); //发送写器件地址
    I2C_send_byte(0x40); //发送要写入内存地址
    I2C_send_byte(dat);  //写入数据
    I2C_stop();
}

//清屏函数
void oled_clear()
{
    uchar i, j;
    for (i = 0; i < 8; i++)
    {
        //设置坐标
        oled_send_cmd(0xb0 + i);
        oled_send_cmd(0x10);
        oled_send_cmd(0x00);
        for (j = 0; j < 128; j++)
        {
            oled_send_data(0x00);
        }
    }
}

//设置起始位置
void oled_setpos(uchar x, uchar y)
{
    //设置起始页
    oled_send_cmd(0xb0 + y);
    //设置起始列
    oled_send_cmd(x & 0x0f);                 //低位（x & 0x0f：起到取低四位的作用）
    oled_send_cmd(((x & 0xf0) >> 4) | 0x10); //高位（x & 0xf0：同理取高四位）
}

void oled_cover_square(uchar x0, uchar yPage0, uchar size, uchar BMP[])
{ //传入开始坐标x，坐标y的页，将覆盖的大小（size*16个像素点），将覆盖的数据，要求将覆盖的区域为正方形
    uint i = 0;
    uchar x, x1, yPage, yPage1;
    x1 = x0 + size * 16;
    yPage1 = yPage0 - 1 + size * 2;
    for (yPage = yPage0; yPage <= yPage1; yPage++)
    {
        oled_setpos(x0, yPage);
        for (x = x0; x < x1; x++)
        {
            oled_send_data(BMP[i++]);
        }
    }
}


// 初始化oled
void oledInit()
{
    //关闭显示
    oled_send_cmd(0xae); //--turn off oled panel
    //设置起始列
    oled_send_cmd(0x00); //---set low column address设置起始列的低四位 0x0x
    oled_send_cmd(0x10); //---set high column address设置起始列的高四位0x1x
    //设置起始行
    oled_send_cmd(0x40); //--set start line address Set Mapping RAM Display Start Line (0x00~0x3F)
    //设置对比度
    oled_send_cmd(0x81); //--set contrast control register
    oled_send_cmd(0xff); // Set SEG Output Current Brightness对比度为oxff
    //左右反置 0xa1正常
    oled_send_cmd(0xa1); //--Set SEG/Column Mapping 0xa0
    //上下反置 0xc8正常
    oled_send_cmd(0xc8); //Set COM/Row Scan Direction 0xc0
    //设置复用率
    oled_send_cmd(0xa8); //--set multiplex ratio(1 to 64)
    oled_send_cmd(0x3f); //--1/64 duty
    //设置显示偏移
    oled_send_cmd(0xd3); //-set display offset Shift Mapping RAM Counter (0x00~0x3F)
    oled_send_cmd(0x00); //-not offset
    //设置显示时钟分频率、振荡器频率
    oled_send_cmd(0xd5); //--set display clock divide ratio/oscillator frequency
    oled_send_cmd(0x80); //--set divide ratio, Set Clock as 100 Frames/Sec
    //设置重充电周期
    oled_send_cmd(0xd9); //--set pre-charge period
    oled_send_cmd(0xf1); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    //设置COM引脚硬件配置
    oled_send_cmd(0xda); //--set com pins hardware configuration
    oled_send_cmd(0x12);
    //设置 Vcomh 取消选择水平
    oled_send_cmd(0xdb); //--set vcomh
    oled_send_cmd(0x20); //Set VCOM Deselect Level
    //设置内存地址模式
    oled_send_cmd(0x20); //-Set Page Addressing Mode (0x00/0x01/0x02)设置地址模式
    oled_send_cmd(0x02); // 地址模式为页寻址
    //电荷泵设置
    oled_send_cmd(0x8d); //-- set Charge Pump enable / disable (0x14 / 0x10)
    oled_send_cmd(0x14); //--set(0x10) disable
    //整体显示开启状态(0xa4输出依据GDDRAM中的内容/0xa5不管显示数据RAM中的内容)
    oled_send_cmd(0xa4); // Disable Entire Display On
    //设置正常/反相显示 (0xa6/a7)
    oled_send_cmd(0xa6); // Disable Inverse Display On
    //开启显示
    oled_send_cmd(0xaf); //--turn on oled panel

    oled_clear(); //清屏
}
