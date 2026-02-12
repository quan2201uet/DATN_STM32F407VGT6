#ifndef STM32F407VGT6_INITTASK_APP_MAIN_H_
#define STM32F407VGT6_INITTASK_APP_MAIN_H_

#include "stm32f4xx_hal.h"
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void initTasks();



#endif /* STM32F407VGT6_INITTASK_APP_MAIN_H_ */
