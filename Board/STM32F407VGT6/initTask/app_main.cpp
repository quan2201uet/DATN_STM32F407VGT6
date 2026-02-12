#include "app_main.h"

#include "FreeRTOS.h"

#include "common.h"
#include "qmc5883l.h"
#include "mpu6050.h"
#include "readIMUTask.h"
#include "readMagTask.h"
#include "uartSTM32.h"
#include "I2CSTM32.h"

constexpr uint16_t IMU_TASK_TIMER_COUNTER_MAX = 10;
constexpr uint16_t MAG_TASK_TIMER_COUNTER_MAX = 20;

constexpr uint16_t IMU_TASK_TIMER_MOD = 1;
constexpr uint16_t MAG_TASK_TIMER_MOD = 2;

constexpr uint16_t COUNTER_TIMER_MAX = 60200;

uartSTM32* uart1Protocol;
uartSTM32* uart2Protocol;
uartSTM32* uart4Protocol;

I2CSTM32* i2c1Protocol;
I2CSTM32* i2c2Protocol;

qmc5883l* deviceQMC5883L;
MPU6050* deviceMPU6050;

readMagTask* magTask;
readIMUTask* IMUTask;

// function callback run task
static void startIMUTask(void*parameter);
static void startMagTask(void*parameter);

bool createTasks()
{
	// create semaphore and queue
	initQueuesAndSemaphores();

	// protocol
	static I2CSTM32 i2c1(&hi2c1);
	static I2CSTM32 i2c2(&hi2c2);

	// device
	static MPU6050 imu(&i2c1);
	static qmc5883l mag(&i2c2);

	// task
	static readIMUTask IMUTask(&imu);
	static readMagTask magTask(&mag);

	if(xTaskCreate(startIMUTask, "IMU-Task", 256, NULL, 1, NULL) == pdFALSE) return false;
	if(xTaskCreate(startMagTask, "Mag-Task", 256, NULL, 1, NULL) == pdFALSE) return false;

	return true;
}

bool initTasks()
{
	if(!IMUTask->init()) return false;
	if(!magTask->init()) return false;

	return true;
}

static uint16_t counterSemaphore = 0;
void controlSemaphores()
{
	counterSemaphore++;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if (counterSemaphore%IMU_TASK_TIMER_COUNTER_MAX == IMU_TASK_TIMER_MOD)
	{
		xSemaphoreGiveFromISR(semaReadIMUTask, &xHigherPriorityTaskWoken);
	}

	if(counterSemaphore % MAG_TASK_TIMER_COUNTER_MAX == MAG_TASK_TIMER_MOD)
	{
		xSemaphoreGiveFromISR(semaReadMagTask, &xHigherPriorityTaskWoken);
	}

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	// reset counter
	if (counterSemaphore == COUNTER_TIMER_MAX)
	{
		counterSemaphore = 0;
	}
}

/* FUNCTION START TASK CODE BEGIN */
static void startIMUTask(void* parameter)
{
	IMUTask->startTask();
}

static void startMagTask(void* parameter)
{
	magTask->startTask();
}
/* FUNCTION START TASK CODE BEGIN */
