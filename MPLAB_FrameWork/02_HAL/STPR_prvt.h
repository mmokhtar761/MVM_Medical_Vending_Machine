/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STPR_PRVT_H                                           */
/*Describtion    : Stepper control driver private file                   */
/* Date          : Oct 2022                                              */
/* Version       : V01.0                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef STPR_PRVT_H
#define STPR_PRVT_H

#define MAX_STPR_uniqueID   (MAX_STPR_NUM-1)
#define MICRO_PER_SEC       (uint32)(1000000)

#define MIN_PULSE_WIDTH     (STP_MIN_LOW_PULSE_WIDTH + STP_MIN_HIGH_PULSE_WIDTH) /*In micro seconds*/
#define MAX_STEPS_PER_SEC   (uint16)(MICRO_PER_SEC/MIN_PULSE_WIDTH)

#define MAX_PULSE_WIDTH     (STP_MAX_HIGH_PULSE_WIDTH + STP_MAX_LOW_PULSE_WIDTH) /*In micro seconds*/
#define MIN_STEPS_PER_SEC   (uint16)(MICRO_PER_SEC/MAX_PULSE_WIDTH)

/*The initial velocity(&Pulse width)the steppers start to accelerate from*/
#define INIT_PULSE_WIDTH    (MAX_PULSE_WIDTH)                  /*In micro seconds*/
#define INIT_VELOCITY       (MICRO_PER_SEC/INIT_PULSE_WIDTH)   /*In: Steps per secound*/

uint32 arrSTPR_LiveVel[MAX_STPR_NUM];

uint8 EMERGANCY_Flag =0;

//uint32 arrAccIntervalCount[MAX_STPR_NUM];

void GenPulse(STPR_type* ptrSTPR , uint32 stpWidth)
{
    SET_PIN_LOW(ptrSTPR->UniqueId,STP);
    BUSY_uSec(stpWidth/2);
    SET_PIN_HIGH(ptrSTPR->UniqueId,STP);
    BUSY_uSec(stpWidth/2);
}

#endif /* STPR_PRVT_H*/
