#include "SerialData.hpp"


bool serial_manager_c::get_data(void) {
    data.bytes = Serial.available();
    
    if(data.bytes > 0) {
        Serial.println(data.bytes);
        for(uint8_t i=0; i<data.bytes; i++) {
            data.buffer[i] = Serial.read();
            Serial.print(data.buffer[i]);
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
        sensor.set_low_limit(40);
        data.lowLimit = true;
        Serial.println("Limite bajo de umbral recibido");
        data.msg_complete = false;
        data.bytes = 0;
        Serial.flush();
    }else if(data.buffer[1] == 'S' && data.buffer[2] == 'H' && data.buffer[3] == 'L') {
        sensor.set_high_limit(250);
        data.highLimit = true;
        Serial.println("Limite altro de umbral recibido");
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

