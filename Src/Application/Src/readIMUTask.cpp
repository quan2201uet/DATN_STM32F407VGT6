
#include "readIMUTask.h"

readRawDataIMUTask::readRawDataIMUTask(MPU6050* newIMU)
{
	mIMUInstance = newIMU;
}


bool readRawDataIMUTask :: init(void)
{

	if(mIMUInstance->initDevice() != true)
	{
		return false;
	}

	return true;
}

void readRawDataIMUTask::startTask ()
{
	for(;;)
	{
		processTask();
	}
}


void readRawDataIMUTask::processTask()
{
	if(xSemaphoreTake(semaReadIMUTask,portMAX_DELAY) == pdTRUE)
	{
		readData();
		sendData();
	}
}


void readRawDataIMUTask::readData(void)
{
	mIMUInstance->getRawData(&_IMU_raw_data);
}

void readRawDataIMUTask::sendData()
{
	xQueueSend(queueIMUToEKF, &_IMU_raw_data, 10);
	xQueueSend(queueIMUToMemory, &_IMU_raw_data, 10);
}

