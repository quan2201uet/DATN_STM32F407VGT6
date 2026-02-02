#ifndef INC_MICROSDTASK_H_
#define INC_MICROSDTASK_H_

#include "common.h"


class logDataTask
{
public:
	logDataTask();
	void init(void);
	void startTask();
private:
	mavlink_sensor_data_t _MicroSD_data;
	void processTask(QueueSetMemberHandle_t activeMember);
	void getBMEDataFromQueue();
	void getGPSDataFromQueue();
	void getIMUDataFromQueue();
};


#endif /* INC_MICROSDTASK_H_ */
