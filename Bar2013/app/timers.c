#include "timers.h"
#include "LCD.h"
#include "hd44780_driver.h"

void TIM2_init(void)
{
   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //��������� ������ �������� ��������� �� TIM2
   TIM2->CNT = 0;
   TIM2->SR = 0;
   TIM2->CR2=0x0;          //�������� �������
   TIM2->CR1=0x0;          //�������� �������?

   TIM2->PSC = 12000;          // ������������ ������� 2
   TIM2->ARR = 999;      //

   TIM2->CR1 &= ~TIM_CR1_DIR;      //������ ���� - 0 (�������� - 1) ������
   TIM2->CR1 &= ~TIM_CR1_UDIS;      //����.-1; ��������� ������� �� �������.������� -0
   TIM2->CR1 &= ~TIM_CR1_CKD;      //clock division
   TIM2->CR1 &= ~TIM_CR1_ARPE;      //��������� 0 - ����� �������� �� ���� ������ �������� ARR;���������=1 �����������
   TIM2->CR1 &= ~TIM_CR1_OPM;      //��������� ������ � ������ ���������� ��������
   TIM2->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - ���������� �� ������������ &&&

   TIM2->CR1 |= TIM_CR1_URS;
   TIM2->EGR &= ~TIM_EGR_UG;      // ���������� 0 ;update enable  ARR � ��������� �������� �� ���������������� � ������� �������
   TIM2->CR1 |= TIM_CR1_CEN;       //��������� ������2
        NVIC_EnableIRQ (TIM2_IRQn);    //��������� ����������
  
}

void TIM3_init(void) // make delays 
{
RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   //������ ������������ �� TIM3                           /
TIM3->PSC     = 8-1;                  //��������� �������� ��� ������������ 
TIM3->ARR     = 1667;                 //1000 ��� ���� 8 ���
TIM3->CR1     = TIM_CR1_CEN;
}


void TIM2_IRQHandler(void)
{
  static u8 InsideCounter = 0;
   if (TIM2->SR & TIM_SR_UIF){
      TIM2->SR &= ~TIM_SR_UIF;        // ������� ���� ���������� 
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

