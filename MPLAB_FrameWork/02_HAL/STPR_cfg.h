/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STPR_CFG_H                                            */
/*Describtion    : Stepper control driver config file                    */
/* Date          : Oct 2022                                              */
/* Version       : V01.0                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef STPR_CFG_H
#define STPR_CFG_H

#define STP_MIN_HIGH_PULSE_WIDTH  4       /*In micro seconds*/
#define STP_MIN_LOW_PULSE_WIDTH   4       /*In micro seconds*/

#define STP_MAX_HIGH_PULSE_WIDTH  12500   /*In micro seconds*/
#define STP_MAX_LOW_PULSE_WIDTH   12500   /*In micro seconds*/

#define MAX_STPR_NUM              11      /*The max intended number of steppers*/

/************************CONST macros, never touch************************/
#define STP     0
#define DIR     1 
#define STP_DIR 2
/*************************************************************************/
/***************************GPIO config section***************************/
/**************This section is dependent on MCAL GPIO driver**************/
/*************************************************************************/
#define PORT_TYPE     uint8
#define PIN_TYPE      uint8
#define NOT_CONNECTED 0xFF        

/*
*Please add a line for each connected stepper and config its step,direction ports
*Incase of no connected direction pin, please assign NOT_CONNECTED macro to it 
*/
const PORT_TYPE STPR_arrStpDirPorts[MAX_STPR_NUM][STP_DIR] =
{
    {PORT_A,PORT_A}, /*STEP,DIRECTION Port  config for stepper unique id 0*/
    {PORT_E,PORT_E}, /*STEP,DIRECTION Port  config for stepper unique id 1*/
    {PORT_D,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 2*/
    {PORT_D,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 3*/
    {PORT_D,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 4*/
    {PORT_D,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 5*/
    {PORT_D,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 6*/
    {PORT_D,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 7*/
    {PORT_D,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 8*/
    {PORT_D,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 9*/
    {PORT_E,NOT_CONNECTED}, /*STEP,DIRECTION Port  config for stepper unique id 10*/
};
/*
*Please add a line for each connected stepper and config its step,direction pins
*Incase of no connected direction pin, please assign NOT_CONNECTED macro to it 
*/
const PIN_TYPE STPR_arrDirPortPin[MAX_STPR_NUM][STP_DIR] =
{
    {PIN4,PIN5}, /*STEP,DIRECTION Pin  config for stepper unique id 0*/
    {PIN1,PIN0}, /*STEP,DIRECTION Pin  config for stepper unique id 1*/
    {PIN7,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 2*/
    {PIN6,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 3*/
    {PIN5,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 4*/
    {PIN4,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 5*/
    {PIN3,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 6*/
    {PIN2,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 7*/
    {PIN1,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 8*/
    {PIN0,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 9*/
    {PIN7,NOT_CONNECTED}, /*STEP,DIRECTION Pin  config for stepper unique id 10*/
};


#define SET_PIN_HIGH(stprUniqueId,stp_dir)      DIO_VidSetPinValue(STPR_arrStpDirPorts[stprUniqueId][stp_dir], STPR_arrDirPortPin[stprUniqueId][stp_dir],HIGH);
#define SET_PIN_LOW(stprUniqueId,stp_dir)       DIO_VidSetPinValue(STPR_arrStpDirPorts[stprUniqueId][stp_dir], STPR_arrDirPortPin[stprUniqueId][stp_dir],LOW);

#define BUSY_uSec(Time_uSec)\                    
for (int mc = 0; mc < Time_uSec; mc++)\
{\
   __delay_us(1);\
}\

#endif  /*STPR_CFG_H*/