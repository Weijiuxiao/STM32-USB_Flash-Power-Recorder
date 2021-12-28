#ifndef __Power_SW_H
#define __Power_SW_H		
//#include "sys.h"	 
//#include "stdlib.h"
#include "main.h"

#define PWR_On HAL_GPIO_WritePin(PWR_EN_GPIO_Port,PWR_EN_Pin,GPIO_PIN_SET)

#define PWR_Off HAL_GPIO_WritePin(PWR_EN_GPIO_Port,PWR_EN_Pin,GPIO_PIN_RESET)



#endif 