#include "adc_driver.h"
#include "uart_com.h"
#include <stdlib.h> /* atoi */
#include "Common.h"

/***********************************************************************************************************************
* static  Varible
***********************************************************************************************************************/

/***********************************************************************************************************************
* Public Functions
***********************************************************************************************************************/
volatile uint16_t adc_value[ADC_CHANNEL_COUNT];
volatile uint16_t adc_buffer_sample[ADC_CHANNEL_COUNT * ADC_SAMPLE_COUNT];

extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim3;


#define TIMER_TRIGGER               htim3
/***********************************************************************************************************************
* public Functions
***********************************************************************************************************************/

//void adc_init(void)
//{
//  /* USER CODE BEGIN ADC1_Init 0 */
//
//  /* USER CODE END ADC1_Init 0 */
//
//  ADC_ChannelConfTypeDef sConfig = {0};
//
//  /* USER CODE BEGIN ADC1_Init 1 */
//
//  /* USER CODE END ADC1_Init 1 */
//  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
//  */
//  hadc1.Instance = ADC1;
////  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
//  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
//  hadc1.Init.ScanConvMode = ENABLE;
//  hadc1.Init.ContinuousConvMode = DISABLE;
//  hadc1.Init.DiscontinuousConvMode = DISABLE;
//  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
//  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
//  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
//  hadc1.Init.NbrOfConversion = 3;
//  hadc1.Init.DMAContinuousRequests = ENABLE;
//  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
//  if (HAL_ADC_Init(&hadc1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_0;
//  sConfig.Rank = 1;
////  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_1;
//  sConfig.Rank = 2;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//  */
//  sConfig.Channel = ADC_CHANNEL_8;
//  sConfig.Rank = 3;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}
/***********************************************************************************************************************
* Function Name:  vsm_protocol_cmd_handler
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    uint16_t i = 0, j = 0;
    uint32_t sumTmp = 0;
    HAL_TIM_Base_Stop(&TIMER_TRIGGER);
    for(j = 0; j < ADC_CHANNEL_COUNT; j++) {
        sumTmp = 0;
        for(i = 0; i < ADC_SAMPLE_COUNT; i++)
        {
            sumTmp += adc_buffer_sample[i * ADC_CHANNEL_COUNT + j]; // 0 3 6 9 12
        }
        adc_value[j] = sumTmp / ADC_SAMPLE_COUNT;
    }
    adc_start_process();
}
/***********************************************************************************************************************
* Function Name:  vsm_protocol_cmd_handler
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void adc_start_process(void)
{
    HAL_ADC_Start_DMA(&hadc, (uint32_t*)&adc_buffer_sample, ADC_CHANNEL_COUNT * ADC_SAMPLE_COUNT);
    HAL_TIM_Base_Start(&TIMER_TRIGGER);
}
/***********************************************************************************************************************
* Function Name:  vsm_protocol_cmd_handler
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
uint16_t* adc_get_sample(void)
{
    return (uint16_t*)adc_value;
}

/***********************************************************************************************************************
* Static Functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* End of file
***********************************************************************************************************************/
