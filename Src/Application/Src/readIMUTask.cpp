#include <math.h>
#include <readIMUTask.h>
readRawDataIMUTask::readRawDataIMUTask(){}


void readRawDataIMUTask :: init(void)
{

}

void readRawDataIMUTask::startTask ()
{
	QueueSetMemberHandle_t activeMember;
	for(;;)
	{
		activeMember = xQueueSelectFromSet(IMUTaskQueueSet, 10);
		processTask(activeMember);
	}
}


void readRawDataIMUTask::processTask(QueueSetMemberHandle_t activeMember)
{
	if(activeMember == semaIMUTask)
	{
		xSemaphoreTake(semaIMUTask,10);
		readData();
		if(xQueueSend(QueueIMUToLora, &_IMU_data, 10) == pdPASS)
		{

		}

		if(xQueueSend(QueueIMUToMicroSD, &_IMU_data, 10) == pdPASS)
		{

		}
	}
}
void readRawDataIMUTask::MPU6050ReadAll()
{

}
void readRawDataIMUTask::readData(void)
{

}


void readRawDataIMUTask::MPU6050ReadG()
{

}

void readRawDataIMUTask::MPU6050ReadA()
{

}

void readRawDataIMUTask::filter()
{

}

