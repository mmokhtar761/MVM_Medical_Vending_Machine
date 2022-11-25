/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : LCD_CFG_H                                             */
/* Describtion   : LCD-driver config file                                */
/* Date          : Oct 2022                                              */
/* Version       : V02.00                                                */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef LCD_CFG_H
#define	LCD_CFG_H

/*Options: */
#define _8BIT_MODE 1
#define _4BIT_MODE 0
#define LINE_WIDTH _4BIT_MODE

#define LCDlines_ON_SAME_PORT   //Comment this line if they aren't

#ifdef  LCDlines_ON_SAME_PORT  //Lines are on PORTx starting from PINx
    #define LCD_dPORT   PORT_B
    #define LCD_dTRIS   TRIS_B
    #define LINE_ST_PIN PIN2     
#else
  //This feature needs more edits on LCD.c file

    #define LCD_d0PORT  PORTDbits.RD0
    #define LCD_d0TRIS  TRISD0

    #define LCD_d1PORT PORTDbits.RD1
    #define LCD_d1TRIS   TRISD1

    #define LCD_d2PORT PORTDbits.RD2
    #define LCD_d2TRIS   TRISD2

    #define LCD_d3PORT PORTDbits.RD3
    #define LCD_d3TRIS   TRISD3

    #define LCD_d4PORT PORTDbits.RD4
    #define LCD_d4TRIS   TRISD4

    #define LCD_d5PORT PORTDbits.RD5
    #define LCD_d5TRIS   TRISD5

    #define LCD_d6PORT PORTDbits.RD6
    #define LCD_d6TRIS   TRISD6

    #define LCD_d7PORT PORTDbits.RD7
    #define LCD_d7TRIS   TRISD7

#endif

#define RS_PORT PORT_A
//#define RS_TRIS TRISE0
#define RS_PIN  PIN1

#define RW_PORT PORT_A
//#define RW_TRIS TRISE0
#define RW_PIN  PIN2



#define E_PORT PORT_A
//#define E_TRIS TRISE0
#define E_PIN  PIN3

#define SET_PIN_HIGH(PORTx,PINx)      DIO_VidSetPinValue(PORTx,PINx,Pin_HIGH)
#define SET_PIN_LOW(PORTx,PINx)       DIO_VidSetPinValue(PORTx,PINx,Pin_LOW)


/*Incase of 8 line, you need to assign a Whole port*/
#if   LINE_WIDTH == _8BIT_MODE
#define Man_LINE(PORT_val)  DIO_VidSetPortValue(LCD_dPORT,PORT_val)
#define GET_LINE_VAL()      PORTB
#define SET_LINE_DIR_O()    DIO_VidSetPortDirection (LCD_dPORT,0x00)
#define SET_LINE_DIR_I()    DIO_VidSetPortDirection (LCD_dPORT,0xFF)
/*Incase of 4 line, you need to assign 4bit starting from ST_PIN*/
#elif LINE_WIDTH == _4BIT_MODE
#define Man_LINE(PORT_val)  DIO_VidSetPortNibble(LCD_dPORT,LINE_ST_PIN,PORT_val)
#define GET_LINE_VAL()      GET_NIBBLE(PORTB,LINE_ST_PIN)
#define SET_LINE_DIR_O()    DIO_VidDirPortNibble(LCD_dPORT,LINE_ST_PIN,0x0)
#define SET_LINE_DIR_I()    DIO_VidDirPortNibble(LCD_dPORT,LINE_ST_PIN,0xF)
#endif


/*Options*/
#define _1LINE     0
#define _2LINES    1
#define LINE_NUM  _2LINES
/*Options*/
#define _5x8DOTS   0
#define _5x11DOTS  1
#define CHAR_FONT  _5x11DOTS
/*Options*/
#define LEFT2RIGHT  2
#define RIGHT2LEFT  0
#define CURSOR_MV_DIR  LEFT2RIGHT

#endif	/* LCD_CFG_H */
