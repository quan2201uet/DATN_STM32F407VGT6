#include "common.h"

constexpr uint16_t IMU_TASK_TIMER_COUNTER_MAX = 5;

constexpr uint16_t BME_TASK_TIMER_COUNTER_MAX = 200;

constexpr uint16_t LORA_TASK_TIMER_COUNTER_MAX = 1000;
constexpr uint16_t PM25_TASK_TIMER_COUNTER_MAX = 1000;

/* USING QUEUESET BEGIN*/
//QueueSetHandle_t BME280TaskQueueSet;
//QueueSetHandle_t GPSTaskQueueSet;
//QueueSetHandle_t IMUTaskQueueSet;
QueueSetHandle_t EKFTaskQueueSet;
QueueSetHandle_t memoryTaskQueueSet;
QueueSetHandle_t GCSTaskQueueSet;
QueueSetHandle_t PIDTaskQueueSet;
QueueSetHandle_t FLTaskQueueSet;
/* USING QUEUESET END*/

/* USING SEMAPHORE BEGIN*/
SemaphoreHandle_t semaReadGPSIMUTask;
SemaphoreHandle_t semaReadIMUTask;
SemaphoreHandle_t semaReadMagTask;
SemaphoreHandle_t semaReadPreTask;
SemaphoreHandle_t semareadBatTask;
SemaphoreHandle_t semaEKFTask;
SemaphoreHandle_t semaGCSTask;
SemaphoreHandle_t semaFLTask;
SemaphoreHandle_t semaPIDTask;
SemaphoreHandle_t semaMemoryTak;
/* USING SEMAPHORE END*/

/* USING QUEUE BEGIN*/
QueueHandle_t queueGPSToMemory;
QueueHandle_t queueGPSToEKF;
//QueueHandle_t QueueISRRawGPS // thay thế bằng stream

QueueHandle_t queueIMUToMemory;
QueueHandle_t queueIMUToEKF;

QueueHandle_t queueMagToMemory;
QueueHandle_t queueMagToEKF;

//pressure
QueueHandle_t queuePreToMemory;
QueueHandle_t queuePreToEKF;

QueueHandle_t queueBatToMemory;
QueueHandle_t queueBatToPID;
// Bat co the thay the bang stream

QueueHandle_t queueEKFToGCS;
QueueHandle_t queueEKFToPID;

QueueHandle_t queuePIDToGCS;

QueueHandle_t queueGCSToFL;

QueueHandle_t queueISRRCToFL; // có thể xem xét thay bằng stream

QueueHandle_t queueFLToPID;
/* USING QUEUE END*/

/* USING FUNCTION BEGIN*/
void initTask()
{
	/* CREATE QUEUE BEGIN*/

	queueGPSToEKF = xQueueCreate(10, sizeof(GPS_data_t));
	queueGPSToMemory = xQueueCreate(10, sizeof(GPS_data_t));

	queueIMUToEKF = xQueueCreate(10, sizeof(IMU_data_t));
	queueIMUToMemory = xQueueCreate(10, sizeof(IMU_data_t));

	queueMagToMemory = xQueueCreate(10, sizeof(Mag_raw_t));
	queueMagToEKF = xQueueCreate(10, sizeof(Mag_raw_t));

	//pressure
	queuePreToMemory = xQueueCreate(10, sizeof(BME_data_t));
	queuePreToEKF = xQueueCreate(10, sizeof(BME_data_t));;

	queueEKFToGCS = xQueueCreate(10, sizeof(nav_state_t));
	queueEKFToPID = xQueueCreate(10, sizeof(nav_state_t));

	queuePIDToGCS = xQueueCreate(10, sizeof(motor_cmd_t));

	//QueueGCSToFL  = xQueueCreate(10, sizeof(control_setpoint_t));

	queueISRRCToFL= xQueueCreate(10, sizeof(rc_input_t)); // có thể xem xét thay bằng stream

	queueFLToPID  = xQueueCreate(10, sizeof(target_control_t));
	/* CREATE QUEUE BEGIN*/

	/* CREATE SEMAPHORE BEGIN */
	semaReadGPSIMUTask	= xSemaphoreCreateBinary();
	semaReadIMUTask 	= xSemaphoreCreateBinary();
	semaReadMagTask 	= xSemaphoreCreateBinary();
	semaReadPreTask 	= xSemaphoreCreateBinary();
	semareadBatTask 	= xSemaphoreCreateBinary();
	semaEKFTask			= xSemaphoreCreateBinary();
	semaGCSTask			= xSemaphoreCreateBinary();
	semaFLTask			= xSemaphoreCreateBinary();
	semaPIDTask			= xSemaphoreCreateBinary();
	semaMemoryTak		= xSemaphoreCreateBinary();
	/* CREATE SEMAPHORE END */

	/* CREATE QUEUE SET BEGIN */
	EKFTaskQueueSet 	= xQueueCreateSet(41);
	memoryTaskQueueSet 	= xQueueCreateSet(51);
	GCSTaskQueueSet 	= xQueueCreateSet(21);
	PIDTaskQueueSet 	= xQueueCreateSet(31);
	FLTaskQueueSet 		= xQueueCreateSet(21);
	/* CREATE QUEUE SET AND*/

	/* ADD SEMAPHORE AND QUEUE INTO EKF QUEUE SET BEGIN */
	xQueueAddToSet(semaEKFTask, EKFTaskQueueSet);
	xQueueAddToSet(queueGPSToEKF, EKFTaskQueueSet);
	xQueueAddToSet(queueIMUToEKF, EKFTaskQueueSet);
	xQueueAddToSet(queueMagToEKF, EKFTaskQueueSet);
	xQueueAddToSet(queuePreToEKF, EKFTaskQueueSet);
	/* ADD SEMAPHORE AND QUEUE INTO EKF QUEUE SET END */

	/* ADD SEMAPHORE AND QUEUE INTO MEMORY QUEUE SET BEGIN */
	xQueueAddToSet(semaMemoryTak, memoryTaskQueueSet);
	xQueueAddToSet(queueGPSToMemory, memoryTaskQueueSet);
	xQueueAddToSet(queueIMUToMemory, memoryTaskQueueSet);
	xQueueAddToSet(queueMagToMemory, memoryTaskQueueSet);
	xQueueAddToSet(queuePreToMemory, memoryTaskQueueSet);
	xQueueAddToSet(queueBatToMemory, memoryTaskQueueSet);
	/* ADD SEMAPHORE AND QUEUE INTO MEMORY QUEUE SET END */

	/* ADD SEMAPHORE AND QUEUE INTO GCS QUEUE SET BEGIN */
	xQueueAddToSet(semaGCSTask, GCSTaskQueueSet);
	xQueueAddToSet(queueEKFToGCS, GCSTaskQueueSet);
	xQueueAddToSet(queuePIDToGCS, GCSTaskQueueSet);
	/* ADD SEMAPHORE AND QUEUE INTO GCS QUEUE SET END */

	/* ADD SEMAPHORE AND QUEUE INTO PID QUEUE SET BEGIN */
	xQueueAddToSet(semaPIDTask, PIDTaskQueueSet);
	xQueueAddToSet(queueFLToPID, PIDTaskQueueSet);
	xQueueAddToSet(queueBatToPID, PIDTaskQueueSet);
	xQueueAddToSet(queueEKFToPID, PIDTaskQueueSet);
	/* ADD SEMAPHORE AND QUEUE INTO PID QUEUE SET END */

	/* ADD SEMAPHORE AND QUEUE INTO FL QUEUE SET BEGIN */
	xQueueAddToSet(semaFLTask, FLTaskQueueSet);
	xQueueAddToSet(queueGCSToFL, FLTaskQueueSet);
	xQueueAddToSet(queueISRRCToFL, FLTaskQueueSet);
	/* ADD SEMAPHORE AND QUEUE INTO FL QUEUE SET END */
}

/* USING FUNCTION END*/

