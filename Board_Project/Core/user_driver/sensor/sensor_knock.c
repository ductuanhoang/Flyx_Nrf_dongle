#include "sensor_knock.h"
#include "uart_com.h"
#include <stdlib.h> /* atoi */
#include "Common.h"
#include "adc_driver.h"

/***********************************************************************************************************************
* static  Varible
***********************************************************************************************************************/
#define kSPU_SET_PRESCALAR_6MHz 0b01000100      /* 6MHz prescalar with SDO active */
#define kSPU_SET_CHANNEL_1 0b11100000           /* Setting active channel to 1 */
#define kSPU_SET_CHANNEL_2 0b11100001           /* Setting active channel to 2 */
#define kSPU_SET_BAND_PASS_FREQUENCY 0b00101010 /* Setting band pass frequency to 7.27kHz */
#define kSPU_SET_PROGRAMMABLE_GAIN 0b10100010   /* Setting programmable gain to 0.381 */
#define kSPU_SET_INTEGRATOR_TIME 0b11001010     /* Setting programmable integrator time constant to 100µs */
#define kKNOCK_THRESHOLD_LEVEL 204              /* Setting knock LED level, max value of 255. */
#define kMEASUREMENT_WINDOW_TIME 3000           /* Defining the time window of measurement to 3ms. */

#define kHIGH 1
#define kLOW 0

static uint8_t COM_SPI(uint8_t TX_data);

static bool user_spi_init(void);
static void user_spi_cs_set(void);

static void user_spi_cs_clear(void);
static void knock_sensor_hold_pin( uint8_t status);

static void sensor_knock_set_channel_1(void);
static void sensor_knock_set_channel_2(void);

static void sensor_knock_read_channel_1(void);
static void sensor_knock_read_channel_2(void);
static void sensor_knock_read_channel_1(void);
static void sensor_knock_read_channel_2(void);

static uint32_t knock_sensor_tick_count = 0;
static uint8_t knock_sensor_state = 0;
/***********************************************************************************************************************
* Public Functions
***********************************************************************************************************************/
extern SPI_HandleTypeDef hspi2;
/***********************************************************************************************************************
* Function Name:  vsm_protocol_cmd_handler
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
bool knock_sensor_init(void)
{
    bool status = false;
    // init user spi
    status = user_spi_init();
    osDelay(10);
    //Configure SPU.
    APP_LOGD("Configuring SPU: 0x%x", COM_SPI(kSPU_SET_PRESCALAR_6MHz));
    APP_LOGD(", 0x%x", COM_SPI(kSPU_SET_BAND_PASS_FREQUENCY));
    APP_LOGD(", 0x%x", COM_SPI(kSPU_SET_PROGRAMMABLE_GAIN));
    APP_LOGD(", 0x%x", COM_SPI(kSPU_SET_INTEGRATOR_TIME));
    APP_LOGD("\n\r");
    return status;
}

/***********************************************************************************************************************
* Function Name:  vsm_protocol_cmd_handler
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void knock_sensor_process(void)
{
    switch (knock_sensor_state)
    {
    case 0:
    {
        knock_sensor_state = 1;
        knock_sensor_tick_count = timer_get_tick(); // tick for 1ms
        sensor_knock_set_channel_1();
        break;
    }
    case 1: // read channel 1
    {
        if (timer_get_tick() - knock_sensor_tick_count > 3)
        {
            knock_sensor_state = 0;
            knock_sensor_tick_count = timer_get_tick();
            // read sensor channel 1
            sensor_knock_read_channel_1();
            // set sensor channel 2
//            sensor_knock_set_channel_2();
        }
    }
    break;
    case 2:
    {
        if (timer_get_tick() - knock_sensor_tick_count > 3)
        {
            knock_sensor_state = 0;
            knock_sensor_tick_count = timer_get_tick();
            // read channel 2
            sensor_knock_read_channel_2();
//            APP_LOGD("send message to device");
        }
    }
    break;
    default:
        break;
    }
}

/***********************************************************************************************************************
* Static Functions
***********************************************************************************************************************/
static void sensor_knock_set_channel_1(void)
{
    //Set channel 1.
    COM_SPI(kSPU_SET_CHANNEL_1);

    //The measurement window starts by driving digital pin 4 high.
    knock_sensor_hold_pin(kHIGH);

    //The SPU performs the integration process and increases the output voltage based on the signal processing result.
//    osDelay(kMEASUREMENT_WINDOW_TIME / 1000);
}

static void sensor_knock_read_channel_1(void)
{
    //The measurement window ends by driving digital pin 4 low. The SPU stops the integration process and the output voltage is frozen until the window starts again.
    knock_sensor_hold_pin(kLOW);

    //The SPU output voltage is read by the Arduino ADC on analogue input pin 0.
    uint16_t adcChannel1 = adc_get_sample()[E_KNOCK_SENSOR];
    float knockChannel1 = ((float)adcChannel1 / 4095) * 100 * 2 / 3;
    sensor_read.knock_sensor_channel_1 = (uint16_t)knockChannel1;
}

static void sensor_knock_set_channel_2(void)
{
    //Set channel 2.
    COM_SPI(kSPU_SET_CHANNEL_2);

    //The measurement window starts by driving digital pin 4 high.
    knock_sensor_hold_pin(kHIGH);

    //The SPU performs the integration process and increases the output voltage based on the signal processing result.
    // delayMicroseconds(MEASUREMENT_WINDOW_TIME);
}

static void sensor_knock_read_channel_2(void)
{
    //The measurement window ends by driving digital pin 4 low. The SPU stops the integration process and the output voltage is frozen until the window starts again.
    knock_sensor_hold_pin(kLOW);

    //The SPU output voltage is read by the Arduino ADC on analogue input pin 0.
    uint16_t adcChannel2 = adc_get_sample()[E_KNOCK_SENSOR];

    //Convert ADC-values to percentages.
    float knockChannel2 = ((float)adcChannel2 / 4095) * 100;
    sensor_read.knock_sensor_channel_2 = knockChannel2;
}
//Function for transfering SPI data to the SPU.
static uint8_t COM_SPI(uint8_t TX_data)
{
    uint8_t Response = 0x00;
    HAL_StatusTypeDef ret = HAL_OK;
    //Configure SPI for knock controller.
    // SPI.setDataMode(SPI_MODE1);
    // SPI.setClockDivider(kSPI_CLOCK_DIV16);

    //Set chip select pin low, chip in use.
    user_spi_cs_clear();

    //Transmit request.
    // uint8_t Response =  SPI.transfer(TX_data);
    ret = HAL_SPI_TransmitReceive(&hspi2, &TX_data, &Response, 1, 100);
    if (ret != HAL_OK)
    {
    	APP_LOGD("ret = %d", ret);
    }
    //Set chip select pin high, chip not in use.
    user_spi_cs_set();

    return Response;
}
/***********************************************************************************************************************
* Function Name:  vsm_protocol_cmd_handler
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static bool user_spi_init(void)
{
    return true;
}
/***********************************************************************************************************************
* Function Name:  vsm_protocol_cmd_handler
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
//static uint8_t user_spi_send(uint8_t data)
//{
//}
static void knock_sensor_hold_pin( uint8_t status)
{
	if( status == kHIGH)
		HAL_GPIO_WritePin(KNOCK_HOLD_GPIO_Port, KNOCK_HOLD_Pin, GPIO_PIN_SET);
	else if( status == kLOW)
		HAL_GPIO_WritePin(KNOCK_HOLD_GPIO_Port, KNOCK_HOLD_Pin, GPIO_PIN_RESET);
}
///***********************************************************************************************************************
//* Function Name:  vsm_protocol_cmd_handler
//* Description  :
//* Arguments    : none
//* Return Value : none
//***********************************************************************************************************************/
static void user_spi_cs_set(void)
{
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
}
///***********************************************************************************************************************
//* Function Name:  vsm_protocol_cmd_handler
//* Description  :
//* Arguments    : none
//* Return Value : none
//***********************************************************************************************************************/
static void user_spi_cs_clear(void)
{
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
}

/***********************************************************************************************************************
* End of file
***********************************************************************************************************************/
