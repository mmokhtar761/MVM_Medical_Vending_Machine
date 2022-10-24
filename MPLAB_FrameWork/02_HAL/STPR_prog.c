/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STPR_PROG_C                                           */
/*Describtion    : Stepper control driver module.c file                  */
/* Date          : Oct 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/

#include "Std_Types.h"
#include "MANIPULATOR.h"
#include "STPR_cfg.h"
#include "STPR_int.h"
#include "STPR_prvt.h"



/*
 * This function must be called before any usage for the created stepper instant.
 * Copy_UniqueId: specifies the actual stepper connected in HW as configured in cfg file
 * Copy_stpVel: the needed number of steps per 1 sec
 */
void STPR_voidInitStpr (STPR_type* ptrSTPR, uint8 Copy_UniqueId, uint16  Conpy_stpPerMm, uint32 Copy_stpVel, uint8  Copy_stprAcc)
{
    ptrSTPR->UniqueId = Copy_UniqueId;
    ptrSTPR->stpPerMm = Conpy_stpPerMm;
    if (Copy_stpVel>MAX_STEPS_PER_SEC) ptrSTPR->stpVel = MAX_STEPS_PER_SEC;
    else                               ptrSTPR->stpVel = Copy_stpVel;
    ptrSTPR->stprAcc  = Copy_stprAcc;
    ptrSTPR->InitFlag = STPR_Init_OK;
}

/*
 * Move the stepper some steps.
 */
void STPR_voidMoveStprStps (STPR_type* ptrSTPR, uint16  Copy_steps, STPR_Dir_type Copy_MveDir)
{
    if (ptrSTPR->InitFlag != STPR_Init_OK) return; /*not initialized correctlly, get out of here*/
    /*Set direction of moving*/
    if      (Copy_MveDir == DIR_High)  SET_DIR_PIN_HIGH(ptrSTPR->UniqueId);
    else if (Copy_MveDir == DIR_Low)   SET_DIR_PIN_LOW(ptrSTPR->UniqueId);

    /*Start Moving with accelerating for the half of steps*/

    /*Start Stopping with de-accelerating for the other half*/

}



/*
 * Move the stepper some mm.
 */
void STPR_voidMoveStprMm (STPR_type* ptrSTPR, uint16  Copy_distMm, STPR_Dir_type Copy_MveDir)
{
    if (ptrSTPR->InitFlag != STPR_Init_OK) return; /*not initialized correctlly, get out of here*/


}

/*
 * Rotate the stepper some degrees (0-360).
 */
void STPR_voidRotateStprDegr (STPR_type* ptrSTPR, uint16  Copy_angleDeg,float32 Copy_stpAngle, STPR_Dir_type Copy_MveDir)
{
    if (ptrSTPR->InitFlag != STPR_Init_OK) return; /*not initialized correctlly, get out of here*/

}

/*
 * Edits the step per mm for the stepper
 */
void STPR_voidCalibStpMm (STPR_type* ptrSTPR, uint8  stpPerMm)
{
    if (ptrSTPR->InitFlag != STPR_Init_OK) return; /*not initialized correctlly, get out of here*/

}

/*
 * Edits the velocity for the stepper
 */
void STPR_voidSetStprVel (STPR_type* ptrSTPR, uint8 Copy_stpVel)
{
    if (ptrSTPR->InitFlag != STPR_Init_OK) return; /*not initialized correctlly, get out of here*/

}

/*
 * Edits the acceleration for the stepper
 */
void STPR_voidSetStprAcc (STPR_type* ptrSTPR, uint8 Copy_stprAcc)
{
    if (ptrSTPR->InitFlag != STPR_Init_OK) return; /*not initialized correctlly, get out of here*/

}