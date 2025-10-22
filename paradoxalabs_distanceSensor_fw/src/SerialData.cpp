#include "SerialData.hpp"


bool serial_manager_c::get_data(void) {
    data.bytes = Serial.available();
    
    if(data.bytes > 0) {
        Serial.println(data.bytes);
        for(uint8_t i=0; i<data.bytes; i++) {
            data.buffer[i] = Serial.read();
            Serial.print(data.buffer[i], 16);
            Serial.print(" - ");
            Serial.println(Serial.available());
        }

        Serial.println(Serial.available());

        if(data.buffer[0] == '<' && data.bytes > 1) {
            data.msg_complete = true;
            Serial.println("Mensaje recibido");
            return data.msg_complete;
        } else {
            memset(data.buffer, 0, BUFFER_SIZE);
            data.bytes = 0;
            data.msg_complete = false;
            return data.msg_complete;
        }
    } else return 0;

}

void serial_manager_c::init_struct(void) {
    data.bytes = 0;
    data.msg_complete = 0;
    data.highLimit = false;
    data.lowLimit = false;

    memset(data.buffer, 0, BUFFER_SIZE);
}

void serial_manager_c::ClearBuffer(void) {
    memset(data.buffer, 0, BUFFER_SIZE);
}

void serial_manager_c::GetMessage(DistanceSensor &sensor) {
    if(data.buffer[1] == 'S' && data.buffer[2] == 'L' && data.buffer[3] == 'L') {
        uint16_t value = ((uint16_t)data.buffer[4] << 8) | data.buffer[5];

        sensor.set_low_limit(value);
        data.lowLimit = true;
        Serial.print("Limite bajo de umbral recibido ");
        Serial.println(value);
        data.msg_complete = false;
        data.bytes = 0;
        Serial.flush();
    }else if(data.buffer[1] == 'S' && data.buffer[2] == 'H' && data.buffer[3] == 'L') {
        uint16_t value = ((uint16_t)data.buffer[4] << 8) | data.buffer[5];

        sensor.set_high_limit(value);
        data.highLimit = true;
        Serial.print("Limite alto de umbral recibido ");
        Serial.println(value);
        data.msg_complete = false;
        data.bytes = 0;
    }
}

bool serial_manager_c::sensor_config_rady(void) {
    if(data.highLimit && data.lowLimit) {
        data.highLimit = false;
        data.lowLimit = false;
        return true;
    } else {
        return false;
    }
}

uint16_t serial_manager_c::Hex2Dec(char *character){

    if(isdigit(character[0]) || character[0] == 48){
		return atoi(character);
	}else return 10 + (toupper(character[0]) - 'A');
}

/* uint16_t serial_manager_c::Hex2Dec(uint8_t *character){

    if(isdigit(character[0]) || character[0] == 48){
		return atoi(character);
	}else return 10 + (toupper(character[0]) - 'A');
} */