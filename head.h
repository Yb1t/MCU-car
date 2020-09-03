#ifndef __HEAD_H__ //防止重复定义
#define __HEAD_H__

#define uint unsigned int
#define uchar unsigned char

#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include "character.h"

//数据初始化/装载
void data_init();

//运动

//左轮
sbit L1 = P1 ^ 0;
sbit L2 = P1 ^ 1;

//右轮
sbit R1 = P1 ^ 2;
sbit R2 = P1 ^ 3;

sbit bzZ = P3 ^ 4; //避障左
sbit bzY = P3 ^ 5; //避障右
sbit xxZ = P3 ^ 7; //巡线左
sbit xxY = P3 ^ 6; //巡线右
extern bit ENbz;   //避障开关
extern bit ENxx;   //巡线开关
void forward();    //前进
void back();       //后退
void left();       //左转
void right();      //右转
void stop();       //停止
void route();      //运动导向

//数码管
sbit a = P0 ^ 7;
sbit b = P0 ^ 6;
sbit c = P0 ^ 5;
sbit d = P0 ^ 4;
sbit e = P0 ^ 3;
sbit f = P0 ^ 2;
sbit g = P0 ^ 1;
#define NUM0 a = b = c = d = e = f = 0
#define NUM1 b = c = 0
#define NUM2 a = b = d = e = g = 0
#define NUM3 a = b = c = d = g = 0
#define NUM4 f = g = b = c = 0
#define NUM5 a = f = g = c = d = 0
void countDown();       //倒计时
void gearShowRefresh(); //挡位显示刷新

//pwm调速
sbit ENA = P1 ^ 4;    //左电机使能
sbit ENB = P1 ^ 5;    //右电机使能
extern uint count;    //计数
extern uint zkbZ;     //左占空比（上限为pwmT）,占空比越高，电机越快
extern uint zkbY;     //右占空比（上限为pwmT）
extern uint zkb1Gear; //1档占空比
extern uint correct;  //左右轮校正值（=左占空比-右占空比）
extern uint pwmT;     //一个周期计数
void pwmInit0();      //计时器0初始化
void Time0Config();   //计时器0配置
void motoControl();   //电机使能控制

//定时器2
extern uint count2; //定时器2计数
extern uint line;   //碰线计数
extern uint gear;   //挡位
extern uint level;
extern bit atoDrive;          //自动驾驶开关
extern bit atoGear;           //自动档开关
void Timer2Init();            //AI挂挡定时器初始化（使用定时器1）
void Time2Config();           //定时器1进入中断
void gearSwitch(uint signal); //挂档
uint getTime();               //获取定时器2计时
uint getDistance();           //获取距离

//工具箱
sbit beep = P2 ^ 3;        //蜂鸣器
void fmq(uint ms);         //蜂鸣器
void delayms(uint minute); //延时
void delay20us();          //延迟20us
void clean();              //清除数码管

//蓝牙
void bluetoothInit(); //通讯串口初始化配置（使用计数器1）
void UART();          //串口中断

//电源管理
sbit press=P3^2;
sfr ISP_CONTR = 0xe7;
void boot();
void powerOff();

//超声波
sbit TRIG = P2 ^ 0; //超声波控制端
sbit ECHO = P2 ^ 1; //超声波接收端
extern uint distance;

//OLED显示屏
sbit SCL = P2 ^ 4;
sbit SDA = P2 ^ 5;
#define STATUS1 16,0
#define STATUS2 32,0
#define STATUS3 48,0
#define STATUS4 64,0
#define STATUS5 80,0
#define STATUS6 96,0
void I2C_start();
void I2C_stop();
void I2C_send_byte(uchar dat);
void oled_send_cmd(uchar cmd);
void oled_send_data(uchar dat);
void oled_clear();
void oledInit();
void oled_show_index();
void delay(uchar i);
void oled_setpos(uchar x, uchar y);
void oled_cover_square(uchar x0, uchar y0, uchar size, uchar BMP[]);
void oled_show_sign();


#endif
