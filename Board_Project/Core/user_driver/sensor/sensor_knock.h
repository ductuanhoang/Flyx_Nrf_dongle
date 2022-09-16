#ifndef SENSOR_KNOCK_H_
#define SENSOR_KNOCK_H_

 #include "stm32l1xx_hal.h"
//#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"
#include "main.h"

bool knock_sensor_init(void);
void knock_sensor_process(void);

#endif /* SENSOR_KNOCK_H_ */
