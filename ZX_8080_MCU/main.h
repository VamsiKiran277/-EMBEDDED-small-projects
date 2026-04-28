#ifndef MAIN_H
#define MAIN_H
//#include <stdio.h>
#include <stdint.h>

//bitfields
typedef struct {
    volatile uint32_t ENABLE:1; //0-Bit pos
    volatile uint32_t RESET:1; //1-Bit pos
    volatile uint32_t CLOCK_SCALE:2; //2and3 Bit Pos
    volatile uint32_t RESERVED    : 28; //fills rest of 32bit
}SYS_CNTL_t;

//pins we need to set these pins input or output
typedef struct {
    volatile uint32_t pin0:1;
    volatile uint32_t pin1:1;
    volatile uint32_t pin2:1;
    volatile uint32_t pin3:1;
    volatile uint32_t pin4:1;
    volatile uint32_t pin5:1;
    volatile uint32_t pin6:1;
    volatile uint32_t pin7:1;
    volatile uint32_t RESERVED: 24;
}GPIO_DIR_t;


typedef struct {
   volatile uint32_t START_CONV:1;
   volatile uint32_t INT_ENABLE:1;
   volatile uint32_t RESERVED   : 30;
}ADX_CNF_t;

typedef struct {
    volatile uint32_t COUNTER_ENABLE:1;
    volatile uint32_t AUTO_RELOAD_PRELOAD_ENABLE:1;
    volatile uint32_t RESERVED:30;
}TIME_CNTL_t;


#endif
