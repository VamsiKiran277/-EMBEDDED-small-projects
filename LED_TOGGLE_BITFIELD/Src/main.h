
#ifndef MAIN_H_
#define MAIN_H_
#include <stdint.h>
typedef struct  {
	uint32_t GPIOAEN:1;
	uint32_t GPIOBEN:1;
	uint32_t GPIOCEN:1;
	uint32_t GPIODEN:1;
	uint32_t GPIOEEN:1;
	uint32_t GPIOFEN:1;
	uint32_t GPIOGEN:1;
	uint32_t GPIOHEN:1;
	uint32_t GPIOIEN:1;
	uint32_t Reserverd1:3; //reserved 3 bits ..gpioj and gpiok can be taken from here
	uint32_t CRC_EN:1;
	uint32_t Reserverd2:3;
	uint32_t Reserverd3:2;
	uint32_t BKPSRAMEN:1;
	uint32_t Reserverd4:1;
	uint32_t CCMDAT_ARAMEN:1;
	uint32_t DMA1EN:1;
	uint32_t DMA2EN:1;
	uint32_t DMA2DEN:1;
	uint32_t Reserverd5:1;
	uint32_t ETHMAC_EN:1;
	uint32_t ETHMACTX_EN:1;
	uint32_t ETHMACRX_EN:1;
	uint32_t ETHMACPTP_EN:1;
	uint32_t OTGHS_EN:1;
	uint32_t OTGHSULPI_EN:1;
	uint32_t Reserved6:1;
}RCC_AHB1ENR_t;  //used t at the end for readibility as a tyoedef

//gpio port mode register
typedef struct {
	uint32_t MODER0:2; //basically pins
	uint32_t MODER1:2;
	uint32_t MODER2:2;
	uint32_t MODER3:2;
	uint32_t MODER4:2;
	uint32_t MODER5:2;
	uint32_t MODER6:2;
	uint32_t MODER7:2;
	uint32_t MODER8:2;
	uint32_t MODER9:2;
	uint32_t MODER10:2;
	uint32_t MODER11:2;
	uint32_t MODER12:2;
	uint32_t MODER13:2;
	uint32_t MODER14:2;
	uint32_t MODER15:2;

}GPIO_MODER_t;

//GPIO output data register
typedef struct {
		uint32_t ODR0:1; //basically pins
		uint32_t ODR1:1;
		uint32_t ODR2:1;
		uint32_t ODR3:1;
		uint32_t ODR4:1;
		uint32_t ODR5:1;
		uint32_t ODR6:1;
		uint32_t ODR7:1;
		uint32_t ODR8:1;
		uint32_t ODR9:1;
		uint32_t ODR10:1;
		uint32_t ODR11:1;
		uint32_t ODR12:1;
		uint32_t ODR13:1;
		uint32_t ODR14:1;
		uint32_t ODR15:1;
		uint32_t reserved:16;
}GPIO_ODR_t;


#endif /* MAIN_H_ */
