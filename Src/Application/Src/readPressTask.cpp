#include <readPressTask.h>


readBME280Task::readBME280Task(){}

void readBME280Task::init(void)
{

}

void readBME280Task::startTask()
{
	QueueSetMemberHandle_t activeMember;
	for(;;)
	{
		activeMember = xQueueSelectFromSet(BME280TaskQueueSet, 10);
		processTask(activeMember);
	}
}


void readBME280Task::processTask(QueueSetMemberHandle_t activeMember)
{
	if(activeMember == semaBME280Task)
	{
		xSemaphoreTake(semaBME280Task, 10);
		readData();
//		if (xQueueSend(QueueBMEToLora, &_BME_data, 10) == pdPASS)
//		{
//
//		}
//
//		if(xQueueSend(QueueBMEToMicroSD, &_BME_data, 10) == pdPASS)
//		{
//
//		}
	}
}

void readBME280Task::readData(void)
{

}





