/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32 VS Code Extension
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "main.h"

void ClockInit(void){
    RCC->CR |= (1 << RCC_CR_HSEON_Pos);
    __IO int StartUpCounter;
    for (StartUpCounter = 0;     ; StartUpCounter++)
    {
        if(RCC->CR & (1 << RCC_CR_HSERDY_Pos)){
            break;
        }
        if(StartUpCounter > 0x1000){
            RCC->CR &= ~(1 << RCC_CR_HSEON_Pos);
        }
    }
    
    RCC->CFGR |= (0x02 << RCC_CFGR_MCO2_Pos);
    RCC->CFGR |= (0x00 << RCC_CFGR_MCO2PRE_Pos);
    RCC->PLLCFGR |= (0x04 << RCC_PLLCFGR_PLLQ_Pos);
    RCC->PLLCFGR |= (0x63 << RCC_PLLCFGR_PLLN_Pos);
    RCC->PLLCFGR |= (0x00 << RCC_PLLCFGR_PLLP_Pos); 
    RCC->CR |= (1 << RCC_CR_PLLON_Pos);
    
    for (StartUpCounter = 0;    ; StartUpCounter++)
    {
        if(RCC->CR & (1 << RCC_CR_PLLON_Pos)){
            break;
        }
        if(StartUpCounter > 0x1000){
            RCC->CR &= ~(1 << RCC_CR_PLLON_Pos);
            RCC->CR &= ~(1 << RCC_CR_HSEON_Pos); 
        }
    }
    
    FLASH->ACR |= (0x02 << FLASH_ACR_LATENCY_Pos);
    
    RCC->CFGR |= (0x00 << RCC_CFGR_PPRE1_Pos);
    RCC->CFGR |= (0x00 << RCC_CFGR_PPRE2_Pos);
    RCC->CFGR |= (0x00 << RCC_CFGR_HPRE_Pos);
    
    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != (0x02 << RCC_CFGR_SWS_Pos)){}
    RCC->CR &= ~(1 << RCC_CR_HSION_Pos);
    
    return 0;    
}

void PC13LED(void){
    RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOCEN_Pos);
	GPIOC->MODER &= ~(GPIO_MODER_MODER13);
	GPIOC->MODER |= (0x02 << GPIO_MODER_MODER13);
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT13);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13);
}

void PC13LEDHi(void){
    GPIOC->BSRR |= (1<<13);
}

void PC13LEDLow(void){
    GPIOC->BSRR |= ~(1<<13);
}

int main(void)
{
    ClockInit();
    PC13LED();
	for(    ;   ;   ){
        PC13LEDHi();
        for (int i = 0; i < 0x4000; i++){}
        PC13LEDLow();
        for (int i = 0; i < 0x4000; i++){}
    }
}
