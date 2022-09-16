#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

 #include "stm32l1xx_hal.h"
//#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "string.h"
#include "main.h"
#include "Common.h"
#define ADC_SAMPLE_COUNT            (5)
#define ADC_CHANNEL_COUNT           E_END_OF_ENUM //(4)//(8)

// #define PRESSURE_PROXIMAL_IDX       (0)
// #define PRESSURE_INTERNAL_IDX       (1)
// #define PRESSURE_VALVE_IDX          (2)
// #define FLOW_INHALE_IDX             (3)
// #define FLOW_EXHALE_IDX             (4)

#define ADC_VREF_MV                 3282
#define ADC_SCALE                   1.47f
#define ADC_RESOLUTION              4095
#define ADC_SCALE_FLOW              2



void adc_start_process(void);

uint16_t* adc_get_sample(void);


#endif /* ADC_DRIVER_H_ */
