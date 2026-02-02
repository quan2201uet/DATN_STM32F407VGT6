#include "GPSTask.h"

GPSDataAnalysisTask :: GPSDataAnalysisTask()
{
	_rxIndex = 0;
	_lineReady = false;
	memset(_rxBuffer, 0, RX_BUFFER_SIZE);
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
//void GPSDataAnalysisTask::readData(void)
//{
//
//	uint8_t RxChar;
//	static char RxBuffer[RX_BUFFER_SIZE];
//	static uint16_t idx = 0;
//
//	HAL_UART_Receive(&huart2, &RxChar, 1, 10);
//
//	if(idx < RX_BUFFER_SIZE-1) RxBuffer[idx++] = RxChar;
//	// Kết thúc chuỗi NMEA
//	if(RxChar == '\n')
//	{
//		RxBuffer[idx] = '\0'; // kết thúc chuỗi
//		if (strstr(RxBuffer, "$GPRMC") != NULL)
//		{
//			parseGNRMC(RxBuffer, &_GPS_data);
//		}
//		else if (strstr(RxBuffer, "$GPGGA") != NULL)
//		{
//			parseGPGGA(RxBuffer, &_GPS_data);
//		}
//		// Reset buffer
//		idx = 0;
//		memset(RxBuffer, 0, RX_BUFFER_SIZE);
//	}
//}

void GPSDataAnalysisTask::readData(void)
{
	if (!_lineReady) return;

	_lineReady = false;

	if (strstr(_rxBuffer, "$GPRMC"))
	{
		parseGNRMC(_rxBuffer, &_GPS_data);
	}
	else if (strstr(_rxBuffer, "$GPGGA"))
	{
		parseGPGGA(_rxBuffer, &_GPS_data);
	}

	memset(_rxBuffer, 0, RX_BUFFER_SIZE);
}

void GPSDataAnalysisTask::parseGPGGA(char *nmea, GPS_data_t *gps)
{
	char *token;
	int field = 0;

	token = strtok(nmea, ",");
	while (token != NULL)
	{
		field++;
		switch (field)
		{
		case 2: // Thời gian UTC (hhmmss.sss)
			gps->timeUTC = atof(token);
			break;

		case 3: // Vĩ độ
			gps->lat = convertToDecimal(token);
			break;

		case 4: // Bắc/Nam
			gps->ns = token[0];
			if (gps->ns == 'S')
				gps->lat = -gps->lat;
			break;

		case 5: // Kinh độ
			gps->lon = convertToDecimal(token);
			break;

		case 6: // Đông/Tây
			gps->ew = token[0];
			if (gps->ew == 'W')
				gps->lon = -gps->lon;
			break;

			// Các field khác của GGA (fix, numSat, hdop, altitude...)
			// không dùng vì GPS_data_t không có

		default:
			break;
		}

		token = strtok(NULL, ",");
	}
}

void GPSDataAnalysisTask:: parseGNRMC(char *nmea, GPS_data_t *gps)
{
	char *token;
	int field = 0;

	token = strtok(nmea, ",");
	while(token != NULL)
	{
		field++;
		switch(field)
		{
		case 2: // Thời gian UTC (hhmmss.sss)
			gps->timeUTC = atof(token);
			break;

			//            case 3: // Trạng thái (A/V)
			//                gps->status = token[0];
			//                break;

		case 4: // Vĩ độ
			gps->lat = convertToDecimal(token);
			break;

		case 5: // Bắc/Nam
			gps->ns = token[0];
			if(gps->ns == 'S') gps->lat = -gps->lat;
			break;

		case 6: // Kinh độ
			gps->lon = convertToDecimal(token);
			break;

		case 7: // Đông/Tây
			gps->ew = token[0];
			if(gps->ew == 'W') gps->lon = -gps->lon;
			break;

		case 8: // Tốc độ (knots)
			gps->speed = atof(token);
			break;

		case 9: // Hướng di chuyển
			gps->course = atof(token);
			break;

			//            case 10: // Ngày (ddmmyy)
			//                if (strlen(token) == 6) {
			//                    char d[3], m[3], y[3];
			//                    strncpy(d, token, 2); d[2] = '\0';
			//                    strncpy(m, token + 2, 2); m[2] = '\0';
			//                    strncpy(y, token + 4, 2); y[2] = '\0';
			//                    gps->day = atoi(d);
			//                    gps->month = atoi(m);
			//                    gps->year = 2000 + atoi(y);
			//                }
			//                break;
		}

		token = strtok(NULL, ",");
	}
}

float GPSDataAnalysisTask::convertToDecimal(char *nmeaCoord)
{
	float val = atof(nmeaCoord);
	int degrees = (int)(val / 100);
	float minutes = val - (degrees * 100);
	return degrees + minutes / 60.0f;
}

void GPSDataAnalysisTask::pushCharFromISR(uint8_t c)
{
	if (_rxIndex < RX_BUFFER_SIZE - 1)
	{
		_rxBuffer[_rxIndex++] = c;

		if (c == '\n')
		{
			_rxBuffer[_rxIndex] = '\0';
			_lineReady = true;
			_rxIndex = 0;

			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			xSemaphoreGiveFromISR(semaGPSTask, &xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
	else
	{
		_rxIndex = 0;
	}
}


