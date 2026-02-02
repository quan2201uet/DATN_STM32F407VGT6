#ifndef INC_BME280TASK_H_
#define INC_BME280TASK_H_

#include "common.h"
#include "bme280.h"
#include "stdio.h"
extern I2C_HandleTypeDef hi2c1;

class readBME280Task
{
private:
	void readData(void);
	void processTask(QueueSetMemberHandle_t activeMember);


public:
	readBME280Task();
	void init(void);
	void startTask();
	BMP280_HandleTypedef bmp280;
	BME_data_t _BME_data;
};




#endif /* INC_BME280TASK_H_ */
