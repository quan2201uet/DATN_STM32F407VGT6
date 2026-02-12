#include "app_main.h"

#include "qmc5883l.h"
#include "mpu6050.h"
#include "readIMUTask.h"
#include "readMagTask.h"
#include "uartSTM32.h"
#include "I2CSTM32.h"

uartSTM32* uart1Protocol;
uartSTM32* uart2Protocol;
uartSTM32* uart4Protocol;

I2CSTM32* i2c1Protocol;
I2CSTM32* i2c2Protocol;


void initTasks()
{

}
