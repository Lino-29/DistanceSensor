#ifndef _VL53L0X_HPP_
#define _VL53L0X_HPP_

#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

typedef struct {
	uint16_t distance_mm_vl;
	uint16_t low_limit_vl;
	uint16_t high_limit_vl;
	bool in_range_vl;
	bool no_range_vl;
} sensor_data_t;

void Int_dist(void);

class DistanceSensor : public Adafruit_VL53L0X{
	public:
		DistanceSensor();
		void get_measure(void);
		void set_range(uint16_t maxRange, uint16_t minRange);
		void clear_int(void);
		void int_config(void);
		void sensor_init(void);

		void set_low_limit(uint16_t value);
		void set_high_limit(uint16_t value);
		uint16_t get_low_limit(void);
		uint16_t get_high_limit(void);
		void find_object(void);
		void set_in_range(bool value);
		bool get_in_range(void);
		void set_out_of_range(bool value);
		bool get_out_of_range(void);
	private:

		sensor_data_t data_vl;
};

#endif


