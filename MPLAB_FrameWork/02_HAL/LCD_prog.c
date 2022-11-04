/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : LCD_PROG_C                                            */
/* Describtion   : LCD-driver module.c file                              */
/* Date          : Oct 2022                                              */
/* Version       : V02.00                                                */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#define _XTAL_FREQ 8000000     //16 Mhz External crystal
#include <xc.h>
#include "Std_Types.h"
#include "MANIPULATOR.h"

#include "DIO_cfg.h"
#include "DIO_int.h"

#include "LCD_cfg.h"
#include "LCD_int.h"
#include "LCD_prvt.h"



#define SET_RS SET_PIN_HIGH(RS_PORT,RS_PIN)
#define CLR_RS SET_PIN_LOW(RS_PORT,RS_PIN)

#define SET_RW SET_PIN_HIGH(RW_PORT,RW_PIN)
#define CLR_RW SET_PIN_LOW(RW_PORT,RW_PIN)


void  LCD_voidInit   (void)
{
  /*RS/RW/E Pins Directions must be handeled by the user befor initialization*/
/*
  RW_D =0;
  RS_D =0;
  E_D  =0;     
  */
  SET_LINE_DIR_O();
  __delay_ms(20);		/* wait LCD Power to sattle */
  CLR_RW;
  CLR_RS;
  LAT_data (FUNCTION_SET);  //Function set command
  __delay_ms(10);         // Wait for more than 4.1 ms
  LAT_data (FUNCTION_SET);// Latch it again
  __delay_us(500);       //Wait for more than 100 us
  LAT_data (FUNCTION_SET); // Latch it again (>37us)
  __delay_us(100);    

  //The number of display lines and character font cannot be changed after this point.
  LAT_data (FUNCTION_SET); //0b0011NF** FUNCTION SET  (>37us)
  __delay_us(100);    
  
  LAT_data (DISPLAY_ON); //0b00001DCB Display ON/OFF con (>37us)
  __delay_us(100);  
  
  LAT_data (Clear_Display_cmd);         // Clear Display
  __delay_us(100);  
  LAT_data (ENTRY_MODE_SET_CMD);//0b00001(I/D)S Entry mode Set   (>37us)
  __delay_ms(3);
}



uint8 IS_BUSY (void)
{
  uint8 tempLineVal;
  
  SET_LINE_DIR_I();
  CLR_RS;
  SET_RW;
  tempLineVal = GET_LINE_VAL();
  SET_LINE_DIR_O();
  #if LINE_WIDTH == _8BIT_MODE
  return (tempLineVal >>7);
  #elif LINE_WIDTH == _4BIT_MODE
  return (tempLineVal >>3);
  #endif
}

void  LCD_wCmd   (uint8 d)
{
  //while (IS_BUSY());
  CLR_RS;
  CLR_RW;
  SET_LINE_DIR_O();

  LAT_data (d); //latching the command
  __delay_ms(20);
}

void  LCD_wData  (uint8 d){
  //while (IS_BUSY());
  SET_RS;
  CLR_RW;
  SET_LINE_DIR_O();
  LAT_data (d); //latching the data
  __delay_ms(20);
}

void  LCD_SetCursor (uint8 p)
{
  if (p>16) p += 48;
  LCD_wCmd(128+p-1);
  __delay_ms(20);
}


void  LCD_wStr   (uint8* str)
{
    uint8 i;
  //while (IS_BUSY());
  SET_RS;
  CLR_RW;
  SET_LINE_DIR_O();
  for(i=0;str[i]!='\0';i++){
    LAT_data (str[i]); //latching the data
    __delay_ms(20);
    if (i==15) LCD_SetCursor (17);
  }
  if (i>=30){
    //  Set_Cursor (1);
        
    LCD_wCmd(Return_Home_cmd);
    __delay_ms(20);
  }        
}
