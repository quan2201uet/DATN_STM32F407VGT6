#include <readGPSTask.h>

GPSDataAnalysisTask :: GPSDataAnalysisTask()
{

}

void GPSDataAnalysisTask::init(void)
{

}

void GPSDataAnalysisTask::startTask()
{
	for(;;)
	{

	}
}

void GPSDataAnalysisTask::processTask(QueueSetMemberHandle_t activeMember)
{
	if (activeMember == semaGCSTask)
	{
		readData();
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


