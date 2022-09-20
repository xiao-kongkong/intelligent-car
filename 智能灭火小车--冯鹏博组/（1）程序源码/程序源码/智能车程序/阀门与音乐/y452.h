#ifndef   y452_H
#define   y452_H

 static unsigned char bf;//定义全局变量播放位置变量
 static unsigned char jp0;//定义全局变量播放时间单位化到0.03s
 static unsigned char jp1;//定义全局变量控制播放时间即节拍
sbit fmq = P2^0;

void ds1();

#endif