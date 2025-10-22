#ifndef _VL53L0X_HPP_
#define _VL53L0X_HPP_

#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

// bool rangeEvent = false;

void Int_dist(void);

class DistanceSensor : public Adafruit_VL53L0X{
	public:
		DistanceSensor();
		bool IsRange(bool range);
		void MeasureDistance(void);
		void StartMeasure(void);
		void SetRange(uint16_t maxRange, uint16_t minRange);
		void ClearInt(void);
		void IntConfig(void);
		void SensorInit(void);
		uint16_t GetRange(void);

		void set_low_limit(uint16_t value);
		void set_high_limit(uint16_t value);
		uint16_t get_low_limit(void);
		uint16_t get_high_limit(void);
	private:

		// Adafruit_VL53L0X sensor;
		uint16_t distance_mm;
		uint16_t lowLimit;
		uint16_t highLimit;
		bool range;
		bool intFlag;
};

#endif


