#include "stm32F10x.h"
#include "stm32f10x_i2c.h"
#include "uart.h"
#include "delays.h"
#include "timers.h"
#include "ioconfig.h"
#include "i2c.h"
#include "bmp085.h"
#include "hd44780_driver.h"
#include "LCD.h"

GPIO_TypeDef * PORT_Temp;


int main(void)
{ 
     RCC->CR|=RCC_CR_HSEON; // Включить генератор HSE.
     while (!(RCC->CR & RCC_CR_HSERDY)) {} // Ожидание готовности HSE.
     RCC->CFGR &=~RCC_CFGR_SW; // Очистить биты SW0, SW1.
     RCC->CFGR |= RCC_CFGR_SW_HSE; // Выбрать HSE для тактирования SW0=1.
     
  PortAConfig();
  I2c1_Init();
  bmp085_init();
  
  PortCConf();
  ConfigureLCD();
  
  
  
  

     
     lcd_out("This is fish");
     lcd_set_xy(0,1); //ia?aaiaei eo?ni? a ia?ao? no?ieo
     lcd_send(0,DATA); //auaiai neiaie iiia? iieu
     TIM2_init();  // for TEST SIGNAL
     ButtonConf(); // button enable/disable signal
     Init_UART1();  
   
     while(1){

     }   

}