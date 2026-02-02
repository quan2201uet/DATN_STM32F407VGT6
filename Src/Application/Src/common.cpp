//#include "common.h"
//
//constexpr uint16_t IMU_TASK_TIMER_COUNTER_MAX = 5;
//
//constexpr uint16_t BME_TASK_TIMER_COUNTER_MAX = 200;
//
//constexpr uint16_t LORA_TASK_TIMER_COUNTER_MAX = 1000;
//constexpr uint16_t PM25_TASK_TIMER_COUNTER_MAX = 1000;
//
///* USING QUEUESET BEGIN*/
//QueueSetHandle_t BME280TaskQueueSet;
//QueueSetHandle_t GPSTaskQueueSet;
//QueueSetHandle_t IMUTaskQueueSet;
//QueueSetHandle_t LoraTaskQueueSet;
//QueueSetHandle_t MicroSDTaskQueueSet;
//QueueSetHandle_t PM25TaskQueueSet;
///* USING QUEUESET END*/
//
///* USING SEMAPHORE BEGIN*/
//SemaphoreHandle_t semaBME280Task;
//SemaphoreHandle_t semaGPSTask;
//SemaphoreHandle_t semaIMUTask;
//SemaphoreHandle_t semaLoraComunicationTask;
//SemaphoreHandle_t semaMicroSDTask;
//SemaphoreHandle_t semaPM25Task;
///* USING SEMAPHORE END*/
//
///* USING QUEUE BEGIN*/
//QueueHandle_t QueueGPSToMicroSD;
//QueueHandle_t QueueGPSToLora;
//
//QueueHandle_t QueueBMEToMicroSD;
//QueueHandle_t QueueBMEToLora;
//
//QueueHandle_t QueueIMUToMicroSD;
//QueueHandle_t QueueIMUToLora;
//
//QueueHandle_t QueuePM25ToMicroSD;
//QueueHandle_t QueuePM25ToLora;
///* USING QUEUE END*/
//
///* USING FUNCTION BEGIN*/
//void initTask()
//{
//
//	QueueBMEToLora = xQueueCreate(10, sizeof(BME_data_t));
//	QueueBMEToMicroSD = xQueueCreate(10, sizeof(BME_data_t));
//
//	QueueGPSToLora = xQueueCreate(10, sizeof(GPS_data_t));
//	QueueGPSToMicroSD = xQueueCreate(10, sizeof(GPS_data_t));
//
//	QueueIMUToLora = xQueueCreate(10, sizeof(IMU_data_t));
//	QueueIMUToMicroSD = xQueueCreate(10, sizeof(IMU_data_t));
//
//	QueuePM25ToLora = xQueueCreate(10, sizeof(float));
//	QueuePM25ToMicroSD = xQueueCreate(10, sizeof(float));
//
//
//	semaBME280Task = xSemaphoreCreateBinary();
//	semaGPSTask = xSemaphoreCreateBinary();
//	semaIMUTask = xSemaphoreCreateBinary();
//	semaLoraComunicationTask = xSemaphoreCreateBinary();
//	semaMicroSDTask = xSemaphoreCreateBinary();
//	semaPM25Task = xSemaphoreCreateBinary();
//
//	/* CREATE QUEUE SET BEGIN*/
//	BME280TaskQueueSet = xQueueCreateSet(1);
//	GPSTaskQueueSet = xQueueCreateSet(1);
//	IMUTaskQueueSet = xQueueCreateSet(1);
//	LoraTaskQueueSet = xQueueCreateSet(41);
//	MicroSDTaskQueueSet= xQueueCreateSet(41);
//	PM25TaskQueueSet = xQueueCreateSet(1);
//	/* CREATE QUEUE SET AND*/
//
//
//	/* ADD SEMAPHORE AND QUEUE INTO BME280 QUEUE SET BEGIN */
//	xQueueAddToSet(semaBME280Task, BME280TaskQueueSet);
//	/* ADD SEMAPHORE AND QUEUE INTO BME280 QUEUE SET END */
//
//	/* ADD SEMAPHORE AND QUEUE INTO GPS QUEUE SET BEGIN */
//	xQueueAddToSet(semaGPSTask, GPSTaskQueueSet);
//	/* ADD SEMAPHORE AND QUEUE INTO GPS QUEUE SET END */
//
//	/* ADD SEMAPHORE AND QUEUE INTO IMU QUEUE SET BEGIN */
//	xQueueAddToSet(semaIMUTask, IMUTaskQueueSet);
//	/* ADD SEMAPHORE AND QUEUE INTO IMU QUEUE SET END */
//
//
//	/* ADD SEMAPHORE AND QUEUE INTO LORA QUEUE SET BEGIN */
//	xQueueAddToSet(semaLoraComunicationTask, LoraTaskQueueSet);
//	xQueueAddToSet(QueueBMEToLora, LoraTaskQueueSet);
//	xQueueAddToSet(QueueGPSToLora, LoraTaskQueueSet);
//	xQueueAddToSet(QueueIMUToLora, LoraTaskQueueSet);
//	xQueueAddToSet(QueuePM25ToLora, LoraTaskQueueSet);
//	/* ADD SEMAPHORE AND QUEUE INTO LORA QUEUE SET END */
//
//	/* ADD SEMAPHORE AND QUEUE INTO MICROSD QUEUE SET BEGIN */
//	xQueueAddToSet(semaMicroSDTask, MicroSDTaskQueueSet);
//	xQueueAddToSet(QueueBMEToMicroSD, MicroSDTaskQueueSet);
//	xQueueAddToSet(QueueGPSToMicroSD, MicroSDTaskQueueSet);
//	xQueueAddToSet(QueueIMUToMicroSD, MicroSDTaskQueueSet);
//	xQueueAddToSet(QueuePM25ToMicroSD, MicroSDTaskQueueSet);
//	/* ADD SEMAPHORE AND QUEUE INTO MICROSD QUEUE SET END */
//
//	/* ADD SEMAPHORE AND QUEUE INTO PM25 QUEUE SET BEGIN */
//	xQueueAddToSet(semaPM25Task, PM25TaskQueueSet);
//	/* ADD SEMAPHORE AND QUEUE INTO PM25 QUEUE SET END */
//}
//
//
//
///* USING FUNCTION END*/
//
