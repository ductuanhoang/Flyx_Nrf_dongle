#ifndef SENSOR_RPM_PROCESS_H_
#define SENSOR_RPM_PROCESS_H_

 #include "stm32l1xx_hal.h"
//#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "main.h"

void rpm_sensor_process(void);

void rpm_sensor_1sflag_active(void);
#endif /* SENSOR_BASE_PROCESS_H_ */
