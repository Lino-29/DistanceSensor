#include <Arduino.h>
#include "NeoPixel.hpp"
#include "VL53L0X.hpp"
#include "SerialData.hpp"	
// #include <EnableInterrupt.h>

extern bool rangeEvent;						//Estado de interrupción
DistanceSensor MySensor;
serial_manager_c msg;
VL53L0X_RangingMeasurementData_t measure;

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

	
	MySensor.sensor_init();													//Inicializacion y configuracion de sensor
	MySensor.int_config();													//Configuración de las interrupciones del sensor
	MySensor.startMeasurement();											//Se habilita la toma de mediciones
	_delay_ms(100);
	attachInterrupt(1, Int_dist, FALLING);									//Se habilita el manejo de interrupciones por flanco de bajada.
	green_color;																//Color por defecto cuando no hay objeto dentro de los limites maximo y minimo del sensor 20 mm a 2000 mm
	msg.init_struct();
	Serial.print("Version de Firmware: ");
	Serial.println(FW_VERSION);
	MySensor.get_measure();
}

void loop() {
	
	if(msg.get_data()) {
		msg.get_message(MySensor);
	}

	if(msg.sensor_config_rady()) {
		MySensor.set_range(MySensor.get_high_limit(), MySensor.get_low_limit());
		Serial.println("Rango de umbral configurado");
		for(uint8_t i=0;i<3;i++) {
			violeta_color;
			_delay_ms(50);
			off_color;
			_delay_ms(50);
		}
	}
	
	//Se descrifra el area donde se encontró el objeto.
	if(rangeEvent){
		rangeEvent = false;

		MySensor.find_object();
		if(MySensor.get_in_range() && !MySensor.get_out_of_range()) {
			red_color;
			if(!msg.get_evento_dentro()) {
				Serial.println("\nObjeto detectado dentro de umbral\n");
				msg.set_evento_dentro(true);
				msg.set_evento_fuera(false);
			}
		} else if(!MySensor.get_in_range() && !MySensor.get_out_of_range()) {
			green_color;
			if(!msg.get_evento_fuera()) {
				Serial.println("\nObjeto fuera de umbral\n");
				msg.set_evento_dentro(false);
				msg.set_evento_fuera(true);
			}
		} else if(MySensor.get_out_of_range()){
			MySensor.set_out_of_range(false);
			blue_color;
		}
		MySensor.clearInterruptMask(false);
	}

	_delay_ms(150);
	
}