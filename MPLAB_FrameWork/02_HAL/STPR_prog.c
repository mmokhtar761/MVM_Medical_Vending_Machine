/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STPR_PROG_C                                           */
/*Describtion    : Stepper control driver module.c file                  */
/* Date          : Oct 2022                                              */
/* Version       : V01.0                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/

#define _XTAL_FREQ 16000000
#include <xc.h>

#include "Std_Types.h"
#include "MANIPULATOR.h"
//#include "DIO_cfg.h"
#include "DIO_int.h"
#include "STPR_cfg.h"
#include "STPR_int.h"
#include "STPR_prvt.h"



/*
 * This function must be called before any usage for the created stepper instant.
 * Copy_UniqueId: specifies the actual stepper connected in HW as configured in cfg file
 * Copy_stpVel: the needed number of steps per 1 sec
 * stprAccPerInterval: the needed increase in velocity witnin each configured time interval
 */
void STPR_voidInitStpr (STPR_type* ptrSTPR, uint8 Copy_UniqueId, uint16  Conpy_stpPerMm, uint16 Copy_stpVel, uint16  stprAccPerInterval)
{
    /*Check for the id passed*/
    if (Copy_UniqueId > MAX_STPR_uniqueID) return;
    ptrSTPR->UniqueId = Copy_UniqueId;
    ptrSTPR->stpPerMm = Conpy_stpPerMm;
    STPR_voidSetStprVel (ptrSTPR,Copy_stpVel);
    /*Evaluating the needed increase in */
    ptrSTPR->stprAccPerInterval  = stprAccPerInterval;
    /*Initialize the live velocity to INIT_VELOCITY*/
    arrSTPR_LiveVel[ptrSTPR->UniqueId] = INIT_VELOCITY;
    /*Initialization is ok*/
    ptrSTPR->stprStat = IDLE;
    return;
}

/*
 * Move the stepper some steps.
 */
void STPR_voidMoveStprStps (STPR_type* ptrSTPR, uint16  Copy_steps, STPR_Dir_type Copy_MveDir)
{
    uint16 i,satStps,accStps;
    uint32 width;
    if (ptrSTPR->stprStat != IDLE) return; /*not initialized correctlly, get out of here*/

    /*Set direction of moving*/
    if      (Copy_MveDir == DIR_High)  
    {
        SET_PIN_HIGH(ptrSTPR->UniqueId,DIR);
    }
    else if (Copy_MveDir == DIR_Low)   
    {
        SET_PIN_LOW(ptrSTPR->UniqueId,DIR);
    }

    /*Start Moving from INIT_VELOCITY with accelerating until reaching the velocity*/
    ptrSTPR->stprStat = ACC;
    for (i=0;arrSTPR_LiveVel[ptrSTPR->UniqueId] < ptrSTPR->stpVel;i++)
    {
        /*In this phase, width is dynamically calculated*/
        width= MICRO_PER_SEC/arrSTPR_LiveVel[ptrSTPR->UniqueId];
        GenPulse(ptrSTPR,width);
        if (EMERGANCY_Flag) return;
        /*If if more than the half of needed steps is gone, get out and deacc directly*/
        if (i >= Copy_steps/2) 
        {
            ptrSTPR->stprStat = DeAcc;
            break;
        }
    }

    /*if no direct deaccleration is needed, Move the steps in targetted velocity (sattle state)*/
    if (ptrSTPR->stprStat != DeAcc)
    {
        /*i in this point represents the number of steps to accelerate*/
        /*We need to count steps to move in Sat state befor deaceleratig for the same count of i */
        satStps= Copy_steps-i;
        ptrSTPR->stprStat = Sat;
        width = ptrSTPR->stpWidth;
        for (;i<satStps;i++)
        {
            GenPulse(ptrSTPR,width);
            if (EMERGANCY_Flag) return;
        }
    }
    /*Start Stopping with de-accelerating until reaching the INIT_VELOCITY then stop*/
    ptrSTPR->stprStat = DeAcc;
    for (;i< Copy_steps;i++)
    {
        /*In this phase, width is dynamically calculated*/
        if (ptrSTPR->stprStat != DeAcc || arrSTPR_LiveVel[ptrSTPR->UniqueId]<= MIN_STEPS_PER_SEC) break;
        width= MICRO_PER_SEC/arrSTPR_LiveVel[ptrSTPR->UniqueId];
        GenPulse(ptrSTPR,width);
        if (EMERGANCY_Flag) return;

    }
    /*Make sure that the stepper is re init to idle and min vel*/
    arrSTPR_LiveVel[ptrSTPR->UniqueId] = MIN_STEPS_PER_SEC;
    ptrSTPR->stprStat= IDLE;
}

/*
 * Move a pair of steppers some steps.
 */
void STPR_voidMovePairStps (STPR_type* ptrSTPR_1,STPR_type* ptrSTPR_2, uint16  Copy_steps, STPR_Dir_type Copy_MveDir)
{
    uint16 i,satStps,accStps;
    uint32 width;
    if (ptrSTPR_1->stprStat != IDLE || ptrSTPR_2->stprStat != IDLE || EMERGANCY_Flag !=0 ) return; /*not initialized correctlly, get out of here*/

    /*Set direction of moving*/
    if      (Copy_MveDir == DIR_High)  
    {
        SET_PIN_HIGH(ptrSTPR_1->UniqueId,DIR);
        SET_PIN_HIGH(ptrSTPR_2->UniqueId,DIR);
    }
    else if (Copy_MveDir == DIR_Low)   
    {
        SET_PIN_LOW(ptrSTPR_1->UniqueId,DIR);
        SET_PIN_LOW(ptrSTPR_2->UniqueId,DIR);
    }

    /*Start Moving from INIT_VELOCITY with accelerating until reaching the velocity*/
    ptrSTPR_1->stprStat = ACC;


    for (i=0;arrSTPR_LiveVel[ptrSTPR_1->UniqueId] < ptrSTPR_1->stpVel;i++)
    {
        /*In this phase, width is dynamically calculated*/
        width= MICRO_PER_SEC/arrSTPR_LiveVel[ptrSTPR_1->UniqueId];
        GenPulse(ptrSTPR_1,width);
        GenPulse(ptrSTPR_2,width);
        if (EMERGANCY_Flag) return;
        /*If if more than the half of needed steps are gone, get out and deacc directly*/
        if (i >= Copy_steps/2) 
        {
            ptrSTPR_1->stprStat = DeAcc;
            break;
        }
    }

    /*if no direct deaccleration is needed, Move the steps in targetted velocity (sattle state)*/
    if (ptrSTPR_1->stprStat != DeAcc)
    {
        /*i in this point represents the number of steps to accelerate*/
        /*We need to count steps to move in Sat state befor deaceleratig for the same count of i */
        satStps= Copy_steps-i;
        ptrSTPR_1->stprStat = Sat;
        width = ptrSTPR_1->stpWidth;
        for (;i<satStps;i++)
        {
            GenPulse(ptrSTPR_1,width);
            GenPulse(ptrSTPR_2,width);
            if (EMERGANCY_Flag) return;

        }
    }
    /*Start Stopping with de-accelerating until reaching the INIT_VELOCITY then stop*/
    ptrSTPR_1->stprStat = DeAcc;
    for (;i< Copy_steps;i++)
    {
        /*In this phase, width is dynamically calculated*/
        if (ptrSTPR_1->stprStat != DeAcc || arrSTPR_LiveVel[ptrSTPR_1->UniqueId]<= MIN_STEPS_PER_SEC) break;
        width= MICRO_PER_SEC/arrSTPR_LiveVel[ptrSTPR_1->UniqueId];
        GenPulse(ptrSTPR_1,width);
        GenPulse(ptrSTPR_2,width);
        if (EMERGANCY_Flag) return;

    }
    /*Make sure that the stepper is re init to idle and min vel*/
    arrSTPR_LiveVel[ptrSTPR_1->UniqueId] = MIN_STEPS_PER_SEC;
    ptrSTPR_1->stprStat= IDLE;
}


/*
 * Move the stepper some mm.
 */
void STPR_voidMoveStprMm (STPR_type* ptrSTPR, uint16  Copy_distMm, STPR_Dir_type Copy_MveDir)
{
    STPR_voidMoveStprStps (ptrSTPR, (Copy_distMm / ptrSTPR->stpPerMm),Copy_MveDir);
}

/*
 * Rotate the stepper some degrees (0-360).
 */
void STPR_voidRotateStprDegr (STPR_type* ptrSTPR, uint16  Copy_angleDeg,float32 Copy_stpAngle, STPR_Dir_type Copy_MveDir)
{
    STPR_voidMoveStprStps (ptrSTPR, (uint16)(Copy_angleDeg / Copy_stpAngle),Copy_MveDir);
}

/*
 * Edits the step per mm for the stepper
 */
void STPR_voidCalibStpMm (STPR_type* ptrSTPR, uint8  stpPerMm)
{
   if (ptrSTPR->stprStat != IDLE) return; /*not initialized correctlly or moving, get out of here*/
   ptrSTPR->stpPerMm = stpPerMm;
}

/*
 * Edits the velocity for the stepper
 */
void STPR_voidSetStprVel (STPR_type* ptrSTPR, uint16 Copy_stpVel)
{
    if (ptrSTPR->stprStat != IDLE) return; /*not initialized correctlly or moving, get out of here*/
    if      (Copy_stpVel>MAX_STEPS_PER_SEC) 
    {
        ptrSTPR->stpVel   = MAX_STEPS_PER_SEC;
        ptrSTPR->stpWidth = MIN_PULSE_WIDTH ;           /*In micro seconds*/
    }
    else if (Copy_stpVel<MIN_STEPS_PER_SEC) 
    {
        ptrSTPR->stpVel   = MIN_STEPS_PER_SEC;
        ptrSTPR->stpWidth = MAX_PULSE_WIDTH ;           /*In micro seconds*/
    }
    else                                    
    {
        ptrSTPR->stpVel   = Copy_stpVel;
        ptrSTPR->stpWidth = MICRO_PER_SEC/Copy_stpVel;  /*In micro seconds*/
    }
}

/*
 * Edits the acceleration for the stepper
 */
void STPR_voidSetStprAcc (STPR_type* ptrSTPR, uint16 Copy_AccPerInterval)
{
    if (ptrSTPR->stprStat != IDLE) return; /*not initialized correctlly or moving, get out of here*/
    ptrSTPR->stprAccPerInterval = Copy_AccPerInterval;
}

/*
* Called in ISR for a timer within each "ACC_INTERVAL"
*/
 void STPR_callBack(STPR_type* ptrSTPR)
 {
    if (ptrSTPR->stprStat == IDLE || ptrSTPR->stprStat == Sat) return; /*not initialized correctlly, get out of here*/
    switch (ptrSTPR->stprStat)
    {
        case ACC:
            arrSTPR_LiveVel[ptrSTPR->UniqueId] += ptrSTPR->stprAccPerInterval;
            break;
        case DeAcc:
            if (arrSTPR_LiveVel[ptrSTPR->UniqueId] <= MIN_STEPS_PER_SEC)
            {
                arrSTPR_LiveVel[ptrSTPR->UniqueId] = MIN_STEPS_PER_SEC;
                ptrSTPR->stprStat= IDLE;
            }
            else
            {
                arrSTPR_LiveVel[ptrSTPR->UniqueId] -= ptrSTPR->stprAccPerInterval;
            }
            break;
        case IDLE:
            /*do no thing*/
            break;
        case Sat:
            /*do no thing*/
            break;
    }
 }

 void STOP_STPRS_Emergancy(void)
 {
    EMERGANCY_Flag=0xFF;
 }
 void Clear_EMERGANCY(void)
 {
    EMERGANCY_Flag=0;
 }

 /*
 void STPR_callBack(STPR_type* ptrSTPR)
 {
    if (arrSTPR_LiveVel[ptrSTPR->UniqueId] < ptrSTPR->stpVel) 
    {
        arrSTPR_LiveVel[ptrSTPR->UniqueId]=(sint16)arrSTPR_LiveVel[ptrSTPR->UniqueId] + ptrSTPR->stprAccPerInterval;
        
        if ( ptrSTPR->stprAccPerInterval >0) arrAccIntervalCount[ptrSTPR->UniqueId]++;
        else                                 arrAccIntervalCount[ptrSTPR->UniqueId]--;
    }
    else
    {
        arrSTPR_LiveVel[ptrSTPR->UniqueId] =  ptrSTPR->stpVel;
    }
 }*/