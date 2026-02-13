#ifndef INC_IMUTASK_H_
#define INC_IMUTASK_H_

#include "common.h"
#include "mpu6050.h"

class readIMUTask
{
private:
	IMU_data_t _IMU_data;
	void readData(void);
	void sendData();
	void processTask();
	MPU6050* mIMUInstance;
public:
	readIMUTask(MPU6050* newIMU);
	~readIMUTask();

	bool init(void);
	void startTask();
};



#endif /* INC_IMUTASK_H_ */
