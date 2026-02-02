#ifndef INC_IMUTASK_H_
#define INC_IMUTASK_H_

#include "common.h"
#define ADD 0xD0
#define RTD 57.2957
extern I2C_HandleTypeDef hi2c2;


class readRawDataIMUTask
{
private:
	IMU_data_t _IMU_data;
	uint32_t last_time = 0;
	float dt = 0;

	void readData(void);
	void processTask(QueueSetMemberHandle_t activeMember);
	void MPU6050ReadG(void);
	void MPU6050ReadA();
	void MPU6050ReadAll();
	void filter();

public:
	readRawDataIMUTask();

	void init(void);
	void startTask();
};



#endif /* INC_IMUTASK_H_ */
