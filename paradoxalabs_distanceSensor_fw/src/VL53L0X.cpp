#include "VL53L0X.hpp"

DistanceSensor::DistanceSensor() : Adafruit_VL53L0X() {}

void DistanceSensor::SensorInit(void){
	Serial.println("Debug 1");
	Serial.println("Sensor VL53L0X Inicializando.");
	if (!begin()) {
		Serial.println(F("Falla Sensor VL53L0X"));
		while(1);
	}else {
		Serial.println("Inicializacion completa");
	}
}

void DistanceSensor::StartMeasure(void){
	/* Serial.println(F("VL53L0X startRangeContinuous\n\n"));

	sensor.startRangeContinuous(); */

	Serial.println("Iniciando medicion");
	startMeasurement(true);
}

void DistanceSensor::MeasureDistance(void){
	if(isRangeComplete()) {
		Serial.print("Distancia en mm: ");
		Serial.println(readRange());
	}/* else{
		Serial.print("Not complete");
		sensor.waitRangeComplete();
	} */
}

void DistanceSensor::SetRange(uint16_t maxRange, uint16_t minRange){
	FixPoint1616_t LowThreashHold = (minRange * 65536.0);
  	FixPoint1616_t HighThreashHold = (maxRange * 65536.0);
	setInterruptThresholds(LowThreashHold, HighThreashHold, true);
	// sensor.setInterruptThresholds(minRange, maxRange, true);
}

bool DistanceSensor::IsRange(bool range){
	
}

void DistanceSensor::ClearInt(void) {
	clearInterruptMask(true);
}

void DistanceSensor::IntConfig(void){
	// setGpioConfig(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, VL53L0X_GPIOFUNCTIONALITY_THRESHOLD_CROSSED_HIGH, VL53L0X_INTERRUPTPOLARITY_LOW);
	setGpioConfig(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, VL53L0X_GPIOFUNCTIONALITY_NEW_MEASURE_READY, VL53L0X_INTERRUPTPOLARITY_LOW);
	// setDeviceMode(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, true);
}

uint16_t DistanceSensor::GetRange(void) {
	// return sensor.readRange();

	VL53L0X_RangingMeasurementData_t measure; // keep our own private copy

	Status = getSingleRangingMeasurement(&measure, false);
// _	sensor._rangeStatus = measure.RangeStatus;

	if (Status == VL53L0X_ERROR_NONE)
		return measure.RangeMilliMeter;
	// Other status return something totally out of bounds...
	return 0xffff;
}

