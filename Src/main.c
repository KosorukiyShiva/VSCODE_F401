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

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f401xc.h"
void ClockInit(void){
    RCC->CR |= (1 << RCC_CR_HSEON_Pos);
}
int main(void)
{
    /* Loop forever */
	for(;;);
}
