/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STPR_INT_H                                            */
/*Describtion    : Stepper control driver interface file                 */
/* Date          : Oct 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef STPR_INT_H
#define STPR_INT_H

typedef enum
{
  STPR_NotInit,
  STPR_Init_OK,
} STPR_InitStat_type;

typedef enum
{
  DIR_Low,
  DIR_High,
} STPR_Dir_type;


typedef struct
{
  uint8   UniqueId;
  uint16  stpPerMm;
  uint32  stpVel;
  uint8   stprAcc;
  STPR_InitStat_type  InitFlag;
} STPR_type;



/*
 * This function must be called before any usage for the created stepper instant.
 * Copy_UniqueId: specifies the actual stepper connected in HW as configured in cfg file
 * Copy_stpVel: the needed number of steps per 1 sec
 */
void STPR_voidInitStpr (STPR_type* ptrSTPR, uint8 Copy_UniqueId, uint16  Conpy_stpPerMm, uint32 Copy_stpVel, uint8  Copy_stprAcc);

/*
 * Move the stepper some steps.
 */
void STPR_voidMoveStprStps (STPR_type* ptrSTPR, uint16  Copy_steps, STPR_Dir_type Copy_MveDir);

/*
 * Move the stepper some mm.
 */
void STPR_voidMoveStprMm (STPR_type* ptrSTPR, uint16  Copy_distMm, STPR_Dir_type Copy_MveDir);

/*
 * Rotate the stepper some degrees (0-360).
 */
void STPR_voidRotateStprDegr (STPR_type* ptrSTPR, uint16  Copy_angleDeg,float32 Copy_stpAngle, STPR_Dir_type Copy_MveDir);

/*
 * Edits the step per mm for the stepper
 */
void STPR_voidCalibStpMm (STPR_type* ptrSTPR, uint8  stpPerMm);

/*
 * Edits the velocity for the stepper
 */
void STPR_voidSetStprVel (STPR_type* ptrSTPR, uint8 Copy_stpVel);

/*
 * Edits the acceleration for the stepper
 */
void STPR_voidSetStprAcc (STPR_type* ptrSTPR, uint8 Copy_stprAcc);

#endif  /*STPR_INT_H*/