/*
 * GPSTask.h
 *
 *  Created on: Nov 7, 2025
 *      Author: LAPTOP K1
 */

#ifndef INC_GPSTASK_H_
#define INC_GPSTASK_H_


#include "common.h"
#include "string.h"
#include <stdlib.h>


class GPSDataAnalysisTask
{
private:
	float convertToDecimal(char *nmeaCoord);
	void parseGNRMC(char *nmea, GPS_data_t *gps);
	void parseGPGGA(char *nmea, GPS_data_t *gps);
	void readData(void);
	void processTask(QueueSetMemberHandle_t activeMember);
	GPS_data_t _GPS_data;

	char _rxBuffer[128];
	volatile uint16_t _rxIndex;
	volatile bool _lineReady;

public:
	GPSDataAnalysisTask ();

	void init(void);

	void startTask ();

	void pushCharFromISR(uint8_t c);
};

#endif /* INC_GPSTASK_H_ */
