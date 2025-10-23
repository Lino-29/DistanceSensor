#include "VL53L0X.hpp"

bool rangeEvent = false;

DistanceSensor::DistanceSensor() : Adafruit_VL53L0X() {
	data_vl.low_limit_vl = 50;		//Límite bajo de umbral por defecto
	data_vl.high_limit_vl = 250;    //Límite alto de umbral por defecto
}

void DistanceSensor::sensor_init(void){
	Serial.println("Inicializando Sensor VL53L0X.");
	if (!begin()) {
		Serial.println(F("Falla en Sensor VL53L0X"));
		while(1);
	}else {
		Serial.println("Inicializacion Correcta\n");
	}

	setDeviceMode(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, false);	//Sensor configurado para tomar mediciones constantes
}

void DistanceSensor::get_measure(void){
	VL53L0X_RangingMeasurementData_t measure;

	Serial.println("Iniciando medicion");
	getRangingMeasurement(&measure, false);
	Serial.print("Distancia en mm: ");
	Serial.println(measure.RangeMilliMeter);
}

void DistanceSensor::set_range(uint16_t maxRange, uint16_t minRange){
	FixPoint1616_t LowThreashHold = (minRange * 65536.0);
  	FixPoint1616_t HighThreashHold = (maxRange * 65536.0);
	setInterruptThresholds(LowThreashHold, HighThreashHold, false);
}

void DistanceSensor::clear_int(void) {
	clearInterruptMask(true);
}

void DistanceSensor::int_config(void){
	// setGpioConfig(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, VL53L0X_GPIOFUNCTIONALITY_THRESHOLD_CROSSED_HIGH, VL53L0X_INTERRUPTPOLARITY_LOW);	//Configuracion de interrupcion cuando sale de rango
	setGpioConfig(VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, VL53L0X_GPIOFUNCTIONALITY_NEW_MEASURE_READY, VL53L0X_INTERRUPTPOLARITY_LOW);	//Configuracion de interrupcion con activo bajo e interrupcion en cada medición
}

void DistanceSensor::set_low_limit(uint16_t value) {
	data_vl.low_limit_vl = value;
}

void DistanceSensor::set_high_limit(uint16_t value) {
	data_vl.high_limit_vl = value;
}

uint16_t DistanceSensor::get_low_limit(void) {
	return data_vl.low_limit_vl;
}

uint16_t DistanceSensor::get_high_limit(void) {
	return data_vl.high_limit_vl;
}

void DistanceSensor::find_object(void) {
	VL53L0X_RangingMeasurementData_t measure;
	getRangingMeasurement(&measure, false); 
	if (measure.RangeStatus != 4 && measure.RangeMilliMeter <= get_high_limit() && measure.RangeMilliMeter >= get_low_limit()) { 
		// red_color;
		set_in_range(true);
		set_out_of_range(false);
		Serial.print("Distancia en mm: ");
		Serial.println(measure.RangeMilliMeter);
	} else if(measure.RangeStatus != 4 && measure.RangeMilliMeter < 8000) {
		set_in_range(false);
		set_out_of_range(false);
		// set_out_of_range(true);
		// green_color;
		// Serial.println("\nObjeto ha salido de Umbral\n");
	}else {
		set_out_of_range(true);
		// blue_color;
	}
}

void DistanceSensor::set_in_range(bool value) {
	data_vl.in_range_vl = value;
}

bool DistanceSensor::get_in_range(void) {
	return data_vl.in_range_vl;
}

void DistanceSensor::set_out_of_range(bool value) {
	data_vl.no_range_vl = value;
}

bool DistanceSensor::get_out_of_range(void) {
	return data_vl.no_range_vl;
}

//Función interrupción para VL53L0X
void Int_dist(void){
	rangeEvent = true;
}


