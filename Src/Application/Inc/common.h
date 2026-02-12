
#ifndef INC_COMMON_H_
#define INC_COMMON_H_

/* USER CODE BEGIN Includes */
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include <stdio.h>
#include <stdint.h>
#include <math.h>
/* USER CODE END Includes */

/* USING QUEUESET BEGIN*/
extern QueueSetHandle_t EKFTaskQueueSet;
extern QueueSetHandle_t memoryTaskQueueSet;
extern QueueSetHandle_t GCSTaskQueueSet;
extern QueueSetHandle_t PIDTaskQueueSet;
extern QueueSetHandle_t FLTaskQueueSet;
/* USING QUEUESET END*/

/* USER CODE BEGIN initial queue */
extern QueueHandle_t queueGPSToMemory;
extern QueueHandle_t queueGPSToEKF;
//extern QueueHandle_t QueueISRRawGPS // thay thế bằng stream

extern QueueHandle_t queueIMUToMemory;
extern QueueHandle_t queueIMUToEKF;

extern QueueHandle_t queueMagToMemory;
extern QueueHandle_t queueMagToEKF;

//pressure
extern QueueHandle_t queuePreToMemory;
extern QueueHandle_t queuePreToEKF;

extern QueueHandle_t queueBatToMemory;
extern QueueHandle_t queueBatToPID;
// Bat co the thay the bang stream

extern QueueHandle_t queueEKFToGCS;
extern QueueHandle_t queueEKFToPID;

extern QueueHandle_t queuePIDToGCS;

extern QueueHandle_t queueGCSToFL;

extern QueueHandle_t queueISRRCToFL; // có thể xem xét thay bằng stream

extern QueueHandle_t queueFLToPID;
/* USER CODE END initial queue */

/* DEFINE TYPEDEF BEGIN*/
typedef uint32_t time_ms_t;
/* DEFINE TYPEDEF END*/

/* USER CODE BEGIN initial semaphore */
extern SemaphoreHandle_t semaReadGPSIMUTask;
extern SemaphoreHandle_t semaReadIMUTask;
extern SemaphoreHandle_t semaReadMagTask;
extern SemaphoreHandle_t semaReadPreTask;
extern SemaphoreHandle_t semareadBatTask;
extern SemaphoreHandle_t semaEKFTask;
extern SemaphoreHandle_t semaGCSTask;
extern SemaphoreHandle_t semaFLTask;
extern SemaphoreHandle_t semaPIDTask;
extern SemaphoreHandle_t semaMemoryTak;
/* USER CODE END initial semaphore */


/* USER CODE BEGIN Struct */
// gps
typedef struct{
	float timeUTC;
	float lat;
	float lon;
	float speed;
	float course;
	float distance;
	char ns;
	char ew;
} GPS_data_t;

//GPRMC
typedef struct GPRMC{
	float utcTime;          // Thời gian UTC (hhmmss.sss)
	float latitude;         // Vĩ độ (độ thập phân)
	float longitude;        // Kinh độ (độ thập phân)
	char ns;                // 'N' hoặc 'S'
	char ew;                // 'E' hoặc 'W'
	int fixQuality;         // 0 = không fix, 1 = GPS fix, 2 = DGPS fix
	int numSatellites;      // Số vệ tinh bắt được
	float hdop;             // Horizontal dilution of precision
	float altitude;         // Cao độ (m)
	char altitudeUnit;      // 'M'

	// Thông tin từ RMC
	char status;            // 'A' = valid, 'V' = invalid
	float speedKnots;       // Tốc độ (knots)
	float course;           // Hướng di chuyển (độ)
	int day, month, year;   // Ngày tháng năm (UTC)
} GPRMC_Data_t;


//bme
typedef struct{
	float humi;
	float temp;
	float press;

}BME_data_t;

// Mag
typedef struct
{
	int16_t mx_raw;
	int16_t my_raw;
	int16_t mz_raw;
} Mag_raw_t;

typedef struct
{
    float offset_x;
    float offset_y;
    float offset_z;

    float scale_x;
    float scale_y;
    float scale_z;

    uint32_t magic;
} Mag_calib_t;

typedef struct
{
    float mx;
    float my;
    float mz;

    uint32_t timestamp_us;
} Mag_data_t;

//imu
typedef struct{
	float ax;
	float ay;
	float az;
	float temp;
	float gx;
	float gy;
	float gz;

} IMU_raw_data_t;

typedef struct{
	float ax;
	float ay;
	float az;
	float temp;
	float gx;
	float gy;
	float gz;

} IMU_data_t;

typedef struct
{
	int16_t gx_cal;
	int16_t gy_cal;
	int16_t gz_cal;
}Gyro_cal_t;


// GPGGA
typedef struct
{
	float latitude;      // vĩ độ dạng độ thập phân
	char ns;             // N/S
	float longitude;     // kinh độ dạng độ thập phân
	char ew;             // E/W
	float altitude;      // độ cao
	char altitudeUnit;   // đơn vị
	float hdop;          // HDOP
	float utcTime;       // giờ phút giây dạng số hhmmss.ss
	uint8_t fixQuality;  // loại fix
	uint8_t numSatellites;
} GPGGA_Data_t;

// ekf out
typedef struct
{
	float pos[3];
	float vel[3];
	float att[3];
} nav_state_t;

//pid out
typedef struct
{
	uint16_t motor_pwm[4];
} motor_cmd_t;

// GCS out
typedef struct
{
	float pos_sp[3];
	float vel_sp[3];
}control_setpoint_t;
// xem xet phat trien sau

// for mixer
typedef struct
{
	float target_roll;
	float target_pitch;
	float target_yaw;
	int throttle;
} target_control_t;

typedef struct
{
	uint8_t sbus[25];
	uint16_t channel[7];
	uint8_t sbus_first_byte;
	uint8_t sbus_state;
	uint8_t sbus_cnt_check;
} rc_input_t;
/* USER CODE END Struct */


/* USER CODE BEGIN Function */

void initTask(void);



/* USER CODE END Struct */

#endif /* INC_COMMON_H_ */
