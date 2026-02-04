#ifndef INC_IMUTASK_H_
#define INC_IMUTASK_H_

#include "common.h"
#include "mpu6050.h"


class readRawDataIMUTask
{
private:
	IMU_raw_data_t _IMU_raw_data;
	void readData(void);
	void processTask(QueueSetMemberHandle_t activeMember);
	MPU6050* mIMUInstance;
public:
	readRawDataIMUTask(MPU6050* newIMU);

	bool init(void);
	void startTask();
};



#endif /* INC_IMUTASK_H_ */
