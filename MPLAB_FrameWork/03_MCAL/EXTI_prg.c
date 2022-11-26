/*
 * EXTI_prg.c
 *
 *  Created on: Aug 17, 2021
 *      Author: Omar Nasr
 */

#include <xc.h>

#include "Std_Types.h"
#include "MANIPULATOR.h"

#include "DIO_int.h"
#include "DIO_cfg.h"


#include "EXTI_int.h"
#include "EXTI_config.h"
#include "EXTI_priv.h"


 void GIE_Enable(void){
	BIT_H(INTCON,7);
}
void GIE_Disable(void){
	BIT_L(INTCON,7);
}


void EXIT_Int(void){ 
   // Interrupt Priority Enable
   BIT_H(RCON,7);
   // Enables  all low-priority peripheral interrupts
   BIT_H(INTCON,6);
   
	//EXIT 0
#if   ISC0== Falling
	BIT_L(INTCON2,6);

#elif ISC0==Rising
	BIT_H(INTCON2,6);
#endif
    
    	//EXIT 1
#if   ISC1== Falling
	BIT_L(INTCON2,5);

#elif ISC1==Rising
	BIT_H(INTCON2,5);
#endif
    
    
    	//EXIT 2
#if   ISC2== Falling
	BIT_L(INTCON2,4);

#elif ISC2==Rising
	BIT_H(INTCON2,4);
#endif
}


void EXIT0_Enable(void) {//External Interrupt 0 Enable
                         BIT_H(INTCON,4);
                         //Clear external Interrupt 0 flag
                         BIT_L(INTCON,1);
                         }

void EXIT0_Disable(void){BIT_L(INTCON,4);}

void EXIT1_Enable(void) {//External Interrupt 1 Enable
                         BIT_H(INTCON3,3);
                         //Clear external Interrupt 1 flag
                         BIT_L(INTCON3,0);
                         //Make the external interrupt 1 high priority
                         BIT_H(INTCON3,6);
                        }
void EXIT1_Disable(void){BIT_L(INTCON3,3);}

void EXIT2_Enable(void) {//External Interrupt 2 Enable
                         BIT_H(INTCON3,4);
                         //Clear external Interrupt 2 flag
                         BIT_L(INTCON3,1);
                         //Make the external interrupt 2 high priority
                         BIT_H(INTCON3,7);}

void EXIT2_Disable(void){BIT_L(INTCON3,4);}

/*
__interrupt(high_priority) void ISR1(void)      //High priority interrupt ISR
{

   
   
}
*/