#ifndef _hp03_h
#define _hp03_h
#include "stm32f10x.h"
extern u8 CoeffsCalibP[18];
extern u8 Temperature[2];
extern u8 Pressure[2];
void HP03_Init(void);
void HP03_GetTemp();
#endif
