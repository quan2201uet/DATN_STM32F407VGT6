#ifndef INCLUDE_COMMON_COMMON_H_
#define INCLUDE_COMMON_COMMON_H_

#include "stdint.h"
typedef struct
{
	int16_t ax;
	int16_t ay;
	int16_t az;

	int16_t gx;
	int16_t gy;
	int16_t gz;

	int16_t gx_cal;
	int16_t gy_cal;
	int16_t gz_cal;

	int16_t temp_raw;

	float temp;
} mpu6050_raw_t;



#endif /* INCLUDE_COMMON_COMMON_H_ */
