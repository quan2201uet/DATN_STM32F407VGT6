/*
 * readMagTask.h
 *
 *  Created on: Feb 2, 2026
 *      Author: phamq
 */

#ifndef APPLICATION_INC_READMAGTASK_H_
#define APPLICATION_INC_READMAGTASK_H_

#include "qmc5883l.h"

class readMagTask
{
private:
	qmc5883l* mMagInstance;
	Mag_calib_t mCalib;
private:
	void processTask();
	bool readRaw(Mag_raw_t* rawData);

	/* calibration */
	void calibrate();
	void applyCalib(const Mag_raw_t* raw, Mag_data_t* out);

	/* flash */
	bool loadCalib();
	bool saveCalib();

	/* comm */
	void sendDataToEKF(const Mag_data_t* data);
public:
	readMagTask(qmc5883l* newMag);
	~readMagTask();
	bool init();
	void startTask();

};

#endif /* APPLICATION_INC_READMAGTASK_H_ */
