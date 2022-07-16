/******************************************************************************

   ���� ������ ������ � GPIO
   �������� ������� ��� �������� ��������������� �������� � GPIO.

 ******************************************************************************
   ����� ��������.
   - � �������� ��������� ������� ���������
   ��������� �� ������� ����� ����� *PORTX (��������� � ������� �������� GPIOX->CRL)

   - ��������� � ����������� ��������� ����� ������� ����� �������� ������������ �������� ������
   - ��� ����������� ��������� ���������� ������������ � ������� � ������� 
    � ����� ��� ������� ��������:
   _m - ��������� ������� �����, �������� ������ � ����������� ������;
   _b - ��������� ����� ����, ������ � ����� �� ����� �����;


 ******************************************************************************/


#include "gpio_emcu.h"

//    ��������� �� ������� ������ GPIO.
u32   *PORTA= (u32*)(&GPIOA->CRL); // APB2PERIPH_BASE + 0x0800.
u32   *PORTB= (u32*)(&GPIOB->CRL); // ... + 0x0C00.
u32   *PORTC= (u32*)(&GPIOC->CRL); // ... + 0x1000.
u32   *PORTD= (u32*)(&GPIOD->CRL); // ... + 0x1400. 
u32   *PORTE= (u32*)(&GPIOE->CRL); // ... + 0x1800. 
u32   *PORTF= (u32*)(&GPIOF->CRL); // ... + 0x1C00. 
u32   *PORTG= (u32*)(&GPIOG->CRL); // ... + 0x2000.


// ��������� ������ �� ����������� PushPull - �����.
void PinOutPP_b (u32 *adr, u8 bit)
{
   if (bit<=7) {*adr|=3<<(bit<<2); *adr&=~(3<<((bit<<2)+2));} // ���� MODE=11 � CNF=00.
   else {*(adr+1)|=3<<((bit-8)<<2); *(adr+1)&=~(3<<(((bit-8)<<2))+2);}
}
// ��������� ������ �� ����� c �������� ������ OpenDrain.
void PinOutOD_b (u32 *adr, u8 bit)
{
   if (bit<=7) {*adr|=3<<(bit<<2); *adr&=~(3<<((bit<<2)+2)); *adr|=(1<<((bit<<2)+2));} // ���� MODE=11 � CNF=01.
   else {*(adr+1)|=3<<((bit-8)<<2); *(adr+1)&=~(3<<(((bit-8)<<2))+2); *(adr+1)|=(1<<(((bit-8)<<2))+2);} 
}
// ��������� ������ �� ���� � ������� Z-���������.
void PinInputZ_b (u32 *adr, u8 bit)
{
   if (bit<=7) {*adr&=~(3<<(bit<<2)); *adr&=~(3<<((bit<<2)+2)); *adr|=(1<<((bit<<2)+2));} // ���� MODE=00 � CNF=01.
   else {*(adr+1)&=3<<~(((bit-8)<<2)); *(adr+1)&=~(3<<(((bit-8)<<2))+2); *(adr+1)|=(1<<(((bit-8)<<2))+2);}
}
// ��������� ������ �� ����� � �������������� ��������.
void PinOutAF_b (u32 *adr, u8 bit)
{
   if (bit<=7) {*adr|=3<<(bit<<2); *adr&=~(3<<((bit<<2)+2)); *adr|=(2<<((bit<<2)+2));} // ���� MODE=11 � CNF=01.
   else {*(adr+1)|=3<<((bit-8)<<2); *(adr+1)&=~(3<<(((bit-8)<<2))+2); *(adr+1)|=(2<<(((bit-8)<<2))+2);} 
}

/******************************************************************************

   �������:

   #define KEY    0 // ������ �� PA0.
   #define LED3   9 // ��������� LED3 �� PC9.
   #define LED4   8 // ��������� LED4 �� PC8.

   PinOutPP_b (PORTC, LED3); // ����� LED3 - ����������� �����.
   PinOutPP_b (PORTC, LED4); // ����� LED4 - ����������� �����.
   PinInputZ_b (PORTA, KEY); // ����� ����� �� ����.

 ******************************************************************************/
