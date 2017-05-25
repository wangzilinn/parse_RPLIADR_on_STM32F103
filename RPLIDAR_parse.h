#ifndef __RPLIDAR_PARSE_H
#define __RPLIDAR_PARSE_H
/* 包含头文件 ----------------------------------------------------------------*/
#include "includes.h"
/* 变量声明 ------------------------------------------------------------------*/
/************************************************************  
雷达串口接收变量  
************************************************************/ 
extern u8 lidarCheckTable[2];//检验接收的前两位
extern u8 lidarDataTable[4];//雷达具体数据
extern u8 lidarDataCnt;
extern u8 lidarOriginalData[4];
extern vu8 systickCnt;
extern FlagStatus lidarCheckRightFlag;
extern FlagStatus lidarStartParseFlag;
typedef struct 
{
	u16 angle;
	u16 distance;
}distanceDataTypeDef;
extern distanceDataTypeDef distanceData;
/* 函数声明 ------------------------------------------------------------------*/
extern void start_parse_RPLIDAR();
#endif