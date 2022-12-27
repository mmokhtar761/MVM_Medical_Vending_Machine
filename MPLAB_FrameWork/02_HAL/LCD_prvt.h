/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : LCD_PRVT_H                                            */
/* Describtion   : LCD-driver private file                               */
/* Date          : Oct 2022                                              */
/* Version       : V02.00                                                */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef LCD_PRVT_H
#define LCD_PRVT_H

#define SET_RS SET_PIN_HIGH(RS_PORT,RS_PIN)
#define CLR_RS SET_PIN_LOW(RS_PORT,RS_PIN)

#define SET_RW SET_PIN_HIGH(RW_PORT,RW_PIN)
#define CLR_RW SET_PIN_LOW(RW_PORT,RW_PIN)
/*************************************************************************/
/**************************Private CMD***********************************/
/*************************************************************************/
#define ENTRY_MODE_SET_CMD (0b100+LEFT2RIGHT)
#define FUNCTION_SET       ((1<<5)+(LINE_WIDTH<<4)+(LINE_NUM<<3)+(CURSOR_MV_DIR))

#define E_Pwidth           (5) //(ms) (1)

/*
  The enable pin is used by the LCD to latch information presented to its data pins.
  When data is supplied to the data pins, a high-to-low pulse must be applied to this pin in order for 
  the LCD to latch in the data present at the data pins. 
  This pulse must be a minimum of 450ns wide.
*/
void LAT_data (uint8 data){
  
  #if LINE_WIDTH == _4BIT_MODE
  /*Latch the high half of the cmd*/
  Man_LINE(data >>4);
  __delay_ms(E_Pwidth);
  SET_PIN_HIGH(E_PORT,E_PIN);
  __delay_ms(E_Pwidth);
  SET_PIN_LOW(E_PORT,E_PIN);              //To latch data
  __delay_ms(E_Pwidth);
  /*Make the lower half ready*/
  data &= 0x0F;
  #endif

  Man_LINE(data );
    __delay_ms(1);
  SET_PIN_HIGH(E_PORT,E_PIN);
  __delay_ms(E_Pwidth);
  SET_PIN_LOW(E_PORT,E_PIN);              //To latch data
  __delay_ms(E_Pwidth);
}

#endif /* LCD_PRVT_H*/
