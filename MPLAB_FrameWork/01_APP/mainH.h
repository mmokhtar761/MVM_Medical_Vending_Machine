/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : MAIN_H                                                */
/* Describtion   : Main app header file                                  */
/* Date          : Nov 2022                                              */
/* Version       : V01.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef MAIN_H
#define MAIN_H
/*************************************************************************/
/*************************General config for the app**********************/
/*************************************************************************/

#define MySteppersNum   11
#define STEPS_PER_ROW   500
#define NTC_RES_25      10000
#define SER_RES_VAL_NTC 10000

#define MAX_ORDER_COUNT 9
#define myTimeOutCount  5000
#define OrderSizeIndex  0
#define FrstOrderIndex  OrderSizeIndex+1

#define StprAUniqueID 0
#define StprBUniqueID 1
#define FrstStepperUniqueID 2
 
#define StartTimer()      BIT_H(T0CON,7);  //timer on 

#define GET_ROW(itemInd) ((itemInd/3)+1)

/*Array of stepper handlers*/
STPR_type MyStprs [MySteppersNum];



void initT0Spaghetti(void)
{
        /*Timer  50ms */
        TMR0H = 0x3C;
        TMR0L = 0xAF;
        T0CON = 0b00000011;
        INTCONbits.GIE=1;
        INTCONbits.T0IE =1;
}

sint16 GetNTC_temp(uint16 ADC_val)
{
    sint32 tempVal;
    /*Guard if there is any problem*/
    if (ADC_val==1023 || ADC_val==0) return -273;

    /*
    * Calc the resistanse of the NTC with:
    *   The voltage relative value(ADC Read) 
    *   The series resistor 
    * are known
    */
    tempVal = ((1023.0-ADC_val)/ADC_val*1.0)*SER_RES_VAL_NTC;  
    /*Converting the resistance into degree of celsius*/
    tempVal = (sint16)((3950/(long double)(298*log(tempVal)+1205.3185))*298-273.25);

    return tempVal;
}

void INIT_SYS (void)
{
    /*************************************************************/
    /**********************Init MCAL modules**********************/
    /*************************************************************/
    /*Init pins dir as configured*/
    DIO_Inti(); 
    /*ADC initialization*/
    ADC_VoidInit();
    /*Init UART to communicate with esp*/
    UART_voidInit ();
    /*Timer of an interval interrupt to be used by stepper module*/
    initT0Spaghetti();
    /*************************************************************/
    /**********************Init HAL modules***********************/
    /*************************************************************/
    /*LCD init communication 4 line mode*/
    LCD_voidInit ();   
    LCD_wCmd   (Clear_Display_cmd);
    LCD_SetCursor (1);
    /*INIT all the steppers needed*/
    for (uint8 i=0; i<MySteppersNum;i++) STPR_voidInitStpr (MyStprs+i,i,(uint16)2,3000,900);
}


void moveLvr2Row (uint8 row)
{
  int i=0;
  static uint8 currentRow = 0;
  STPR_Dir_type myDir;
  if      (row == currentRow ) return;
  else if (row > currentRow) myDir = DIR_High;
  else if (row < currentRow) myDir = DIR_Low;
  /*Move lever in the right direction with the needed steps*/
  //if (row == 0) 
  for (i=0 ; i< STEPS_PER_ROW;i+=2)
    {
        STPR_voidMoveStprStps (&MyStprs[StprAUniqueID], 2 , myDir);
        STPR_voidMoveStprStps (&MyStprs[StprBUniqueID], 2 , myDir);
    }
  /*lever is on the required row*/
  /*mission complete*/
  return;
}
#endif /*mainH*/

