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

	}
}


void readBME280Task::processTask(QueueSetMemberHandle_t activeMember)
{
	readData();
}


void readBME280Task::readData(void)
{

}





