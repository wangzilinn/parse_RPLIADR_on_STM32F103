/* 包含头文件 ----------------------------------------------------------------*/
#include "includes.h"
/* 变量定义 ------------------------------------------------------------------*/

/* 函数定义 ------------------------------------------------------------------*/
  
/************************************************************  
 * Function: LED_init  PC13
 * Description: LED指示灯定义  
 * Input parameter: void  
 * Return parameter: void  
 * Calls:  
 * Called by:  
 * Author: zilin Wang     Build_Date：2017/4/15 星期六    
 * Other:  
*************************************************************/  

void LED_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/************************************************************  
 * Function: Systick_init  
 * Description: 滴答定时器初始化  
 * Input parameter: void  
 * Return parameter: void  
 * Calls:  
 * Called by:  
 * Author: zilin Wang     Build_Date：2017/4/15 星期六    
 * Other:  
*************************************************************/  
   
void Systick_init(void)  
{  
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//9Mhz
    SysTick_Config(7200000); //定时100ms 
}  
/************************************************************  
* Function: Usart1_init  
* Description:   
* Input parameter: void  
* Return parameter: void  
* Calls:  
* Called by:  
* Author: zilin Wang     Build_Date??2017/3/22 ???    
* Other:  
*************************************************************/  

void Usart1_init(void)  
{  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_initStructure;
	GPIO_initStructure.GPIO_Pin = GPIO_Pin_9;//tx
	GPIO_initStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_initStructure);
	GPIO_initStructure.GPIO_Pin = GPIO_Pin_10;//rx
	GPIO_initStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_initStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//usart1
	NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitTypeDef USART_initStructure;
	USART_initStructure.USART_BaudRate = 115200;
	USART_initStructure.USART_WordLength = USART_WordLength_8b;
	USART_initStructure.USART_StopBits = USART_StopBits_1;
	USART_initStructure.USART_Parity = USART_Parity_No;
	USART_initStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_initStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_initStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1, USART_IT_RXNE);	
} 
/************************************************************  
 * Function: delay_ms  
 * Description: 延迟，毫秒单位  
 * Input parameter: u16 time  
 * Return parameter: void  
 * Calls:  
 * Called by:  
 * Author: zilin Wang     Build_Date：2017/4/23 星期日    
 * Other:  
*************************************************************/  
   
void delay_ms(u16 time)  
{  
   	while(time--)    
	{        
		u16 i=12000; 
		while(i--);        
	}   
}  
/************************************************************  
 * Function: Main  
 * Description: The main function
 * Calls:  
 * Author: zilin Wang      Build_Date：2017/3/25 星期六    
 * Others:  
************************************************************/  
void main(void)  
{  
	SystemInit();
	Usart1_init();
	LED_init();
	Systick_init();//1ms中断
	while(1)//延时2s Delaye 2S
	{
		if (systickCnt > 20)
			break;
	}
	//发送请求数据
	Usart_send_byte(USART1, 0xa5);  
	delay_ms(2);
	Usart_send_byte(USART1, 0x20);
    while(1)
    {  	
		if (lidarStartParseFlag == SET)
		{
			//start parse data
			start_parse_RPLIDAR();
			//distanceData.angle is lidar's angle
			//distanceData.distance is corresponded angles
			lidarStartParseFlag = RESET;			
		}		
    }
}  