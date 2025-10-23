#ifndef _SERIALDATA_HPP_
#define _SERIALDATA_HPP_

#include <Arduino.h>
#include "VL53L0X.hpp"
#include <math.h>

#define BUFFER_SIZE 15
#define FW_VERSION 1.20

//Estructura
typedef struct {
    uint8_t bytes;
    uint8_t buffer[BUFFER_SIZE];
    bool lowLimit;
    bool highLimit;
    bool msg_complete;
    bool evento_dentro;
    bool evento_fuera;
}serial_data_t;

class serial_manager_c {
    public:
        bool get_data(void);
        void init_struct(void);
        void ClearBuffer(void);
        void get_message(DistanceSensor &sensor);
        bool sensor_config_rady(void);
        void set_evento_dentro(bool value);
        bool get_evento_dentro(void);
        void set_evento_fuera(bool value);
        bool get_evento_fuera(void);
    private:
        serial_data_t data;

};


#endif