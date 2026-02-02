#include "BME280Task.h"


readBME280Task::readBME280Task(){}

void readBME280Task::init(void)
{
	bmp280_init_default_params(&bmp280.params);
	bmp280.addr = BMP280_I2C_ADDRESS_0;
	bmp280.i2c = &hi2c1;

	while (!bmp280_init(&bmp280, &bmp280.params)) {
	//	size = sprintf((char *)Data, "BMP280 initialization failed\n");
HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}
	bool bme280p = bmp280.id == BME280_CHIP_ID;
	//size = sprintf((char *)Data, "BMP280: found %s\n", bme280p ? "BME280" : "BMP280");
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
		if (xQueueSend(QueueBMEToLora, &_BME_data, 10) == pdPASS)
		{

		}

		if(xQueueSend(QueueBMEToMicroSD, &_BME_data, 10) == pdPASS)
		{

		}
	}
}

void readBME280Task::readData(void)
{
	bmp280_read_float(&bmp280, &_BME_data.temp, &_BME_data.press, &_BME_data.humi);
}





