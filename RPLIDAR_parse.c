/* 包含头文件 ----------------------------------------------------------------*/
#include "includes.h"

/* 变量定义 ------------------------------------------------------------------*/
/************************************************************  
雷达串口接收变量  
************************************************************/ 
u8 lidarCheckTable[2] = {0};//检验接收的前两位
u8 lidarDataTable[4] = {0};//雷达具体数据
u8 lidarDataCnt = 0;
u8 lidarOriginalData[4] = {0};
vu8 systickCnt = 0;
FlagStatus lidarCheckRightFlag = RESET;
FlagStatus lidarStartParseFlag = RESET;
distanceDataTypeDef distanceData;

/* 函数声明 ------------------------------------------------------------------*/
  
/************************************************************  
 * Function: start_parse_RPLIDAR  
 * Description: --  
 * Input parameter: void  
 * Return parameter: void  
 * Calls:  
 * Called by:  
 * Author: zilin Wang     Build_Date :2017/5/25    
 * Other:  
*************************************************************/  
   
void start_parse_RPLIDAR(void)  
{  
    distanceData.angle = ((((u16)lidarOriginalData[0]) >> 1) | (((u16)lidarOriginalData [1]) << 7)) / 64;
	distanceData.distance = (((u16)lidarOriginalData[2]) | (((u16)lidarOriginalData[3]) << 8)) / 4;  
}  


