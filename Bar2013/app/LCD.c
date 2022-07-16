#include "hd44780_driver.h"
#include "LCD.h"
#include "bmp085.h"

unsigned char       Char_0[]={0x0E,0x11,0x11,0x11,0x11,0x0A,0x11,0x11};
char DispString[12]={0};
int32_t temperature=0;
int32_t pressure=0;
         
void ConfigureLCD(void){
lcd_init(); //Display Init
lcd_set_user_char(0, Char_0); // Set char
lcd_clear(); // clear LCD
lcd_out("This is fish");
lcd_clear(); // clear LCD
}

void DisplayPressure(float Pressure){
 temperature = bmp085_read_temperature();
 pressure = bmp085_read_pressure();
 if(temperature > 305){
 temperature-- ;
 }
 DispString[0] = temperature/1000 + 0x30;
 DispString[1] = (temperature%1000)/100 + 0x30;
 DispString[2] = (temperature%100)/10 + 0x30;
 DispString[3] = temperature%10 + 0x30;
 lcd_clear(); // clear LCD
 lcd_out(DispString);
 
return;
}