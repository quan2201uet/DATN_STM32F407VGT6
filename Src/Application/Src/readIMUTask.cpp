
#include "readIMUTask.h"

readIMUTask::readIMUTask(MPU6050* newIMU)
{
	mIMUInstance = newIMU;
}
readIMUTask::~readIMUTask()
{
}

bool readIMUTask :: init(void)
{

	if(mIMUInstance->initDevice() != true)
	{
		return false;
	}
	mIMUInstance->calibrate();

	return true;
}

void readIMUTask::startTask ()
{
	for(;;)
	{
		processTask();
	}
}


void readIMUTask::processTask()
{
	if(xSemaphoreTake(semaReadIMUTask,portMAX_DELAY) == pdTRUE)
	{
		readData();
		sendData();
	}
}


void readIMUTask::readData(void)
{
	mIMUInstance->getScaleData(&_IMU_data);
}

void readIMUTask::sendData()
{
	xQueueSend(queueIMUToEKF, &_IMU_data, 10);
	xQueueSend(queueIMUToMemory, &_IMU_data, 10);
}

