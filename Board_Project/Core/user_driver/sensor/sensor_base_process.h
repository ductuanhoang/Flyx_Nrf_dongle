#ifndef SENSOR_BASE_PROCESS_H_
#define SENSOR_BASE_PROCESS_H_
#ifdef __cplusplus
extern "C"
{
#endif
 #include "stm32l1xx_hal.h"
//#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "main.h"


void sensor_measure_process(void);
int32_t oild_pressuare_table(float resistance); // for test
#ifdef __cplusplus
}
#endif

#endif /* SENSOR_BASE_PROCESS_H_ */
