//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它商业用途
//测试硬件：单片机STM32F103C8T6,F103C8T6核心开发板,主频72MHZ，晶振8MHZ
//QDtech-TFT液晶驱动 for STM32 IO模拟
//Chan@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//wiki技术资料网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-21077707 
//手机: (销售)18823372746 （技术)15989313508
//邮箱:(销售/订单) sales@qdtft.com  (售后/技术服务)service@qdtft.com
//QQ:(售前咨询)3002706772 (技术支持)3002778157
//技术交流QQ群:778679828
//创建日期:2020/05/07
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                STM32单片机
//      VCC          接          3.3V         //电源
//      GND          接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为4线制SPI总线
//     LCD模块                STM32单片机    
//       SDA         接          PA7         //液晶屏SPI总线数据写信号
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 					      STM32单片机 
//       BLK         接          PB6          //液晶屏背光控制信号，如果不需要控制，接3.3V
//       SCK         接          PA5         //液晶屏SPI总线时钟信号
//       DC          接          PB7         //液晶屏数据/命令控制信号
//       RES         接          PB8         //液晶屏复位控制信号
//       CS          接          PB9         //液晶屏片选控制信号
//=========================================触摸屏触接线=========================================//
//模块不带触摸功能，不需要进行触摸屏接线
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/	
#ifndef __LCD_H
#define __LCD_H		
//#include "sys.h"	 
//#include "stdlib.h"
#include "main.h"
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
//LCD重要参数集

typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				  //LCD ID
	u8  dir;			  //横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	 wramcmd;		//开始写gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令	
}_lcd_dev; 	

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数
/////////////////////////////////////用户配置区///////////////////////////////////	 
#define USE_HORIZONTAL  	 0 //定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转

//////////////////////////////////////////////////////////////////////////////////	  
//定义LCD的尺寸
//#define LCD_W 240		//TFT 2.0
//#define LCD_H 320

//#define LCD_W 240		//TFT 1.3
//#define LCD_H 240

#define LCD_W 135		//TFT 1.14
#define LCD_H 240

//#define LCD_W 80		//TFT 0.96
//#define LCD_H 160

//TFTLCD部分外要调用的函数		   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

////////////////////////////////////////////////////////////////////
//-----------------示例教程LCD端口定义---------------- 
//#define GPIO_TYPE  GPIOB  //GPIO组类型
//#define LED      6        //背光控制引脚       PB6
//#define LCD_CS   9       //片选引脚            PB9
//#define LCD_RS   7       //寄存器/数据选择引脚 PB7 
//#define LCD_RST  8       //复位引脚            PB8

//------------Flash Power Recorder LCD端口定义----------- 
//#define GPIO_TYPE  GPIOB  //GPIO组类型
//#define LED      A15        //背光控制引脚       PB6
//#define LCD_CS   B7       //片选引脚            PB9
//#define LCD_RS   B6       //寄存器/数据选择引脚 PB7 
//#define LCD_RST  B4       //复位引脚            PB8


//QDtech全系列模块采用了三极管控制背光亮灭，用户也可以接PWM调节背光亮度
#define	LCD_LED_On  HAL_GPIO_WritePin(TFT_SW_GPIO_Port,TFT_SW_Pin,GPIO_PIN_SET)//LCD背光    		 PB6
#define	LCD_LED_Off  HAL_GPIO_WritePin(TFT_SW_GPIO_Port,TFT_SW_Pin,GPIO_PIN_RESET)//LCD背光
//#define	LCD_LED PBout(LED) //LCD背光    		 PB6
//如果使用官方库函数定义下列底层，速度将会下降到14帧每秒，建议采用我司推荐方法
//以下IO定义直接操作寄存器，快速IO操作，刷屏速率可以达到28帧每秒！ 

////GPIO置位（拉高）
//#define	LCD_CS_SET  GPIO_TYPE->BSRR=1<<LCD_CS    //片选端口  	
//#define	LCD_RS_SET	GPIO_TYPE->BSRR=1<<LCD_RS    //数据/命令  	  
//#define	LCD_RST_SET	GPIO_TYPE->BSRR=1<<LCD_RST   //复位			  

////GPIO复位（拉低）							    
//#define	LCD_CS_CLR  GPIO_TYPE->BRR=1<<LCD_CS     //片选端口  	
//#define	LCD_RS_CLR	GPIO_TYPE->BRR=1<<LCD_RS     //数据/命令  	 
//#define	LCD_RST_CLR	GPIO_TYPE->BRR=1<<LCD_RST    //复位		

//GPIO置位（拉高）
#define	LCD_CS_SET  HAL_GPIO_WritePin(TFT_CS_GPIO_Port,TFT_CS_Pin,GPIO_PIN_SET)   //片选端口  	
#define	LCD_RS_SET	HAL_GPIO_WritePin(TFT_RS_GPIO_Port,TFT_RS_Pin,GPIO_PIN_SET)    //数据/命令  	  
#define	LCD_RST_SET	HAL_GPIO_WritePin(TFT_RES_GPIO_Port,TFT_RES_Pin,GPIO_PIN_SET)   //复位			  

//GPIO复位（拉低）							    
#define	LCD_CS_CLR  HAL_GPIO_WritePin(TFT_CS_GPIO_Port,TFT_CS_Pin,GPIO_PIN_RESET)     //片选端口  	
#define	LCD_RS_CLR	HAL_GPIO_WritePin(TFT_RS_GPIO_Port,TFT_RS_Pin,GPIO_PIN_RESET)     //数据/命令  	 
#define	LCD_RST_CLR	HAL_GPIO_WritePin(TFT_RES_GPIO_Port,TFT_RES_Pin,GPIO_PIN_RESET)    //复位	

//画笔颜色
#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0XF81F
#define GRED 			 	0XFFE0
#define GBLUE			 	0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 			0XBC40 //棕色
#define BRRED 			0XFC07 //棕红色
#define GRAY  			0X8430 //灰色
#define GRAY0       0xEF7D 
#define GRAY1       0x8410      	//灰色1      00000 000000 00000
#define GRAY2       0x4208 
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 		0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE      	0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)
	    															  
void LCD_Init(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(u16 Color);	 
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_DrawPoint(u16 x,u16 y);//画点
u16  LCD_ReadPoint(u16 x,u16 y); //读点
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);

u16 LCD_RD_DATA(void);//读取LCD数据									    
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
void LCD_WR_DATA(u8 data);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);		   
u16 LCD_BGR2RGB(u16 c);
void LCD_SetParam(void);
void Lcd_WriteData_16Bit(u16 Data);
void LCD_direction(u8 direction );

//如果仍然觉得速度不够快，可以使用下面的宏定义,提高速度.
//注意要去掉lcd.c中void LCD_WR_DATA(u16 data)函数定义哦
/*
#if LCD_USE8BIT_MODEL==1//使用8位并行数据总线模式
	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	DATAOUT(data<<8);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	}
	#else//使用16位并行数据总线模式
	#define LCD_WR_DATA(data){\
	LCD_RS_SET;\
	LCD_CS_CLR;\
	DATAOUT(data);\
	LCD_WR_CLR;\
	LCD_WR_SET;\
	LCD_CS_SET;\
	} 	
#endif
*/
				  		 
#endif  
	 
	 



