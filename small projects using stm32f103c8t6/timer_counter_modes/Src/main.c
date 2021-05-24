#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "timer.h"
#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
#define AFIO_BASE 0x40010000

// RCC registers
#define RCC_APB2ENR *((volatile unsigned int*)(RCC_BASE+0x18))
#define RCC_APB1ENR *((volatile unsigned int*)(RCC_BASE+0x1C))
#define RCC_CFGR *((volatile unsigned int*)(RCC_BASE+0x04))
// GPIO registers
#define GPIOA_CRH *((volatile unsigned int*)(GPIOA_BASE+0x04))
#define GPIOA_ODR *((volatile unsigned int*)(GPIOA_BASE+0x0C))
 void tim2_upCounter()
{
	 // set dir up counter mode
	 	TIM2_CR1 &=~(1<<4);
	/*
	 we choose prescale factor /16 in APB1 (TIM2 CONNECTED)
	 so we have APB1 clock of 500khz
	 and we have TIMCLK 2*APB1 clk = 1MHZ
	 */
	RCC_CFGR |=(0b111<<8);
	// tim2 prescal 999+1 so tclk will be 1M/1000=1000hz so 1mes
	TIM2_PSC =999;

	// enable update interrupt
	//TIM2_DIER |=(1<<8);
  //auto reload register to calculate 5 seconds
	// 5000*1msec=5 seconds
	TIM2_ARR=5000;

 // enable counter
	TIM2_CR1 |=(1<<0);

}
void clock_init()
{
	// enable clock for tim2,3,4
	RCC_APB1ENR |=(1<<0)|(1<<1)|(1<<2);
	// enable clock for GPIO and AFIO
	RCC_APB2ENR |=(1<<0)|(1<<2);

}

void GPIO_init()
{   // clear bit field of PA8
	GPIOA_CRH &=0xfffffff0;
	// configure PA8 as GP output 10 mhz max
	GPIOA_CRH |=(0b0001<<0);
}
int main(void)
{
	clock_init();
	GPIO_init();
	tim2_upCounter();

    /* Loop forever */
	while(1)
	{

		while(!(TIM2_SR &(1<<0)));

		GPIOA_ODR ^=(1<<8);
		 TIM2_SR &=~(1<<0);

	}
}

