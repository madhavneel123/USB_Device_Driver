/*
 * systeminit.c
 *
 *  Created on: Mar 17, 2023
 *      Author: salil madhav
 */

#include <stdint.h>
#include "system_stm32f4xx.h"
#include "stm32f4xx.h"

uint32_t SystemCoreClock = 72000000;

//HCLK = 72MHz
//PLL : M = 4, N = 72, P = 2, Q = 3
//AHB prescaler = 1
//APB prescaler = 2 APB prescaler2 = 1
//MCO1 prescaler = 2

static void Configure_Clock(void)
{
	FLASH -> ACR |= 0x02;

	//Enable HSE
	RCC -> CR |= (1 << 16);

	//wait until HSE is stable
	while(!((RCC -> CR) | ~(1 << 17)));

	//Configure PLL Source HSE, SYSCLK = 72MHz
	//M = 4
	RCC -> PLLCFGR |= (0x04 << 0);
	//N = 72
	RCC -> PLLCFGR |= (0x48 << 6);
	//P = 2
	RCC -> PLLCFGR |= (0x02 << 16);
	//Q = 3
	RCC -> PLLCFGR |= (0x03 << 24);
	//SRC = 2
	RCC -> PLLCFGR |= (0x02 << 22);

	//Enable PLL Module. Always enable PLL after configuration
	RCC -> CR |= (1 << 24);

	//Wait until PLL is stable
	while(!(RCC -> CR |= ~(1 << 25)));

	//Switches system clock to PLL
	RCC -> CFGR |= (0b10 << 0);

	//Configure PRE1
	RCC -> CFGR |= (0b101 << 10);

	//Wait until PLL is used
	while((RCC -> CFGR & 0x0C) != 0x08);

	//Disable HSI - To save power. We are using HSE
	RCC -> CR &= ~(1 << 0);

}

void SystemInit(void)
{
	Configure_Clock();
}
