#include "sensor_rpm.h"
#include <stdlib.h> /* atoi */
#include "Common.h"
#include "main.h"
/***********************************************************************************************************************
* static  Varible
***********************************************************************************************************************/
uint32_t rmp_per_second = 0;
uint8_t one_second_active = 0;
uint32_t previous_time = 0;
/***********************************************************************************************************************
* Public Functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name:  data_measure_process
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void rpm_sensor_process(void)
{
  // timer 1s for process
	switch (one_second_active) {
		case 0:
			previous_time = timer_get_tick();
			one_second_active = 1;
			break;
		case 1:
			if( timer_get_tick() - previous_time > 1000)
			{
				one_second_active = 0;
			    sensor_read.rpm = rmp_per_second * 60; // change second to minutes
			    rmp_per_second = 0;
			}
		default:
			break;
	}
}
/***********************************************************************************************************************
* Static Functions
***********************************************************************************************************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if( GPIO_Pin == RPM_SENSOR_Pin)
  {
    rmp_per_second++;
  }
}
/***********************************************************************************************************************
* Function Name:  batterry_lipo_measure
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/

/***********************************************************************************************************************
* End of file
***********************************************************************************************************************/