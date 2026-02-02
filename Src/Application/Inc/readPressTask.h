#ifndef INC_BME280TASK_H_
#define INC_BME280TASK_H_

#include "common.h"
#include "stdio.h"

class readBME280Task
{
private:
	void readData(void);
	void processTask(QueueSetMemberHandle_t activeMember);


public:
	readBME280Task();
	void init(void);
	void startTask();

};




#endif /* INC_BME280TASK_H_ */
