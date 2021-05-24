/*
 * timer.h
 *
 *  Created on: May 23, 2021
 *      Author: shady mamdouh
 */

#ifndef TIMER_H_
#define TIMER_H_
#define TIM3_BASE 0x40000400
#define TIM4_BASE 0x40000800
#define TIM2_BASE 0x40000000
// TIM6 registers
#define TIM2_CR1 *((volatile unsigned int*)(TIM2_BASE+0x00))
#define TIM2_DIER *((volatile unsigned int*)(TIM2_BASE+0x0C))  // INTERRUPT ENABLE REG
#define TIM2_SR *((volatile unsigned int*)(TIM2_BASE+0x10))
#define TIM2_CNT *((volatile unsigned int*)(TIM2_BASE+0x24))
#define TIM2_PSC *((volatile unsigned int*)(TIM2_BASE+0x28))  // PRESCALE
#define TIM2_ARR *((volatile unsigned int*)(TIM2_BASE+0x2C)) // AUTO RELOAD REG

extern void tim6_upCounter();

#endif /* TIMER_H_ */
