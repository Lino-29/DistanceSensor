#include <Arduino.h>
#include "NeoPixel.hpp"
#include "VL53L0X.hpp"
#include "SerialData.hpp"	
// #include <EnableInterrupt.h>

extern bool rangeEvent;
DistanceSensor MySensor;
serial_manager_c msg;
// uint16_t measure = 0;
// uint8_t buffer[15] = {0};

void setup() {
	pinMode(ledPin, OUTPUT);
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(PIND3, INPUT);
	pinMode(8, OUTPUT);
	Serial.begin(115200);

	while (! Serial) {
		delay(1);
	}
	digitalWrite(8, HIGH);

	
	MySensor.SensorInit();
	MySensor.IntConfig();
	MySensor.SetRange(100, 50);
	MySensor.setDeviceMode(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, true);
	// MySensor.setDeviceMode(VL53L0X_DEVICEMODE_SINGLE_RANGING, true);
	MySensor.startMeasurement();
	_delay_ms(100);
	attachInterrupt(1, Int_dist, FALLING);
	// enableInterrupt(10, Int_dist, CHANGE);
	green_color;
	msg.init_struct();
}

void loop() {
	
	if(msg.get_data()) {

		msg.GetMessage(MySensor);
		
	}

	if(msg.sensor_config_rady()) {
		MySensor.SetRange(MySensor.get_high_limit(), MySensor.get_low_limit());
		Serial.println("Rangos Configurados");
	}
	
	if(rangeEvent){
		rangeEvent = false;
		VL53L0X_RangingMeasurementData_t measure;
		MySensor.getRangingMeasurement(&measure, false); 
		if (measure.RangeStatus != 4 && measure.RangeMilliMeter <= 100 && measure.RangeMilliMeter >= 50) { 
			Serial.print("Distancia en mm: ");
			Serial.println(measure.RangeMilliMeter);
			red_color;
		} else if(measure.RangeStatus != 4 && measure.RangeMilliMeter < 8000) {
			green_color;
		}else {
			blue_color;
		}
		MySensor.clearInterruptMask(false);
	}

	_delay_ms(150);
	
}