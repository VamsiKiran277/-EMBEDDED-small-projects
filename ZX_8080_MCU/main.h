#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdint.h>

//bitfields
typedef struct {
    uint32_t ENABLE:1; //0-Bit pos
    uint32_t RESET:1; //1-Bit pos
    uint32_t CLOCK_SCALE:2; //2and3 Bit Pos
    uint32_t RESERVED    : 28; //fills rest of 32bit
}SYS_CNTL_t;

//pins we need to set these pins input or output
typedef struct {
    uint32_t pin0:1;
    uint32_t pin1:1;
    uint32_t pin2:1;
    uint32_t pin3:1;
    uint32_t pin4:1;
    uint32_t pin5:1;
    uint32_t pin6:1;
    uint32_t pin7:1;
    uint32_t RESERVED: 24;
}GPIO_DIR_t;


typedef struct {
   uint32_t START_CONV:1;
   uint32_t INT_ENABLE:1;
   uint32_t RESERVED   : 30;
}ADX_CNF_t;

typedef struct {
    uint32_t COUNTER_ENABLE:1;
    uint32_t AUTO_RELOAD_PRELOAD_ENABLE:1;
    uint32_t RESERVED:30;
}TIME_CNTL_t;


#endif