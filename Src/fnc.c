#include "fnc.h"

 void ClockInit(void){
    RCC->CR &= ~(1 << RCC_CR_PLLON_Pos);
    RCC->CR &= ~(1 << RCC_CR_HSION_Pos);
    RCC->CR &= ~(1 << RCC_CR_HSEON_Pos);
    //RCC->CR = 0x00006983;
    RCC->PLLCFGR = 0x24003010;              //see EASYPLL
    FLASH->ACR = 0x00000000;
    RCC->CFGR = 0x00000000;
    RCC->PLLCFGR |= (0x01 << RCC_PLLCFGR_PLLSRC_Pos);
    RCC->PLLCFGR |= (0x192 << RCC_PLLCFGR_PLLN_Pos);
    RCC->PLLCFGR |= (0x08 << RCC_PLLCFGR_PLLM_Pos);
    RCC->PLLCFGR |= (0x03 << RCC_PLLCFGR_PLLP_Pos);
    FLASH->ACR |= (0x02 << FLASH_ACR_LATENCY_Pos);
    RCC->CFGR |= (0x00 << RCC_CFGR_HPRE_Pos);
    RCC->CFGR |= (0x00 << RCC_CFGR_PPRE2_Pos);
    RCC->CFGR |= (0x02 << RCC_CFGR_SW_Pos);
    RCC->CR |= (1 << RCC_CR_PLLON_Pos);
    RCC->CR |= (1 << RCC_CR_HSION_Pos);
    RCC->CR |= (1 << RCC_CR_HSEON_Pos);
    __IO int StrtUpcntr;
    for (StrtUpcntr = 0 ;    ;   StrtUpcntr++)
    {
        if(RCC->CR & (1 << RCC_CR_HSIRDY_Pos))break;
        if(StrtUpcntr > 0x1000){
            RCC->CR &= ~(1 << RCC_CR_HSION_Pos);
            return 1;
        }
    }
    for (StrtUpcntr = 0 ;    ;   StrtUpcntr++)
    {
        if(RCC->CR & (1 << RCC_CR_HSERDY_Pos)){
            RCC->CR |= ~(1 << RCC_CR_HSION_Pos);
            break;
            }
        if(StrtUpcntr > 0x1000){
            RCC->CR &= ~(1 << RCC_CR_HSION_Pos);
            RCC->CR &= ~(1 << RCC_CR_HSEON_Pos);
            return 1;
        }
    }
    for(StrtUpcntr = 0; ;   StrtUpcntr++){
        if ((RCC->CR & RCC_CR_PLLRDY_Msk) & (0x01 << RCC_CR_PLLRDY_Pos))break;
        if(StrtUpcntr > 0x1000){
            RCC->CR &= ~(1 << RCC_CR_PLLON_Pos);
            RCC->CR &= ~(1 << RCC_CR_HSION_Pos);
            return 1;
        }
    }
    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != (0x02 << RCC_CFGR_SWS_Pos)){}
    RCC->CR &= ~(1 << RCC_CR_HSION_Pos);
    return 0;    
}

void PC13LED(void){
    RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOCEN_Pos);
	GPIOC->MODER &= ~(GPIO_MODER_MODER13);
	GPIOC->OTYPER &= ~(GPIO_OTYPER_OT13);
	GPIOC->MODER |= (0x02 << GPIO_MODER_MODER13_Pos);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13);
}

void PC13LEDHi(void){
    GPIOC->BSRR |= (1<<13);
}

void PC13LEDLow(void){
    GPIOC->BSRR |= ~(1<<13);
}
