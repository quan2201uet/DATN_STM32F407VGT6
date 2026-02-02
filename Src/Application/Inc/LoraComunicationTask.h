#ifndef INC_LORACOMUNICATIONTASK_H_
#define INC_LORACOMUNICATIONTASK_H_

#include "common.h"
#include <cstring>
#include "uartAbstract.h"

/* BEGIN INCLUE DEFINE */
#define SYSTEM_ID           20       // ID của thiết bị (STM32)
#define COMPONENT_ID        1        // ID của thành phần
#define MAVLINK_MAX_TX_BUFFER_LEN 30
/* END INCLUE DEFINE */

class LoraComunicationTask
{

public:
	LoraComunicationTask(uartAbstract * newUartProtocol);
	~LoraComunicationTask();
	void init(void);

	void startTask();

private:
	uartAbstract* uartProtocol {nullptr};
	mavlink_sensor_data_t _Lora_data;
	void getBMEDataFromQueue();
	void getGPSDataFromQueue();
	void getIMUDataFromQueue();
	void getPM25DataFromQueue();
	void processTask(QueueSetMemberHandle_t activeMember);

	uint16_t crc16(uint8_t *data, uint16_t len);
	uint16_t build_frame(uint8_t msg_id,
			mavlink_sensor_data_t payload,
			uint8_t payload_len,
			uint8_t sequence,
			uint8_t *out);

};

#endif /* INC_LORACOMUNICATIONTASK_H_ */
