#include "main.h"
#define BASE_ADDRESS 0x40001000
#define TIMER_BASE_ADDRESS 0x40002000
//offsets for adc and rst
#define SYSTEM_CNTL 0x00
#define GPIO_DIR 0x04
#define GPIO_DATA 0x08
#define ADC_CNF 0x10
#define ADC_VAL 0x14
//offsets for timer
#define TIM_CNTL 0x00
#define TIM_PSC 0x04
#define TIM_ARR 0x08
#define TIM_STAT 0x0c

int main() {
    //ADC ADDRESSES
    SYS_CNTL_t* system_control = (SYS_CNTL_t*)(BASE_ADDRESS + SYSTEM_CNTL);
    GPIO_DIR_t* gpio_port = (GPIO_DIR_t*)(BASE_ADDRESS + GPIO_DIR);
    GPIO_DIR_t* gpio_data = (GPIO_DIR_t*)(BASE_ADDRESS + GPIO_DATA);
    ADX_CNF_t* adc_config = (ADX_CNF_t*)(BASE_ADDRESS + ADC_CNF);
    uint32_t* adc_val = (uint32_t*)(BASE_ADDRESS + ADC_VAL);
    //TIMER ADDRESSES
    TIME_CNTL_t* timer_control = (TIME_CNTL_t*)(TIMER_BASE_ADDRESS + TIM_CNTL);
    uint32_t* Timer_Status = (uint32_t*)(TIMER_BASE_ADDRESS + TIM_STAT);
    uint32_t* TIMER_ARR = (uint32_t*)(TIMER_BASE_ADDRESS + TIM_ARR);
    uint32_t* TIMER_PSC = (uint32_t*)(TIMER_BASE_ADDRESS + TIM_PSC);
    //Finding the CLock Timer = 80MHz/(PSC+1) (fsys =  80MHz)
    //taking PSC=7999 the goal of prescaler to slow down the highspeed system clock too human readable level
//    uint32_t clock_timer = 80000000/(7999+1);
    *TIMER_PSC = 7999; //need to let the hardware know
    //now clock is ticking at 10khz we need to set the target at which it need to blink which is 0.5 sec check datasheet
    //T_delay = ARR + 1/clock_timer , here arr is 0.5 seconds
//    uint32_t Time_delay = (1/2)+1/clock_timer;
    *TIMER_ARR = 4999; //need to let the hardware know

    //enabling the timer
    timer_control->COUNTER_ENABLE = 1;
    gpio_port->pin5 =1; //configuring port a pin5 as output

    system_control->ENABLE = 1; //system enabled
    gpio_port->pin0 = 1; //port a pin 0 enable
    while(1) {
        //triggering an ADC conv to read the temperature sensor
        adc_config->START_CONV = 1;
        //if we want to to polling method we need below while loop and dont need the INT enable above 
        while(adc_config->START_CONV==1) {
            //do nothing
        }
        uint32_t current_temp = *adc_val;
        if(current_temp > 3000) {
            //set port a pin0 to high
            gpio_data->pin0 = 1;
        } else if(current_temp < 1500){
            gpio_data->pin0 = 0;
        }
        //LED TIMER 
        //IF the update Interrupt flag is set to zero 
        if((*Timer_Status & 0x01)==1) {
            gpio_data->pin5 ^= 1; //To toggle the state
            *Timer_Status &=~(0x01);
        }
    }
    return 0;
}