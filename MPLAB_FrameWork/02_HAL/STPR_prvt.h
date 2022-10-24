/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STPR_PRVT_H                                           */
/*Describtion    : Stepper control driver private file                   */
/* Date          : Oct 2022                                              */
/* Version       : V00.1                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef STPR_PRVT_H
#define STPR_PRVT_H

#define MICRO_PER_SEC       (uint32)(1000000)

#define MIN_PULSE_WIDTH     (STP_MIN_LOW_PULSE_WIDTH+STP_MIN_HIGH_PULSE_WIDTH) /*In micro seconds*/
#define MAX_STEPS_PER_SEC   (MICRO_PER_SEC/MIN_PULSE_WIDTH)

#endif /* STPR_PRVT_H*/
