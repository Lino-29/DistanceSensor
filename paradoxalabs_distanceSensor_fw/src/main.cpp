#include <Arduino.h>
#include "NeoPixel.hpp"
#include "VL53L0X.hpp"

bool rangeEvent = false;
DistanceSensor MySensor = DistanceSensor();
uint16_t measure = 0;

void Int_dist(void);
void GetEvent(void);

void setup() {
	pinMode(ledPin, OUTPUT);
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(PIND3, INPUT);
	pinMode(9, OUTPUT);
	Serial.begin(115200);

	while (! Serial) {
		delay(1);
	}
	digitalWrite(9, HIGH);

	
	MySensor.SensorInit();
	MySensor.IntConfig();
	MySensor.SetRange(250, 50);
	MySensor.setDeviceMode(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, true);
	// MySensor.setDeviceMode(VL53L0X_DEVICEMODE_SINGLE_RANGING, true);
	MySensor.startMeasurement();
	_delay_ms(100);
	attachInterrupt(1, Int_dist, FALLING);
	green_color;
}

void loop() {
	// green_color;

	/* digitalWrite(ledPin, HIGH);
	_delay_ms(100);
	digitalWrite(ledPin, LOW);
	_delay_ms(100); */

	// MySensor.MeasureDistance();
	// Serial.println("Debug 2");
	
	// if(rangeEvent){
	// 	rangeEvent = false;
	// 	Serial.println("Dentro de rango");
	// 	red_color;
	// }

	// Serial.println(digitalRead(3));
	// MySensor.MeasureDistance();
	if(rangeEvent){
		rangeEvent = false;
		VL53L0X_RangingMeasurementData_t measure;
		// Serial.print("Leyendo medicion... ");
		MySensor.getRangingMeasurement(&measure, false); // 
		if (measure.RangeStatus != 4 && measure.RangeMilliMeter <= 250 && measure.RangeMilliMeter >= 50) { 
			Serial.print("Distancia en mm: ");
			Serial.println(measure.RangeMilliMeter);
			red_color;
		} else if(measure.RangeStatus != 4 && measure.RangeMilliMeter != 8190) {
			green_color;
		}else {
			blue_color;
			// Serial.println(" out of range ");
		}
		MySensor.clearInterruptMask(false);
	}
	
	/* measure = MySensor.GetRange();
	if(measure >= 250 && measure != 8190) {
		Serial.println(measure);
		green_color;
	}else if(measure < 250 && measure >= 50) {
		red_color;
	}else {
		blue_color;
	} */
	// Serial.println(digitalRead(3));
	_delay_ms(150);
	
}

void Int_dist(void){
	rangeEvent = true;
}