
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
	QueueSetMemberHandle_t activeMember;
	for(;;)
	{
		activeMember = xQueueSelectFromSet(semaReadIMUTask, 10);
		processTask(activeMember);
	}
}


void readRawDataIMUTask::processTask(QueueSetMemberHandle_t activeMember)
{
	if(activeMember == semaReadIMUTask)
	{
		xSemaphoreTake(semaReadIMUTask,10);
		readData();
//		if(xQueueSend(QueueIMUToLora, &_IMU_raw_data, 10) == pdPASS);


	}
}


void readRawDataIMUTask::readData(void)
{
	mIMUInstance->getRawData(&_IMU_raw_data);
}

