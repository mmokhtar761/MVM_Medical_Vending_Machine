/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : UART_INT_H                                            */
/* Describtion   : UART communication protocol driver interface file     */
/* Date          : Nov 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef MAIN_H
#define MAIN_H
    /*************************************************************/
/*************************General config for the app**********************/
    /*************************************************************/

#define MySteppersNum 11
#define StartTimer()      BIT_H(T0CON,7);  //timer on 
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
    /*INIT all the steppers needed*/
    for (uint8 i=0; i<MySteppersNum;i++)
    {
        STPR_voidInitStpr (MyStprs+i,i,(uint16)2,3000,900);
    }
    //                         VAR|=  ((uint32)1<<BIT)
    //PORTD =0;
    while (1)
    {
        //UART_TxMsgSyn  ('x',100);
        //mymsg = UART_RxMsgSyn  (10000);
        LCD_SetCursor (3);
        __delay_ms(20);
        LCD_wStr   ((uint8 *)"I am here");
        //while(1);
        //STPR_voidMoveStprStps (MyStprs+1, 600 , DIR_High);
        
        //__delay_ms(500);
        //STPR_voidMoveStprStps (MyStprs+1, 600 , DIR_Low);
        // if (mymsg != -1 && mymsg!=-2) UART_TxArrMsg ((uint8 *)"I want to sleep", 16);
        //else UART_TxArrMsg ("ERROR", 6);
        //UART_TxMsgSyn  ('\n',100);
        //UART_TxMsgSyn  ('\r',100);
        __delay_ms(2000);


    }
    

}


#endif /*mainH*/