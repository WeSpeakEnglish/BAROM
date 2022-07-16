#include "timers.h"
#include "LCD.h"
#include "hd44780_driver.h"

void TIM2_init(void)
{
   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //разрешить подачу тактовых импульсов на TIM2
   TIM2->CNT = 0;
   TIM2->SR = 0;
   TIM2->CR2=0x0;          //обнуляем регистр
   TIM2->CR1=0x0;          //обнуляем регистр?

   TIM2->PSC = 12000;          // предделитель таймера 2
   TIM2->ARR = 999;      //

   TIM2->CR1 &= ~TIM_CR1_DIR;      //прямой счёт - 0 (обратный - 1) отсчёт
   TIM2->CR1 &= ~TIM_CR1_UDIS;      //запр.-1; разрешаем событие по перепол.таймера -0
   TIM2->CR1 &= ~TIM_CR1_CKD;      //clock division
   TIM2->CR1 &= ~TIM_CR1_ARPE;      //запрещаем 0 - когда прграмно не надо менять значение ARR;разрешаем=1 перзагрузку
   TIM2->CR1 &= ~TIM_CR1_OPM;      //Запрещаем работу в режиме одиночного импульса
   TIM2->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - прерывание по переполнению &&&

   TIM2->CR1 |= TIM_CR1_URS;
   TIM2->EGR &= ~TIM_EGR_UG;      // сбрасываем 0 ;update enable  ARR и прескалер грузятся из предварительного в теневой регистр
   TIM2->CR1 |= TIM_CR1_CEN;       //запускаем таймер2
        NVIC_EnableIRQ (TIM2_IRQn);    //разрешаем прерывание
  
}

void TIM3_init(void) // make delays 
{
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   //подать тактирование на TIM3                           /
TIM3->PSC     = 8-1;                  //настроить делитель для формирования 
TIM3->ARR     = 1667;                 //1000 мкс если 8 Мгц
TIM3->CR1     = TIM_CR1_CEN;
}


void TIM2_IRQHandler(void)
{
  static u8 InsideCounter = 0;
   if (TIM2->SR & TIM_SR_UIF){
      TIM2->SR &= ~TIM_SR_UIF;        // очищаем флаг прерывания 
      /*
      if(InsideCounter%2) {
                        GPIOA->ODR&=~GPIO_ODR_ODR5; // drive PA5 to low
                        GPIOA->ODR|=GPIO_ODR_ODR6; // drive PA6 to high
                          }
      else                {
                        GPIOA->ODR|=GPIO_ODR_ODR5; // drive PA5 to high
                        GPIOA->ODR&=~GPIO_ODR_ODR6; // drive PA6 to low
                          }
      */
      lcd_set_xy(0,1);
      DisplayPressure(0.1);
      InsideCounter++;
      }
}

