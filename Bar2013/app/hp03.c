#include "hp03.h"
#include "i2c.h"
#include "delays.h"
#include "stm32f10x_i2c.h"
#include "I2CLib.h"

#define HP03_SETTINGS_ADDRESS 0xA1

u8 CoeffsCalibP[18];
u8 Temperature[2]={10,10};
u8 Pressure[2];

//struct Coeffs;

void HP03_Init(void)
{
u32 index = 0;

/*
// разрешаем работу
I2C1->CR1 |= I2C_CR1_PE;
// формирование сигнала старт
I2C1->CR1 |= I2C_CR1_START;
// ждем окончания формирования сигнала "Старт"
while (!(I2C1->SR1 & I2C_SR1_SB))
{
}
(void) I2C1->SR1;
 
// передаем адрес ведомого
I2C1->DR = 0xA1;

// ожидаем окончания передачи адреса
while (!(I2C1->SR1 & I2C_SR1_ADDR))
{
}
 
(void) I2C1->SR1;
(void) I2C1->SR2;

// передаем адрес десятой ячейки
I2C1->DR = 16;

while (!(I2C1->SR1 & I2C_SR1_BTF))
{
}

*/


    // устанавливаем указатель на начальный адрес корректировочных ячеек
    mcu_i2c_write_byte(0xA0, 16);
 delay_40ms();
    // считываем значение корректировочных ячеек
    for (index = 0; index < sizeof(CoeffsCalibP); index++)
    {
      if(index == 17){
     I2C_AcknowledgeConfig(I2C1, DISABLE);
      CoeffsCalibP[index] = mcu_i2c_read_byte(HP03_SETTINGS_ADDRESS);
   //   I2C_GenerateSTOP(I2C1, ENABLE);
     I2C_AcknowledgeConfig(I2C1, ENABLE);
      }
      else
        CoeffsCalibP[index] = mcu_i2c_read_byte(HP03_SETTINGS_ADDRESS);

    }

return;
}

void HP03_GetTemp(void){
  u8 NumByteToRead=2;
  u8* pBuffer = Temperature;
  GPIOA->ODR|=GPIO_ODR_ODR2; // drive HP03 XCLR to high
  delay_40ms();
  GPIOA->ODR&=~GPIO_ODR_ODR2; // drive HP03 XCLR to low
  delay_40ms();
  GPIOA->ODR|=GPIO_ODR_ODR2; // drive HP03 XCLR to high
    // запуск преобразования
    delay_40ms();
    delay_40ms();
    mcu_i2c_write_two_byte(0xEE, 0xFF, 0xE8);
    ///////////////////////////////////////////////////////////////////////
//  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
 
    /* Send START condition */
//  I2C_GenerateSTART(I2C1, ENABLE);
 
    /* Test on EV5 and clear it */
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
 
    /* Send address for write */
//  I2C_Send7bitAddress(I2C1, 0xEE, I2C_Direction_Transmitter);  
   /* Test on EV6 and clear it */
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
//  I2C_SendData(I2C1, 0xFF);
  
   /* Test on EV8 and clear it */
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
//  I2C_SendData(I2C1, 0xE8);
  
 /* Test on EV8 and clear it */
//  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
 // I2C_GenerateSTOP(I2C1, ENABLE);
   ///////////////////////////////////////////////////////////////////////////////// 
    delay_40ms();
    delay_40ms();


    mcu_i2c_write_byte(0xEE, 0xFD);
    
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
 
    /* Send START condition */
   I2C_GenerateSTART(I2C1, ENABLE);
 
    /* Test on EV5 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
 
    /* Send address for write */
    I2C_Send7bitAddress(I2C1, 0xEE, I2C_Direction_Transmitter);
 
    /* Test on EV6 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
     I2C_SendData(I2C1, 0xFD);
  
 /* Test on EV8 and clear it */
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Test on EV8 and clear it */
  
 I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on EV5 and clear it */
   while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
 
  /* Send MPU6050 address for read */
   I2C_Send7bitAddress(I2C1, 0xEF, I2C_Direction_Receiver);
 
  /* Test on EV6 and clear it */
   while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
  
   I2C_AcknowledgeConfig(I2C1, ENABLE);
  
while(NumByteToRead)
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2C1, DISABLE);
 
      /* Send STOP Condition */
    I2C_GenerateSTOP(I2C1, ENABLE);
    }
 
    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      /* Read a byte from the HP03 */
      *pBuffer = I2C_ReceiveData(I2C1);
 
      /* Point to the next location where the byte read will be saved */
      pBuffer++;
 
      /* Decrement the read bytes counter */
      NumByteToRead--;
    }
  }
 
  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C1, ENABLE);

//////////////////////////////////////////////////////////////////////////////////    
   // 
   // Temperature[1] = mcu_i2c_read_byte(0xEF);
GPIOA->ODR&=~GPIO_ODR_ODR2; // drive HP03 XCLR to low
return;
}