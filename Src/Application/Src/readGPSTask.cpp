#include <readGPSTask.h>

GPSDataAnalysisTask :: GPSDataAnalysisTask()
{

}

void GPSDataAnalysisTask::init(void)
{

}

void GPSDataAnalysisTask::startTask()
{
	QueueSetMemberHandle_t activeMember;
	for(;;)
	{
		activeMember = xQueueSelectFromSet(GPSTaskQueueSet, 10);
		processTask(activeMember);

	}
}

void GPSDataAnalysisTask::processTask(QueueSetMemberHandle_t activeMember)
{
	if (activeMember == semaGPSTask)
	{
		xSemaphoreTake(semaGPSTask, 10);

		readData();
		if (xQueueSend(QueueGPSToLora, &_GPS_data, 100) == pdPASS)
		{

		}
		if (xQueueSend(QueueGPSToMicroSD, &_GPS_data, 100) == pdPASS)
		{

		}
	}

}

void GPSDataAnalysisTask::readData(void)
{

}

void GPSDataAnalysisTask::parseGPGGA(char *nmea, GPS_data_t *gps)
{

}

void GPSDataAnalysisTask:: parseGNRMC(char *nmea, GPS_data_t *gps)
{

}

float GPSDataAnalysisTask::convertToDecimal(char *nmeaCoord)
{
	return 0;
}

void GPSDataAnalysisTask::pushCharFromISR(uint8_t c)
{

}


