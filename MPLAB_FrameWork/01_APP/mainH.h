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
#define FrstOrderIndex  1

#define StprAUniqueID 0
#define StprBUniqueID 1
#define FrstStepperUniqueID 2

#define NumOfRows 3
#define NumOfCol  3
#define LIMIT_OFFSET 100

#define STPS_FOR_AN_ITEM 200
 
#define PIR_PORT     PORT_C
#define PIR_PIN      PIN0

#define TempO_PORT     PORT_B
#define TempO_PIN      PIN1

#define HighTempLimit 28 /*Value above which the fan starts */
#define LowTempLimit  25 /*Value below which the fan stops*/
/*Options*/
/*
EXTI0.
EXTI1
EXTI2
*/
#define EXT_IRQ_CHANNEL EXTI0

#define StartTimer()      BIT_H(T0CON,7);  //timer on 

#define GET_ROW(itemInd) ((itemInd/3)+1)

uint8 currentRow = 0;
uint8 PersonExist = 0;

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

void PrintTemp(sint16 tempVal)
{
  uint8 * TempStr = " 25 degCel";
  if (tempVal<0) 
  {
    TempStr[0] = '-';
    tempVal*=-1;
  }
  else           TempStr[0] = ' ';

  /*assigneng the first box value*/
  TempStr[1] = (tempVal%10) + '0'; 
  /*assigneng the second box value*/
  TempStr[2] = (tempVal/10) + '0';


  LCD_SetCursor (1);
  LCD_wStr   ("System Temp is:    ");
  LCD_wStr   (TempStr);
  /*to clear any extra data remaining on the LCD*/
  LCD_wStr   ("   ");
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
    /*init external interrupt to detect the emergancy*/
    EXIT_Int();
    /*Enable the needed channel*/
    #if   EXT_IRQ_CHANNEL == EXTI0 
    EXIT0_Enable();
    #elif EXT_IRQ_CHANNEL == EXTI1
    EXIT1_Enable();
    #elif EXT_IRQ_CHANNEL == EXTI2
    EXIT2_Enable();
    #endif

    /*************************************************************/
    /**********************Init HAL modules***********************/
    /*************************************************************/
    /*LCD init communication 4 line mode*/
    LCD_voidInit ();   
    LCD_wCmd   (Clear_Display_cmd);
    LCD_SetCursor (1);
    /*INIT all the steppers needed*/
    for (uint8 i=0; i<MySteppersNum;i++) STPR_voidInitStpr (MyStprs+i,i,(uint16)2,3000,900);

    /*Move lever Home, STOP on external interrupt and return*/
    STPR_voidMovePairStps (&MyStprs[StprAUniqueID],&MyStprs[StprBUniqueID], NumOfRows*STEPS_PER_ROW , DIR_Low);
    /*Clearing emergancy limit switch*/
    Clear_EMERGANCY();
    /*moving an offset*/
    STPR_voidMovePairStps (&MyStprs[StprAUniqueID],&MyStprs[StprBUniqueID], LIMIT_OFFSET , DIR_High);
    currentRow  = 0;
}

void moveLvr2Row (uint8 row)
{
  uint8 rowsToMove;

  STPR_Dir_type myDir;
  if      (row == currentRow ) return;
  /*Choosing the right dir and num of rows to be moved*/
  else if (row > currentRow) 
  {
    myDir = DIR_High;
    rowsToMove = currentRow - row;
  }
  else if (row < currentRow) 
  {
    myDir = DIR_Low;
    rowsToMove = currentRow - row;
  }
  /*Move lever in the right direction with the needed steps*/  
  STPR_voidMovePairStps (&MyStprs[StprAUniqueID],&MyStprs[StprBUniqueID], rowsToMove*STEPS_PER_ROW , myDir);
  /*lever is on the required row*/
  currentRow = row;
  /*mission complete*/
  return;
}

uint8 IS_SomeOneThere(void)
{
  if ( DIO_u8GetPinValue(PIR_PORT, PIR_PIN ) ) 
  {
    __delay_ms(20);
    if ( DIO_u8GetPinValue(PIR_PORT, PIR_PIN ) ) return 1;
    /*else false signal*/
  }
  return 0;
}

#endif /*mainH*/

