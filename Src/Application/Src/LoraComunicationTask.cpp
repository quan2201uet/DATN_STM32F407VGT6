#include <LoraComunicationTask.h>

LoraComunicationTask::LoraComunicationTask(uartAbstract * newUartProtocol)
{
	uartProtocol = newUartProtocol;
}

void LoraComunicationTask::init(void)
{

}


void LoraComunicationTask::startTask()
{
	QueueSetMemberHandle_t activeMember;
	for(;;)
	{
		activeMember = xQueueSelectFromSet(LoraTaskQueueSet, 10);
		processTask(activeMember);
	}
}

void LoraComunicationTask::processTask(QueueSetMemberHandle_t activeMember)
{
	if(activeMember == semaLoraComunicationTask)
	{
		xSemaphoreTake(semaLoraComunicationTask, 10); // gửi bản tin với tần số 1HZ
		static uint8_t sequence = 0;
		sequence++;
		uint8_t Lora_TX_Buffer[100];
		uint8_t len = build_frame(SYSTEM_ID, _Lora_data, sizeof(mavlink_sensor_data_t), sequence, Lora_TX_Buffer);
		//		len_encoded = mavlink_msg_sensor_data_encode(SYSTEM_ID, COMPONENT_ID, &msg, &_Lora_data);
		//
		//		len_encoded = mavlink_msg_to_send_buffer(tx_mavlink_buffer, &msg);

		if (len > 0)
		{
			//uartProtocol->sendData(tx_mavlink_buffer, len_encoded);
			HAL_UART_Transmit(&huart1, Lora_TX_Buffer, len, 100);
		}
	}
	else if(activeMember == QueueBMEToLora)
	{
		getBMEDataFromQueue();
	}
	else if (activeMember == QueueGPSToLora)
	{
		getGPSDataFromQueue();
	}
	else if (activeMember == QueueIMUToLora)
	{
		getIMUDataFromQueue();
	}

}


/* USER FUNCTION CODE BEGIN */
void LoraComunicationTask::getBMEDataFromQueue()
{
	BME_data_t _BME_data;
	if(xQueueReceive(QueueBMEToLora, &_BME_data, 10) == pdPASS)
	{
		_Lora_data.temperature  = _BME_data.temp;
		_Lora_data.pressure     = _BME_data.press;
	}
}

void LoraComunicationTask::getGPSDataFromQueue()
{
	GPS_data_t _GPS_data;
	if(xQueueReceive(QueueGPSToLora, &_GPS_data, 10) == pdPASS)
	{
		_Lora_data.utc_time  = _GPS_data.timeUTC;
		_Lora_data.latitude  = _GPS_data.lat;
		_Lora_data.longitude = _GPS_data.lon;
		_Lora_data.speed     = _GPS_data.speed;
		_Lora_data.course    = _GPS_data.course;
		_Lora_data.distance  = _GPS_data.distance;
	}
}
void LoraComunicationTask::getIMUDataFromQueue()
{
	IMU_data_t _IMU_data;
	if(xQueueReceive(QueueIMUToLora, &_IMU_data, 10) == pdPASS)
	{
		_Lora_data.acc_x  = _IMU_data.ax;
		_Lora_data.acc_y  = _IMU_data.ay;
		_Lora_data.acc_z  = _IMU_data.az;

		_Lora_data.gyro_x = _IMU_data.gx;
		_Lora_data.gyro_y = _IMU_data.gy;
		_Lora_data.gyro_z = _IMU_data.gz;

		_Lora_data.roll = _IMU_data.roll;
		_Lora_data.pitch = _IMU_data.pitch;
	}
}




uint16_t LoraComunicationTask::crc16(uint8_t *data, uint16_t len)
{
	uint16_t crc = 0xFFFF;

	for (uint16_t i = 0; i < len; i++) {
		crc ^= data[i];

		for (uint8_t j = 0; j < 8; j++) {
			if (crc & 1)
				crc = (crc >> 1) ^ 0xA001;
			else
				crc >>= 1;
		}
	}
	return crc;
}

uint16_t LoraComunicationTask:: build_frame(uint8_t msg_id,
		mavlink_sensor_data_t payload,
		uint8_t payload_len,
		uint8_t sequence,
		uint8_t *out)
{
	uint16_t index = 0;

	// 1. Start bytes (2)
	out[index++] = 0xAA;
	out[index++] = 0x55;

	// 2. Data length (1)
	out[index++] = payload_len;

	// 3. Sequence (1 byte)
	out[index++] = sequence;

	// 4. Message ID (1)
	out[index++] = msg_id;

	// ---- CRC_H: tính từ byte 0 đến byte 4 (AA 55 LEN SEQ MSGID) ----
	uint16_t crc_h = crc16(out, index);

	out[index++] = (uint8_t)(crc_h & 0xFF);      // CRC_H low
	out[index++] = (uint8_t)(crc_h >> 8);        // CRC_H high

	// 5. Payload
	memcpy(&out[index], &payload, payload_len);
	index += payload_len;

	// ---- CRC_FRS cho toàn bộ frame (trừ CRC cuối) ----
	uint16_t crc_f = crc16(out, index);

	out[index++] = (uint8_t)(crc_f & 0xFF);      // CRC_FRS low
	out[index++] = (uint8_t)(crc_f >> 8);        // CRC_FRS high

	return index;
}
/* USER FUNCTION CODE END */



