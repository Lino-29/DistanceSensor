#ifndef _SERIALDATA_HPP_
#define _SERIALDATA_HPP_

#include <Arduino.h>
#include "VL53L0X.hpp"
#include <math.h>

#define BUFFER_SIZE 15
#define FW_VERSION 1.1

//Estructura
struct serial_data_t {
    uint8_t bytes;
    uint8_t buffer[BUFFER_SIZE];
    bool lowLimit;
    bool highLimit;
    bool msg_complete;
};

class serial_manager_c {
    public:
        bool get_data(void);
        void init_struct(void);
        void ClearBuffer(void);
        void GetMessage(DistanceSensor &sensor);
        uint16_t Hex2Dec(char *character);
        // uint16_t Hex2Dec(uint8_t *value);
        bool sensor_config_rady(void);
    private:
        serial_data_t data;

};


#endif