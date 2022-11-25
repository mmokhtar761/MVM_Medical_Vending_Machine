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
volatile uint8 * GetPortAdd(PORTS u8PortIdCopy)
{
	if(u8PortIdCopy > PORT_E) return NULL;
	switch (u8PortIdCopy)
    {
        case PORT_A:  return & PORTA; break;
        case PORT_B:  return & PORTB; break;
        case PORT_C:  return & PORTC; break;
        case PORT_D:  return & PORTD; break;
        case PORT_E:  return & PORTE; break;
    } 
}

void DIO_VidSetPinDirection (PORTS u8PortIdCopy, PINS u8PinIdCopy, uint8 u8PinDirCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_E) && (u8PinIdCopy <= PIN7))
	{
		/* Check on the Required TRIS Number */
		switch (u8PortIdCopy)
		{
			case PORT_A: MAN_BIT(TRISA,u8PinIdCopy,u8PinDirCopy); break;
			case PORT_B: MAN_BIT(TRISB,u8PinIdCopy,u8PinDirCopy); break;
			case PORT_C: MAN_BIT(TRISC,u8PinIdCopy,u8PinDirCopy); break;
			case PORT_D: MAN_BIT(TRISD,u8PinIdCopy,u8PinDirCopy); break;
			case PORT_E: MAN_BIT(TRISE,u8PinIdCopy,u8PinDirCopy); break;
		}
	}

	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

void DIO_VidSetPinValue(PORTS u8PortIdCopy , PINS u8PinIdCopy, uint8 u8PinValCopy)
{
	/* Check the pin value passed is ok*/
	if (u8PinValCopy > 1) return;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_E) && (u8PinIdCopy <= PIN7))
	{
		/* Check on the Required PORT Number */
		MAN_BIT((*GetPortAdd(u8PortIdCopy)),u8PinIdCopy,u8PinValCopy); 
	}
	else
	{
		/* Do nothing, Error in the Pin ID or PORT ID */
	}
}

uint8 DIO_u8GetPinValue(PORTS u8PortIdCopy, PINS u8PinIdCopy)
{
	/* Define Local Variable to get the BIT Value */
	uint8 u8ResultLocal;

	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_E) && (u8PinIdCopy <= PIN7))
	if ((u8PortIdCopy <= PORT_E) && (u8PinIdCopy <= PIN7))
	{
		/* Check on the Required PORT Number */
		u8ResultLocal= GET_BIT((*GetPortAdd(u8PortIdCopy)),u8PinIdCopy);
	}
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		u8ResultLocal = 0xFF; /* 255 */
	}
	return u8ResultLocal;
}

/* Port Related Function Definition*/
void DIO_VidSetPortDirection (PORTS u8PortId, uint8 u8PortDir)
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

void DIO_VidSetPortValue (PORTS u8PortId, uint8 u8PortVal)
{
	/* Check on the Required PORT Number */
	*GetPortAdd(u8PortId) = u8PortVal;
}


void DIO_Inti(void){
    /*Init the ports values*/
    PORTA = INIT_PORTA_VAL;
    PORTB = INIT_PORTB_VAL;
    PORTC = INIT_PORTC_VAL;
    PORTD = INIT_PORTD_VAL;
    PORTE = INIT_PORTE_VAL;
     
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




void DIO_VidSetHalfPortDirection(PORTS u8PortId, uint8 u8PortHalf ,uint8 u8PortDir){ 
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


void DIO_VidSetHalfPortSet(PORTS u8PortId, uint8 u8PortHalf ,uint8 u8PortVal){ 
        for (uint8 u8PinIdCopy= 4*(u8PortHalf-1) ; u8PinIdCopy<= 4*(u8PortHalf-1)+3  ;u8PinIdCopy++){
			switch (u8PortId)
			{
				case PORT_A: if      (u8PortVal == Pin_LOW) {BIT_L(PORTA,u8PinIdCopy); break;}
                             else if (u8PortVal == Pin_HIGH){BIT_H(PORTA,u8PinIdCopy); break;}else{}
				case PORT_B: if      (u8PortVal == Pin_LOW) {BIT_L(PORTB,u8PinIdCopy); break;}
                             else if (u8PortVal == Pin_HIGH){BIT_H(PORTB,u8PinIdCopy); break;}else{}
				case PORT_C: if      (u8PortVal == Pin_LOW) {BIT_L(PORTC,u8PinIdCopy); break;}
                             else if (u8PortVal == Pin_HIGH){BIT_H(PORTC,u8PinIdCopy); break;}else{}
				case PORT_D: if      (u8PortVal == Pin_LOW) {BIT_L(PORTD,u8PinIdCopy); break;}
                             else if (u8PortVal == Pin_HIGH){BIT_H(PORTD,u8PinIdCopy); break;}else{}
                case PORT_E: if(u8PinIdCopy<=PORT_E_LAST_PIN){
                             if      (u8PortVal == Pin_LOW) {BIT_L(PORTE,u8PinIdCopy); break;}
                             else if (u8PortVal == Pin_HIGH){BIT_H(PORTE,u8PinIdCopy); break;}else{}}
			} 
        }   
} 


void DIO_VidDirPortNibble(PORTS u8PortId, PINS u8StPin ,uint8 u8PortDir){
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



uint8 DIO_u8GetPortNibble(PORTS u8PortIdCopy , PINS u8StPin )
{
	/* Define Local Variable to get the BITS Value */
	uint8 u8ResultLocal=0;

	/* Make sure that the Port ID is in the valid range */
	if ((u8PortIdCopy <= PORT_E))
	{
		/* Check on the Required PORT Number */
		u8ResultLocal= GET_NIBBLE((*GetPortAdd(u8PortIdCopy)),u8StPin); 
	}
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		u8ResultLocal = 0xFF; /* 255 */
	}
	return u8ResultLocal;
}




uint8 DIO_u8GetPortValue(PORTS u8PortIdCopy)
{
	/* Define Local Variable to get the BYTE Value */
	uint8 u8ResultLocal=0;

	/* Make sure that the Port ID is in the valid range */
	if ((u8PortIdCopy <= PORT_E))
	{
		/* Check on the Required PORT Number */
		switch (u8PortIdCopy)
		{
			case PORT_A: u8ResultLocal= GET_BYTE(PORTA,PIN0); break;
			case PORT_B: u8ResultLocal= GET_BYTE(PORTB,PIN0); break;
			case PORT_C: u8ResultLocal= GET_BYTE(PORTC,PIN0); break;
			case PORT_D: u8ResultLocal= GET_BYTE(PORTD,PIN0); break;
            case PORT_E: u8ResultLocal= GET_BYTE(PORTE,PIN0); break;
		}
	}
	else
	{
		/* return 0xff in case of error in the Pin ID or PORT ID */
		u8ResultLocal = 0xFF; /* 255 */
	}
	return u8ResultLocal;
}



void DIO_VidSetPortNibble(PORTS u8PortId, PINS u8StPin ,uint8 u8PortVal){
    if(u8StPin > PIN4)return;
    MAN_NIBBLE((*GetPortAdd(u8PortId)),u8StPin,u8PortVal);
}