/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : LCD_INT_H                                             */
/* Describtion   : LCD-driver interface file                             */
/* Date          : Oct 2022                                              */
/* Version       : V02.00                                                */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef LCD_INT_H
#define LCD_INT_H
/*************************************************************************/
/*-------------------------Command LCD instructions----------------------*/
/*************************************************************************/

//Clears entire display ands ets DDRAM address 0 inaddress counter.
#define Clear_Display_cmd (1)  
/*Gets the cursor to the first segment*/
#define Return_Home_cmd   (2)  //Takes (>=2ms)

#define DISPLAY_OFF       (8)

#define DISPLAY_ON        (12)

#define DISP_cursor       (14)

#define cursor_BLNK       (15)
#define cursor_FIXD       (14)

#define MV_CURSOR_L       (16)
#define MV_CURSOR_R       (20)
#define MV_DIPLAY_L       (24)
#define MV_DIPLAY_R       (28)





void  LCD_voidInit   (void);
/*returns The busy flag status*/
uint8 IS_BUSY (void); 
void  LCD_SetCursor (uint8 p);
void  LCD_wCmd   (uint8 d);
void  LCD_wData  (uint8 d);
void  LCD_wStr   (uint8* str);
#endif  /*LCD_INT_H*/