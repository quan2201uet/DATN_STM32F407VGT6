#include "IMUTask.h"
#include <math.h>
readRawDataIMUTask::readRawDataIMUTask(){}


void readRawDataIMUTask :: init(void)
{
	uint8_t check;
	uint8_t mData;
	HAL_I2C_Mem_Read(&hi2c2,ADD, 0x75,1, &check,1,1000);
	if(check == 0x68){
		mData = 0x00;
		HAL_I2C_Mem_Write(&hi2c2, ADD,0x6B,1,&mData,1,1000);
		mData = 0x07;
		HAL_I2C_Mem_Write(&hi2c2, ADD,0x19,1,&mData,1,1000);
		mData = 0x00;
		HAL_I2C_Mem_Write(&hi2c2, ADD,0x1B,1,&mData,1,1000);
		mData = 0x00;
		HAL_I2C_Mem_Write(&hi2c2, ADD,0x1C,1,&mData,1,1000);
	}


}

void readRawDataIMUTask::startTask ()
{
	QueueSetMemberHandle_t activeMember;
	for(;;)
	{
		activeMember = xQueueSelectFromSet(IMUTaskQueueSet, 10);
		processTask(activeMember);
	}
}


void readRawDataIMUTask::processTask(QueueSetMemberHandle_t activeMember)
{
	if(activeMember == semaIMUTask)
	{
		xSemaphoreTake(semaIMUTask,10);
		readData();
		if(xQueueSend(QueueIMUToLora, &_IMU_data, 10) == pdPASS)
		{

		}

		if(xQueueSend(QueueIMUToMicroSD, &_IMU_data, 10) == pdPASS)
		{

		}
	}
}
void readRawDataIMUTask::MPU6050ReadAll()
{
	uint8_t buffer[14];
	int16_t raw_ax, raw_ay, raw_az, raw_gx, raw_gy, raw_gz;
	const float ALPHA = 0.98f;

	// Đọc một lần 14 bytes bắt đầu từ thanh ghi ACCEL_XOUT_H (0x3B)
	if(HAL_I2C_Mem_Read(&hi2c2, ADD, 0x3B, 1, buffer, 14, 100) == HAL_OK)
	{
		// Ghép bytes cho Accel
		raw_ax = (int16_t)(buffer[0] << 8 | buffer[1]);
		raw_ay = (int16_t)(buffer[2] << 8 | buffer[3]);
		raw_az = (int16_t)(buffer[4] << 8 | buffer[5]);

		// Skip buffer[6] & [7] (Temperature) nếu không dùng

		// Ghép bytes cho Gyro
		raw_gx = (int16_t)(buffer[8] << 8 | buffer[9]);
		raw_gy = (int16_t)(buffer[10] << 8 | buffer[11]);
		raw_gz = (int16_t)(buffer[12] << 8 | buffer[13]);

		// Chuyển đổi sang đơn vị vật lý
		_IMU_data.ax = (float)raw_ax / 16384.0f;
		_IMU_data.ay = (float)raw_ay / 16384.0f;
		_IMU_data.az = (float)raw_az / 16384.0f;

		_IMU_data.gx = (float)raw_gx / 131.0f;
		_IMU_data.gy = (float)raw_gy / 131.0f;
		_IMU_data.gz = (float)raw_gz / 131.0f;

		// 3. Tính toán thời gian dt thực tế
		uint32_t current_time = HAL_GetTick();
		dt = (float)(current_time - last_time) / 1000.0f;

		// Tránh lỗi dt bằng 0 hoặc quá lớn khi mới khởi động hoặc tràn tick
		if (dt <= 0 || dt > 0.1f) dt = 0.01f;
		last_time = current_time; // <<< QUAN TRỌNG: Phải cập nhật last_time

		// 4. Tính góc từ Accelerometer (Trạng thái tĩnh)
		float roll_acc = atan2f(_IMU_data.ay, _IMU_data.az) * 180.0f / M_PI;
		float pitch_acc = atan2f(-_IMU_data.ax, sqrtf(_IMU_data.ay * _IMU_data.ay + _IMU_data.az * _IMU_data.az)) * 180.0f / M_PI;

		// 5. Bộ lọc bù (Complementary Filter)
		// Kết hợp phản ứng nhanh của Gyro và sự ổn định của Accel
		_IMU_data.roll  = ALPHA * (_IMU_data.roll + _IMU_data.gx * dt) + (1.0f - ALPHA) * roll_acc;
		_IMU_data.pitch = ALPHA * (_IMU_data.pitch + _IMU_data.gy * dt) + (1.0f - ALPHA) * pitch_acc;
	}
}
void readRawDataIMUTask::readData(void)
{
	//	MPU6050ReadA();
	//	MPU6050ReadG();
	MPU6050ReadAll();
	//filter();
}


void readRawDataIMUTask::MPU6050ReadG()
{
	uint8_t dataG[6];
	uint16_t data16_G[3];
	HAL_I2C_Mem_Read(&hi2c2,ADD, 0x43,1, dataG,6,1000);
	data16_G[0] = (int16_t)(dataG[0] << 8 | dataG[1]);
	data16_G[1] = (int16_t)(dataG[2] << 8 | dataG[3]);
	data16_G[2] = (int16_t)(dataG[4] << 8 | dataG[5]);
	_IMU_data.gx = (float)data16_G[0]/131.0;
	_IMU_data.gy = (float)data16_G[1]/131.0;
	_IMU_data.gz = (float)data16_G[2]/131.0;
}

void readRawDataIMUTask::MPU6050ReadA()
{
	uint8_t dataA[6];
	uint16_t data16_A[3];
	HAL_I2C_Mem_Read(&hi2c2,ADD, 0x3B,1, dataA,6,1000);
	data16_A[0] = (int16_t)(dataA[0] << 8 | dataA[1]);
	data16_A[1] = (int16_t)(dataA[2] << 8 | dataA[3]);
	data16_A[2] = (int16_t)(dataA[4] << 8 | dataA[5]);
	_IMU_data.ax = (float)data16_A[0]/16384.0;
	_IMU_data.ay = (float)data16_A[1]/16384.0;
	_IMU_data.az = (float)data16_A[2]/16384.0;


}

void readRawDataIMUTask::filter()
{
	//		float pitchG = _IMU_data.pitch + GX*(10000/1000000.0f);
	//		float rollG = _IMU_data.roll + GY*(10000/1000000.0f);
	//
	//		float pitchA = atan2(AY, sqrt(AX*AX + AZ * AZ))*RTD;
	//		float rollA = atan2(AX, sqrt(AY*AY + AZ*AZ))*RTD;
	//
	//		pitch = 0.98*pitchG + 0.02*pitchA;
	//		roll = 0.98*rollG + 0.02*rollA;
	//

}

