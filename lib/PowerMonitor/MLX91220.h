/*
 * MLX91220.h
 *
 * Created: 2023-06-21
 *  Author: WU555
 */

#ifndef MLX91220_H_
#define MLX91220_H_

// #include "FreeRTOS.h"
// #include "task.h"
#include <math.h>
#include "stm32f4xx_hal.h"
#include "PowerBoardConfig.h"
#include "PinConfig.h"
#include "LOG.h"
#include "RunningStatistics_C.h"

#include "MSP_ADC.h"
#include "MSP_TIM.h"

//#define TWO_PI    6.28318530717958647693
//#define PI        3.14159265358979323846

#define MAX_ADC_CHANNELS 			9       //表示有9颗MLX91220芯片，每个芯片一个adc引脚
//#define constrain(x, a, b) ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))
//#/define sq(x) ((x)*(x))


/**
 * @struct PowerMonitorHandler_t
 * @brief
 * Power monitor handler structure
 * Contains all the variables required for Power Monitor daemon operation
 */
typedef struct
{
    /* 需要外部配置的参数 */
    uint8_t AC_freq;        //交流电的频率
    uint8_t ADC_channel_num;
    uint16_t ADC_conv_period;

    /* 提供给外部使用的数据 */
    float Inow[MAX_ADC_CHANNELS];
    float Irms[MAX_ADC_CHANNELS];
    float Itrms[MAX_ADC_CHANNELS];
}
PowerMonitorHandler_t;

extern PowerMonitorHandler_t *_powermH;

void PowerMonitor_Init(PowerMonitorHandler_t *powermH);
void FiltersInit(void);
void calibrate(void);
void PowerMonitor_process(void);
uint8_t getAC_Inow(float inow[]);
uint8_t getAC_Irms(float irms[]);
void start_adc_conversion(void);

#endif /* MLX91220_H_ */