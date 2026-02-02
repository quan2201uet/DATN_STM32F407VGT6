
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
/* USER CODE END Includes */

/* USING QUEUESET BEGIN*/
extern QueueSetHandle_t BME280TaskQueueSet;
extern QueueSetHandle_t GPSTaskQueueSet;
extern QueueSetHandle_t IMUTaskQueueSet;
extern QueueSetHandle_t LoraTaskQueueSet;
extern QueueSetHandle_t MicroSDTaskQueueSet;
extern QueueSetHandle_t PM25TaskQueueSet;
/* USING QUEUESET END*/

/* USER CODE BEGIN initial queue */
extern QueueHandle_t QueueGPSToMicroSD;
extern QueueHandle_t QueueGPSToLora;

extern QueueHandle_t QueueBMEToMicroSD;
extern QueueHandle_t QueueBMEToLora;

extern QueueHandle_t QueueIMUToMicroSD;
extern QueueHandle_t QueueIMUToLora;

extern QueueHandle_t QueuePM25ToMicroSD;
extern QueueHandle_t QueuePM25ToLora;
/* USER CODE END initial queue */

/* USER CODE BEGIN initial semaphore */
extern SemaphoreHandle_t semaBME280Task;
extern SemaphoreHandle_t semaGPSTask;
extern SemaphoreHandle_t semaIMUTask;
extern SemaphoreHandle_t semaLoraComunicationTask;
extern SemaphoreHandle_t semaMicroSDTask;
extern SemaphoreHandle_t semaPM25Task;
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

//bme
typedef struct{
	float humi;
	float temp;
	float press;

}BME_data_t;

//imu
typedef struct{
	float gx;
	float gy;
	float gz;
	float ax;
	float ay;
	float az;
} IMU_data_t;

//Lora
typedef struct{
	float timeUTC;
	float speed;
	float course;
	float distance;

	float gpsTime;
	float gpsLatitude;
	float gpsLongtitude;

	float accX;
	float accY;
	float accZ;
	float gyroX;
	float gyroY;
	float gyroZ;

	float roll;
	float pitch;

	float press;
	float temp;
	float humi;
	float co;
	float pm;


} Lora_data_t;


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

// qmc5883l raw data
typedef struct
{
	int16_t mx_raw;
	int16_t my_raw;
	int16_t mz_raw;

	int16_t mx_offset;
	int16_t my_offset;
	int16_t mz_offset;

	float my_scale;
	float mz_scale;

	int16_t qmc_calib[6];

} qmc5883l_raw_t;
/* USER CODE END Struct */


/* USER CODE BEGIN Function */

void initTask(void);


/* USER CODE END Struct */

#endif /* INC_COMMON_H_ */
