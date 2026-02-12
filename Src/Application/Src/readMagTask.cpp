#include "common.h"
#include "readMagTask.h"
#include <cstring>
#include <algorithm>
#include <climits>

constexpr float MIN_RANGE = 400.0f;
constexpr uint32_t MAG_CALIB_MAGIC = 0x4D414743;
constexpr uint32_t FLASH_ADDR   = 0x080E0000UL;   // Sector 11
constexpr uint32_t FLASH_SECTOR = FLASH_SECTOR_11;

readMagTask::readMagTask(qmc5883l* newMag)
{
	mMagInstance = newMag;
}

readMagTask::~readMagTask()
{
}

bool readMagTask::init()
{
	if(!mMagInstance->init()) return false;

	if(!loadCalib()) calibrate();

	return true;
}

void readMagTask::startTask()
{
	for(;;)
	{
		xSemaphoreTake(semaReadMagTask, portMAX_DELAY);
		processTask();
	}
}

void readMagTask::processTask()
{
	Mag_raw_t rawdata;
	Mag_data_t dataOut;

	if(readRaw(&rawdata))
	{
		applyCalib(&rawdata, &dataOut);
		sendDataToEKF(&dataOut);
	}
}

void readMagTask::applyCalib(const Mag_raw_t* raw, Mag_data_t* out)
{
	if (!raw || !out)
		return;

	float mx = (static_cast<float>(raw->mx_raw) - mCalib.offset_x) * mCalib.scale_x;
	float my = (static_cast<float>(raw->my_raw) - mCalib.offset_y) * mCalib.scale_y;
	float mz = (static_cast<float>(raw->mz_raw) - mCalib.offset_z) * mCalib.scale_z;

	float norm = sqrtf(mx*mx + my*my + mz*mz);

	if (norm > 1e-6f)
	{
		mx /= norm;
		my /= norm;
		mz /= norm;
	}

	out->mx = mx;
	out->my = my;
	out->mz = mz;
}

void readMagTask::sendDataToEKF(const Mag_data_t* data)
{
	if(xQueueSend(queueMagToEKF, &data, 10)){}
}

bool readMagTask::readRaw(Mag_raw_t* rawData)
{
	return mMagInstance->readRawData(rawData);
}

void readMagTask::calibrate()
{
	int16_t minVal[3] = { INT16_MAX, INT16_MAX, INT16_MAX };
	int16_t maxVal[3] = { INT16_MIN, INT16_MIN, INT16_MIN };
	Mag_raw_t raw;
	for (int i = 0; i < 3000; i++)
	{
		if (readRaw(&raw))
		{

			minVal[0] = std::min<int16_t>(minVal[0], raw.mx_raw);
			maxVal[0] = std::max<int16_t>(maxVal[0], raw.mx_raw);

			minVal[1] = std::min<int16_t>(minVal[1], raw.my_raw);
			maxVal[1] = std::max<int16_t>(maxVal[1], raw.my_raw);

			minVal[2] = std::min<int16_t>(minVal[2], raw.mz_raw);
			maxVal[2] = std::max<int16_t>(maxVal[2], raw.mz_raw);

		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}

	mCalib.offset_x = (maxVal[0] + minVal[0]) * 0.5f;
	mCalib.offset_y = (maxVal[1] + minVal[1]) * 0.5f;
	mCalib.offset_z = (maxVal[2] + minVal[2]) * 0.5f;

	float dx = (maxVal[0] - minVal[0]) * 0.5f;
	float dy = (maxVal[1] - minVal[1]) * 0.5f;
	float dz = (maxVal[2] - minVal[2]) * 0.5f;

	if (dx < MIN_RANGE || dy < MIN_RANGE || dz < MIN_RANGE) {
		// calib fail → dùng default calib hoặc báo lỗi
		mCalib.scale_x = mCalib.scale_y = mCalib.scale_z = 1.0f;
		mCalib.offset_x = mCalib.offset_y = mCalib.offset_z = 0.0f;
	}else {
		float avg = (dx + dy + dz) / 3.0f;
		mCalib.scale_x = avg / dx;
		mCalib.scale_y = avg / dy;
		mCalib.scale_z = avg / dz;
	}

	saveCalib();
}

bool readMagTask::saveCalib()
{
	HAL_FLASH_Unlock();

	FLASH_EraseInitTypeDef eraseInit{};
	uint32_t sectorError = 0;

	eraseInit.TypeErase    = FLASH_TYPEERASE_SECTORS;
	eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	eraseInit.Sector       = FLASH_SECTOR;
	eraseInit.NbSectors    = 1;

	if (HAL_FLASHEx_Erase(&eraseInit, &sectorError) != HAL_OK)
	{
		HAL_FLASH_Lock();
		return false;
	}

	mCalib.magic = MAG_CALIB_MAGIC;

	const uint32_t* data =
			reinterpret_cast<const uint32_t*>(&mCalib);

	uint32_t address = FLASH_ADDR;

	for (size_t i = 0; i < sizeof(Mag_calib_t)/4; i++)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,
				address,
				data[i]) != HAL_OK)
		{
			HAL_FLASH_Lock();
			return false;
		}

		address += 4;
	}

	HAL_FLASH_Lock();
	return true;
}

bool readMagTask::loadCalib()
{
	const Mag_calib_t* flash = reinterpret_cast<const Mag_calib_t*>(FLASH_ADDR);

	if (flash->magic != MAG_CALIB_MAGIC)
		return false;

	std::memcpy(&mCalib, flash, sizeof(Mag_calib_t));

	return true;
}




