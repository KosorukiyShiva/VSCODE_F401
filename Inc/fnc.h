#ifndef FNC_H
#define FNC_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f401xc.h"

void ClockInit(void);
void PC13LED(void);
void PC13LEDHi(void);
void PC13LEDLow(void);

#endif