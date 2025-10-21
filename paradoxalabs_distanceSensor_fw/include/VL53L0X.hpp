#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

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
	private:

		// Adafruit_VL53L0X sensor;
		uint16_t distance_mm;
		bool range;
};



