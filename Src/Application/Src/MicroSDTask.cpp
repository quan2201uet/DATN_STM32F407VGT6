#include "MicroSDTask.h"

void logDataTask::init()
{

}
logDataTask::logDataTask(){}

void logDataTask::startTask()
{
	QueueSetMemberHandle_t activeMember;
	for(;;)
	{
		activeMember = xQueueSelectFromSet(MicroSDTaskQueueSet, 10);
		processTask(activeMember);
	}
}

void logDataTask::processTask(QueueSetMemberHandle_t activeMember)
{
	if(activeMember == semaMicroSDTask)
	{
		xSemaphoreTake(semaMicroSDTask, 10);
#pragma message ("chưa log data")
	}
	else if(activeMember == QueueBMEToMicroSD)
	{
		getBMEDataFromQueue();
	}
	else if (activeMember == QueueGPSToMicroSD)
	{
		getGPSDataFromQueue();
	}
	else if (activeMember == QueueIMUToMicroSD)
	{
		getIMUDataFromQueue();
	}

}

/* USER FUNCTION CODE BEGIN */
void logDataTask::getBMEDataFromQueue()
{
	BME_data_t _BME_data;
	xQueueReceive(QueueBMEToMicroSD, &_BME_data, 10);

	_MicroSD_data.temperature  = _BME_data.temp;
	_MicroSD_data.pressure     = _BME_data.press;
}

void logDataTask::getGPSDataFromQueue()
{
	GPS_data_t _GPS_data;
	xQueueReceive(QueueGPSToMicroSD, &_GPS_data, 10);

	_MicroSD_data.utc_time  = _GPS_data.timeUTC;
	_MicroSD_data.latitude  = _GPS_data.lat;
	_MicroSD_data.longitude = _GPS_data.lon;
	_MicroSD_data.speed     = _GPS_data.speed;
	_MicroSD_data.course    = _GPS_data.course;

}
void logDataTask::getIMUDataFromQueue()
{
	IMU_data_t _IMU_data;
	xQueueReceive(QueueIMUToMicroSD, &_IMU_data, 10);
	_MicroSD_data.acc_x  = _IMU_data.ax;
	_MicroSD_data.acc_y  = _IMU_data.ay;
	_MicroSD_data.acc_z  = _IMU_data.az;

	_MicroSD_data.gyro_x = _IMU_data.gx;
	_MicroSD_data.gyro_y = _IMU_data.gy;
	_MicroSD_data.gyro_z = _IMU_data.gz;
}

/* USER FUNCTION CODE END */
