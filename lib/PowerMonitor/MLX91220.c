/*
 * MXL91220.c
 *
 * Created: 2023.06.21
 *  Author: WU555
 */

#include "MLX91220.h"

PowerMonitorHandler_t *_powermH;

float Default_AC_Freq       = 50.0;
float windowTimes          = 40.0;     // how long to average the signal, for statistist

uint32_t _ADC_values[MAX_ADC_CHANNELS];
uint32_t _ADC_zeros[MAX_ADC_CHANNELS];

uint8_t _AC_period;
uint32_t _ADC_conv_counter;
uint32_t _ADC_conv_LastTime;  
uint32_t _IRMS_LastTime;        //用于计算Irms

uint8_t _getInow_flag = 0;
uint8_t _getIrms_flag = 0;
uint8_t _getItrms_flag = 0;

uint32_t _Isum[MAX_ADC_CHANNELS];
/* 关于斜率(slope)和截距(intercept)
 * 首先你需要知道所有的 TRMS 计算都是由库中的函数完成的，它是“inputStats.sigma()”值
 * 然后，您可以显示“inputStats.sigma()”作为您的 TRMS 值，然后尝试在输入为 0.00A 时使用它进行测量
 * 如果测量值像我得到的那样为 0，您可以将截距保持为 0，否则您需要添加或减去以使该值等于 0
 * 换句话说“删除偏移量”
 * 然后将电源打开到已知值，例如使用知道其功率并且已经知道电压的灯泡或 LED，因此进行一点数学计算即可获得理论安培数
 * 将理论值除以测量值，得到斜率，现在放置或修改它们
 */
float intercept = 0;                    // to be adjusted based on calibration testing
float slope = 0.0752;                   // to be adjusted based on calibration testing

float sensitivity = 0.080;              //MLX91220KDC-ABF-025-RE的灵敏度为80mV/A

void PowerMonitor_Init(PowerMonitorHandler_t *powermH) {
    _powermH = powermH;
    _powermH->ADC_channel_num = 9;
    _powermH->AC_freq = 50;

    memset(_ADC_values, 0, _powermH->ADC_channel_num);
    memset(_ADC_zeros, 0, _powermH->ADC_channel_num);

    memset(_powermH->Inow, 0, _powermH->ADC_channel_num);
    memset(_powermH->Irms, 0, _powermH->ADC_channel_num);
    memset(_powermH->Itrms, 0, _powermH->ADC_channel_num);

    memset(_Isum, 0, _powermH->ADC_channel_num);

    _AC_period  = (uint8_t)(1000 / _powermH->AC_freq);
    _ADC_conv_counter = 0;
    _ADC_conv_LastTime = HAL_getTick_us();
    _IRMS_LastTime = 0;
}

void FiltersInit(void)
{
    LOG("fileters init \r\n");
    float windowLen = windowTimes / Default_AC_Freq;
    void *rStats = RunningStatistics_C_New();
    RunningStatistics_C_setWindowSecs(rStats, windowLen);
}

void calibrate(void) {
	uint8_t counttimes = 100;
	uint32_t acc[_powermH->ADC_channel_num];
    memset(acc, 0, _powermH->ADC_channel_num);
	for (int i = 0; i < counttimes; i++) {
        for (uint8_t adci = 0; adci < _powermH->ADC_channel_num; adci++) {
            start_adc_conversion();
            acc[adci] += _ADC_values[adci];
            HAL_Delay(1);
		}
	}
    for (uint8_t adci = 0; adci < _powermH->ADC_channel_num; adci++) {
        _ADC_zeros[adci] = acc[adci] / counttimes;
    }
}

void PowerMonitor_process(void) {
    /* 10us获取一次adc引脚的数值 */
    if (HAL_getTick_us() - _ADC_conv_LastTime > _powermH->ADC_conv_period) {
        _ADC_conv_LastTime = HAL_getTick_us();
        start_adc_conversion();
        for (int i = 0; i < _powermH->ADC_channel_num; i++) {	
            uint32_t amp = _ADC_values[i] - _ADC_zeros[i];
            _powermH->Inow[i] = amp / (0.0005 * 0.9 * 100 * 3.33);
            if (_powermH->Inow[i] < 0) _powermH->Inow[i] = 0;
            _Isum[i] += _powermH->Inow[i] * _powermH->Inow[i];
        }
        _getInow_flag = 1;
    }
    /* 20ms计算一次电流有效值 Irms */
    if (HAL_getTick_us() - _IRMS_LastTime > _AC_period) {
        for (int i = 0; i < _powermH->ADC_channel_num; i++) {
			_powermH->Irms[i] = sqrt(_Isum[i] / _ADC_conv_counter);     //   / ADC_SCALE * VREF / _sens;
		}
        _IRMS_LastTime = HAL_getTick_us();
        _ADC_conv_counter = 0;
        memset(_Isum, 0, _powermH->ADC_channel_num);
        _getIrms_flag = 1;
    }
}

/**
 * ADC引脚读数与实际电流值转换关系 I_v = (ADC_Value / (Current_CT_Gain * Empirical * Sample_Resistor * Amplifier_Gain)) * 100
 * I_v：                 为实际的电流值 数值300表示300ma， 1000表示1A
 * ADC_Value：           为读取的ADC数值 为float类型
 * Current_CT_Gain:      为电流互感器的变比，LKHM100采用的是ZMCT112B，数值为 1/2000 ； LKHM200采用的是TS2021C，数值为 1/2000
 * Empirical：           经验常数，默认设置为0.9
 * Sample_Resistor：     目前电路设计中，采样电阻为100欧
 * Amplifier_Gain：      LKHM100中，放大器的放大倍数设计为4.9 （39KΩ/10KΩ + 1）； LKHM200中，放大器的放大倍数为3.33 (23.3KΩ/10KΩ + 1)
 */
uint8_t getAC_Inow(float inow[]) {
    if (_getInow_flag == 1) {
        memcpy(inow, _powermH->Inow, _powermH->ADC_channel_num);
        return 1;
    }
    return 0;
}


/**电流有效值计算公式： 
  * sum += current * current  电流平方 累加count次数
  * Irms = sum / count 
  * 
  **/
uint8_t getAC_Irms(float irms[]) {
    if (_getIrms_flag == 1) {
        memcpy(irms, _powermH->Irms, _powermH->ADC_channel_num);
        return 1;
    }
    return 0;
}

#if 0
float getAC_Itrms(float windowT, float )
{
    float windowLen = windowT / Default_AC_Freq;
    float *AmpsTrms;
    float Amps_TRMS;
    void *rStats = RunningStatistics_C_New();
	RunningStatistics_C_getACtrms(rStats, acValue, AmpsTrms);
    Amps_TRMS = intercept + slope * AmpsTrms[0];
}
#endif

/* 启动ADC的数据转换 */
void start_adc_conversion(void) {
    HAL_ADC_Start_DMA(&hadc1, _ADC_values, _powermH->ADC_channel_num);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    // ADC转换完成后的回调函数
    // 在这里处理adc_values数组中的数据
    if (hadc->Instance == ADC1) {
        _ADC_conv_counter++;
    }
}

