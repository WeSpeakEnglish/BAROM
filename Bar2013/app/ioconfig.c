#include "ioconfig.h"
#include "delays.h"
#include "stm32f10x_i2c.h"

void ButtonConf(void){
  RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;    //
  AFIO->EXTICR[0]&=~AFIO_EXTICR1_EXTI0_PA; //EXTI0  A (A0 as result)
  EXTI->IMR|=EXTI_IMR_MR0;                           //
  EXTI->RTSR|=EXTI_RTSR_TR0;                          //
  NVIC_EnableIRQ (EXTI0_IRQn);          //

return;
} 

void EXTI0_IRQHandler(void)
{
 static u8 InsideCounter = 0;

 //  GPIOA->ODR&=~GPIO_ODR_ODR5; // drive PA5 to low
 //  GPIOA->ODR&=~GPIO_ODR_ODR6; // drive PA6 to low
   delay_1s(); //delay button condition stable 
  
   if (InsideCounter%2)
    {
   NVIC_EnableIRQ (TIM2_IRQn);    //разрешаем прерывание таймера
    }
    else
    {
   NVIC_DisableIRQ (TIM2_IRQn);    //запретить прерывание таймера

     }  
 

EXTI->PR|=0x01; // clear interrupt
InsideCounter++;
}

void PortCConf(void){
 RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;            //clock to the GPIOC
 GPIOC->CRL = 0x88333333; // push-pull output 50 MHz (PC0...PC3, PC4,5; )
 GPIOC->ODR &= ~0x00C0; //PC6,7 - pull down input
 return;
}

void PortAConfig(void){
   //PA 2 Enable (XCLR BMP085)
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;            //тактирование линий GPIOA
  GPIOA->CRL &=~(GPIO_CRL_CNF2_0);
  GPIOA->CRL |=(GPIO_CRL_MODE2_1);
    
   //PA 6 As Input (EOC BMP085)
  GPIOA->CRL &=~GPIO_CRL_MODE6;
  GPIOA->CRL &=~GPIO_CRL_CNF6;
  GPIOA->CRL |=GPIO_CRL_CNF6_1; //дискретный вход с подт€гивающим резистором
  GPIOA->BSRR =  GPIO_BSRR_BS6; // подт€жка к нулю GPIO_BSRR_BR6 - к нулю
 
  GPIOA->ODR|=GPIO_ODR_ODR2; // drive BMP085 XCLR to low
 return;
}
