#ifndef BLE_COM_H_
#define BLE_COM_H_
#ifdef __cplusplus
extern "C"
{
#endif
 #include "stm32l1xx_hal.h"
//#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "main.h"

void ble_com_init(void);

void ble_hanlder_loop(void);

void ble_com_send_interval();
#ifdef __cplusplus
}
#endif
#endif /* BLE_COM_H_ */
