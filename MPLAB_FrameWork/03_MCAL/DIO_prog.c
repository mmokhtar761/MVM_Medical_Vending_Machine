/*
 * File:   DIO_prog.c
 * Author: omarnasr
 *
 * Created on October 22, 2022, 12:58 PM
 */



#include <xc.h>


#include "Platform_Types.h"
#include "MANIPULATOR.h"

#include "DIO_int.h"
#include "DIO_cfg.h"


/*
 * Function Definitions
 */
/* Pin Related Function Definition*/
void DIO_VidSetPinDirection (uint8 u8PortIdCopy, uint8 u8PinIdCopy, uint8 u8PinDirCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_E) && (u8PinIdCopy <= PIN7))
	{
		if ( u8PinDirCopy == INPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: BIT_H(TRISA,u8PinIdCopy); break;
				case PORT_B: BIT_H(TRISB,u8PinIdCopy); break;
				case PORT_C: BIT_H(TRISC,u8PinIdCopy); break;
				case PORT_D: BIT_H(TRISD,u8PinIdCopy); break;
                case PORT_E: BIT_H(TRISE,u8PinIdCopy); break;
			}
		}
		else if ( u8PinDirCopy == OUTPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: BIT_L(TRISA,u8PinIdCopy); break;
				case PORT_B: BIT_L(TRISB,u8PinIdCopy); break;
				case PORT_C: BIT_L(TRISC,u8PinIdCopy); break;
				case PORT_D: BIT_L(TRISD,u8PinIdCopy); break;
                case PORT_E: BIT_L(TRISE,u8PinIdCopy); break;
			}
		}

		else
		{
			/* Do nothing, Wrong Direction Required */
		}
	}

	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

void DIO_VidSetPinValue(uint8 u8PortIdCopy , uint8 u8PinIdCopy, uint8 u8PinValCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_E) && (u8PinIdCopy <= PIN7))
	{
		if (u8PinValCopy == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: BIT_H(PORTA,u8PinIdCopy); break;
				case PORT_B: BIT_H(PORTB,u8PinIdCopy); break;
				case PORT_C: BIT_H(PORTC,u8PinIdCopy); break;
				case PORT_D: BIT_H(PORTD,u8PinIdCopy); break;
                case PORT_E: BIT_H(PORTE,u8PinIdCopy); break;
			}
		}
		else if (u8PinValCopy == LOW)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: BIT_L(PORTA,u8PinIdCopy); break;
				case PORT_B: BIT_L(PORTB,u8PinIdCopy); break;
				case PORT_C: BIT_L(PORTC,u8PinIdCopy); break;
				case PORT_D: BIT_L(PORTD,u8PinIdCopy); break;
                case PORT_E: BIT_L(PORTE,u8PinIdCopy); break;
                 
			}
		}
		else
		{
			/* Do nothing, Wrong value to set */
		}
	}
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

uint8 DIO_u8GetPinValue(uint8 u8PortIdCopy, uint8 u8PinIdCopy)
{
	/* Define Local Variable to get the BIT Value */
	uint8 u8ResultLocal;

	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_E) && (u8PinIdCopy <= PIN7))
	{
		/* Check on the Required PORT Number */
		switch (u8PortIdCopy)
		{
			case PORT_A: u8ResultLocal= GET_BIT(PORTA,u8PinIdCopy); break;
			case PORT_B: u8ResultLocal= GET_BIT(PORTB,u8PinIdCopy); break;
			case PORT_C: u8ResultLocal= GET_BIT(PORTC,u8PinIdCopy); break;
			case PORT_D: u8ResultLocal= GET_BIT(PORTD,u8PinIdCopy); break;
            case PORT_E: u8ResultLocal= GET_BIT(PORTE,u8PinIdCopy); break;
		}
	}
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		u8ResultLocal = 0xFF; /* 255 */
	}
	return u8ResultLocal;
}

/* Port Related Function Definition*/
void DIO_VidSetPortDirection (uint8 u8PortId, uint8 u8PortDir)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
		case     PORT_A: TRISA = u8PortDir; break;
		case     PORT_B: TRISB = u8PortDir; break;
		case     PORT_C: TRISC = u8PortDir; break;
		case     PORT_D: TRISD = u8PortDir; break;
        case     PORT_E: TRISE = u8PortDir; break;
		default: /* Wrong Port ID */       break;
	}
}

void DIO_VidSetPortValue (uint8 u8PortId, uint8 u8PortVal)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
		case     PORT_A: PORTA = u8PortVal; break;
		case     PORT_B: PORTB = u8PortVal; break;
		case     PORT_C: PORTC = u8PortVal; break;
		case     PORT_D: PORTD = u8PortVal; break;
        case     PORT_E: PORTE = u8PortVal; break;
		default: /* Wrong Port ID */        break;
	}
}


void DIO_Inti(void){
    for (uint8 u8PortIdCopy=PORT_A;u8PortIdCopy<=PORT_E;u8PortIdCopy++){
        for (uint8 u8PinIdCopy=PIN0;u8PinIdCopy<=PIN7;u8PinIdCopy++){
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: if      (PORT_A_DEF[u8PinIdCopy] == OUTPUT){BIT_L(TRISA,u8PinIdCopy); break;}
                             else if (PORT_A_DEF[u8PinIdCopy] == INPUT) {BIT_H(TRISA,u8PinIdCopy); break;}else{}
				case PORT_B: if      (PORT_B_DEF[u8PinIdCopy] == OUTPUT){BIT_L(TRISB,u8PinIdCopy); break;}
                             else if (PORT_B_DEF[u8PinIdCopy] == INPUT) {BIT_H(TRISB,u8PinIdCopy); break;}else{}
				case PORT_C: if      (PORT_C_DEF[u8PinIdCopy] == OUTPUT){BIT_L(TRISC,u8PinIdCopy); break;}
                             else if (PORT_C_DEF[u8PinIdCopy] == INPUT) {BIT_H(TRISC,u8PinIdCopy); break;}else{}
				case PORT_D: if      (PORT_D_DEF[u8PinIdCopy] == OUTPUT){BIT_L(TRISD,u8PinIdCopy); break;}
                             else if (PORT_D_DEF[u8PinIdCopy] == INPUT) {BIT_H(TRISD,u8PinIdCopy); break;}else{}
                case PORT_E: if(u8PinIdCopy<=PORT_E_LAST_PIN){
                             if      (PORT_E_DEF[u8PinIdCopy] == OUTPUT){BIT_L(TRISE,u8PinIdCopy); break;}
                             else if (PORT_E_DEF[u8PinIdCopy] == INPUT) {BIT_H(TRISE,u8PinIdCopy); break;}else{}}
			} 
        }   
    }
} 




void DIO_VidSetHalfPortDirection(uint8 u8PortId, uint8 u8PortHalf ,uint8 u8PortDir){ 
        for (uint8 u8PinIdCopy= 4*(u8PortHalf-1) ; u8PinIdCopy<= 4*(u8PortHalf-1)+3  ;u8PinIdCopy++){
			switch (u8PortId)
			{
				case PORT_A: if      (u8PortDir == OUTPUT){BIT_L(TRISA,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISA,u8PinIdCopy); break;}else{}
				case PORT_B: if      (u8PortDir == OUTPUT){BIT_L(TRISB,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISB,u8PinIdCopy); break;}else{}
				case PORT_C: if      (u8PortDir == OUTPUT){BIT_L(TRISC,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISC,u8PinIdCopy); break;}else{}
				case PORT_D: if      (u8PortDir == OUTPUT){BIT_L(TRISD,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISD,u8PinIdCopy); break;}else{}
                case PORT_E: if(u8PinIdCopy<=PORT_E_LAST_PIN){
                             if      (u8PortDir == OUTPUT){BIT_L(TRISE,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISE,u8PinIdCopy); break;}else{}}
			} 
        }   
} 


void DIO_VidSetHalfPortSet(uint8 u8PortId, uint8 u8PortHalf ,uint8 u8PortVal){ 
        for (uint8 u8PinIdCopy= 4*(u8PortHalf-1) ; u8PinIdCopy<= 4*(u8PortHalf-1)+3  ;u8PinIdCopy++){
			switch (u8PortId)
			{
				case PORT_A: if      (u8PortVal == LOW) {BIT_L(PORTA,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTA,u8PinIdCopy); break;}else{}
				case PORT_B: if      (u8PortVal == LOW) {BIT_L(PORTB,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTB,u8PinIdCopy); break;}else{}
				case PORT_C: if      (u8PortVal == LOW) {BIT_L(PORTC,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTC,u8PinIdCopy); break;}else{}
				case PORT_D: if      (u8PortVal == LOW) {BIT_L(PORTD,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTD,u8PinIdCopy); break;}else{}
                case PORT_E: if(u8PinIdCopy<=PORT_E_LAST_PIN){
                             if      (u8PortVal == LOW) {BIT_L(PORTE,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTE,u8PinIdCopy); break;}else{}}
			} 
        }   
} 

void DIO_VidDirPortNibble(uint8 u8PortId, uint8 u8StPin ,uint8 u8PortDir){
    if(u8StPin <= PIN4){
    for (uint8 u8PinIdCopy= u8StPin ; u8PinIdCopy<= u8StPin+3  ;u8PinIdCopy++){
			switch (u8PortId)
			{
				case PORT_A: if      (u8PortDir == OUTPUT){BIT_L(TRISA,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISA,u8PinIdCopy); break;}else{}
				case PORT_B: if      (u8PortDir == OUTPUT){BIT_L(TRISB,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISB,u8PinIdCopy); break;}else{}
				case PORT_C: if      (u8PortDir == OUTPUT){BIT_L(TRISC,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISC,u8PinIdCopy); break;}else{}
				case PORT_D: if      (u8PortDir == OUTPUT){BIT_L(TRISD,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISD,u8PinIdCopy); break;}else{}
                case PORT_E: if(u8PinIdCopy<=PORT_E_LAST_PIN){
                             if      (u8PortDir == OUTPUT){BIT_L(TRISE,u8PinIdCopy); break;}
                             else if (u8PortDir == INPUT) {BIT_H(TRISE,u8PinIdCopy); break;}else{}}
			} 
        }   
    
    }
}


void DIO_VidSetPortNibble(uint8 u8PortId, uint8 u8StPin ,uint8 u8PortVal){
    if(u8StPin <= PIN4){
     for (uint8 u8PinIdCopy= u8StPin ; u8PinIdCopy<= u8StPin+3  ;u8PinIdCopy++){
			switch (u8PortId)
			{
				case PORT_A: if      (u8PortVal == LOW) {BIT_L(PORTA,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTA,u8PinIdCopy); break;}else{}
				case PORT_B: if      (u8PortVal == LOW) {BIT_L(PORTB,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTB,u8PinIdCopy); break;}else{}
				case PORT_C: if      (u8PortVal == LOW) {BIT_L(PORTC,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTC,u8PinIdCopy); break;}else{}
				case PORT_D: if      (u8PortVal == LOW) {BIT_L(PORTD,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTD,u8PinIdCopy); break;}else{}
                case PORT_E: if(u8PinIdCopy<=PORT_E_LAST_PIN){
                             if      (u8PortVal == LOW) {BIT_L(PORTE,u8PinIdCopy); break;}
                             else if (u8PortVal == HIGH){BIT_H(PORTE,u8PinIdCopy); break;}else{}}
			} 
        }    
    }
}