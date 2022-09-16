#include "sensor_base_process.h"
#include <stdlib.h> /* atoi */
#include "Common.h"
#include "adc_driver.h"
#include "sensor_rpm.h"
#include "sensor_knock.h"
#include "vsm_rise_compute.h"
/***********************************************************************************************************************
* static  Varible
***********************************************************************************************************************/
#define kVCC                            (3300) //(mini Volt)
#define kADC_SENSOR_SCALE               (1.0f * kVCC /4095.0f)

/* VBAT measure
 VBAT
  |
 [ ] R_BAT_CONST_01
  |
  --------- v_measure
  |
 [ ] R_BAT_CONST_02
  |
 GND
*/

#define kVBAT_LP_REF            3900 // (mini Volt) for full charger
#define kVBAT_R_BAT_CONST_01    316 // kOmh
#define kVBAT_R_BAT_CONST_02    47 // kOmh

/* ADC_VCHG_IN measure
 VH_VBAT
  |
 [ ] R_CONST_01
  |
  --------- v_measure
  |
 [ ] R_CONST_02
  |
 GND
*/
#define kVBAT_R_BAT_CHG_CONST_01    100 // kOmh
#define kVBAT_R_BAT_CHG_CONST_02    10 // kOmh


//OIL_PRESSURE_SENDER
#define kR_PRESSURE_SENDER          (0)
/***********************************************************************************************************************
* Public Functions
***********************************************************************************************************************/

static void batterry_lipo_measure(void);
static void batterry_charging_measure(void);
static void pressure_sender_measure(void);

/***********************************************************************************************************************
* Function Name:  data_measure_process
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void sensor_measure_process(void)
{
    batterry_lipo_measure();
    batterry_charging_measure();
    pressure_sender_measure();
    // read rpm ad knock sensor
	rpm_sensor_process();
	knock_sensor_process();
}

/***********************************************************************************************************************
* Static Functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name:  batterry_lipo_measure
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void batterry_lipo_measure(void)
{
    uint16_t volt_lipo_adc_raw = 0;
    volt_lipo_adc_raw = adc_get_sample()[E_VBAT_LIPO];
    sensor_read.fVbat_lipo =	(uint16_t)(((volt_lipo_adc_raw * kADC_SENSOR_SCALE) * (kVBAT_R_BAT_CONST_02 + kVBAT_R_BAT_CONST_01)) / kVBAT_R_BAT_CONST_02);
}

/***********************************************************************************************************************
* Function Name:  batterry_charging_measure
* Description  :
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
static void batterry_charging_measure(void)
{
    uint16_t volt_charging_adc_raw = 0;
    volt_charging_adc_raw = adc_get_sample()[E_VBAT_CHARGING];
    sensor_read.fVbat_charging = (uint16_t)(((volt_charging_adc_raw * kADC_SENSOR_SCALE) *(kVBAT_R_BAT_CHG_CONST_02 + kVBAT_R_BAT_CHG_CONST_01)) / kVBAT_R_BAT_CHG_CONST_02);
}

/***********************************************************************************************************************
* Function Name:  batterry_charging_measure
* Description  : V_OUT = 11*3.3*R/(2400+R) and R = 10R to 184R xem lại
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
float volt_pressure_out = 0.0;
float resistance = 0.0;
static void pressure_sender_measure(void)
{
    uint16_t volt_pressure_adc_raw = 0;
    volt_pressure_adc_raw = adc_get_sample()[E_PRESSURE_SENDER];
    volt_pressure_out = volt_pressure_adc_raw * kADC_SENSOR_SCALE / 1000;
    resistance = ((volt_pressure_out) * 2400) / (11*3.3 - volt_pressure_out);

    sensor_read.fPressure_sender_percent = oild_pressuare_table(resistance * 10); // xem lai
}

//uint8_t table_resistance2bar[10][2] = {
//	{10	,0},
//	{31	,1},
//	{52	,2},
//	{71	,3},
//	{88	,4},
//	{106	,5},
//	{124	,6},
//	{155	,7},
//	{170	,8},
//	{184	,9},
//};


int32_t oild_pressuare_table(float resistance) // factor 10
{
	int32_t value_compute = 0;
	if( resistance < 100)
		value_compute = 0;
	else if( (100 <= resistance) && (resistance < 310))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 100, 0, 310, 10);
	}
	else if( (310 <= resistance) && (resistance < 520))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 310, 10, 520, 20);
	}
	else if( (520 <= resistance) && (resistance < 710))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 520, 20, 710, 30);
	}
	else if( (710 <= resistance) && (resistance < 880))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 710, 30, 880, 40);
	}
	else if( (880 <= resistance) && (resistance < 1060))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 880, 40, 1060, 50);
	}
	else if( (1060 <= resistance) && (resistance < 1240))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 1060, 50, 1240, 60);
	}
	else if( (1240 <= resistance) && (resistance < 1550))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 1240, 60, 1550, 70);
	}
	else if( (1550 <= resistance) && (resistance < 1700))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 1550, 70, 1700, 80);
	}
	else if( (1700 <= resistance) && (resistance < 1840))
	{
		value_compute = vsm_rise_compute((int32_t)resistance, 1700, 80, 1840, 90);
	}
	else if( (1840 >= resistance))
	{
		value_compute = 100;
	}
	return value_compute;
}
/***********************************************************************************************************************
* End of file
***********************************************************************************************************************/
