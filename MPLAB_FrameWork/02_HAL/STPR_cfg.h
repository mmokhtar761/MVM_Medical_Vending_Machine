/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STPR_CFG_H                                            */
/*Describtion    : Stepper control driver config file                    */
/* Date          : Oct 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef STPR_CFG_H
#define STPR_CFG_H

#define STP_MIN_HIGH_PULSE_WIDTH  4   /*In micro seconds*/
#define STP_MIN_LOW_PULSE_WIDTH   4   /*In micro seconds*/
#define MAX_STPR_NUM             11   /*The max intended number of steppers*/

/************************CONST macros, never touch************************/
#define STP     0
#define DIR     1 
#define STP_DIR 2
/*************************************************************************/
/***************************GPIO config section***************************/
/**************This section is dependent on MCAL GPIO driver**************/
/*************************************************************************/
#define PORT_TYPE
#define PIN_TYPE
#define NOT_CONNECTED             

/*
*Please add a line for each connected stepper and config its step,directin ports
*Incase of no connected direction pin, please assign NOT_CONNECTED macro to it 
*/
const PORT_TYPE STPR_arrStpDirPorts[MAX_STPR_NUM][STP_DIR] =
{
    {,}, /*STEP,DIRECTION Port  config for steper unique id 0*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 1*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 2*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 3*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 4*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 5*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 6*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 7*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 8*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 9*/
    {,}, /*STEP,DIRECTION Port  config for steper unique id 10*/
};
/*
*Please add a line for each connected stepper and config its step,directin pins
*Incase of no connected direction pin, please assign NOT_CONNECTED macro to it 
*/
const PIN_TYPE STPR_arrDirPortPin[MAX_STPR_NUM][STP_DIR] =
{
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 0*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 1*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 2*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 3*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 4*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 5*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 6*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 7*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 8*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 9*/
    {,}, /*STEP,DIRECTION Pin  config for steper unique id 10*/
};


#define SET_STP_PIN_HIGH(stprUniqueId)  GPIO_set_Pin(STPR_arrStpDirPorts[stprUniqueId][STP], STPR_arrDirPortPin[stprUniqueId][STP])
#define SET_STP_PIN_LOW(stprUniqueId)   GPIO_set_Pin(STPR_arrStpDirPorts[stprUniqueId][STP], STPR_arrDirPortPin[stprUniqueId][STP])

#define SET_DIR_PIN_HIGH(stprUniqueId)  GPIO_set_Pin(STPR_arrStpDirPorts[stprUniqueId][DIR], STPR_arrDirPortPin[stprUniqueId][DIR])
#define SET_DIR_PIN_LOW(stprUniqueId)   GPIO_set_Pin(STPR_arrStpDirPorts[stprUniqueId][DIR], STPR_arrDirPortPin[stprUniqueId][DIR])


#endif  /*STPR_CFG_H*/