#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "Arduino.h"

typedef struct DataNode
{
    float vol;
    float current;
    float power;
    float energy;
    float frequency;
    float pf;
    float water_volume;
}DataNode;

extern DataNode _Data;

extern uint16_t _time_screen, _time_read_data;

extern uint8_t _counter_time_elapsed;

#endif /* INC_GLOBAL_H_ */
