/*
 * File:   DIO_prog.c
 * Author: omarnasr
 *
 * Created on October 22, 2022, 12:58 PM
 */


#include <xc.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_int.h"


/*
 * Function Definitions
 */
/* Pin Related Function Definition*/
void DIO_VidSetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_D) && (u8PinIdCopy <= PIN7))
	{
		if ( u8PinDirCopy == OUTPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: SET_BIT(TRISA,u8PinIdCopy); break;
				case PORT_B: SET_BIT(TRISB,u8PinIdCopy); break;
				case PORT_C: SET_BIT(TRISC,u8PinIdCopy); break;
				case PORT_D: SET_BIT(TRISD,u8PinIdCopy); break;
			}
		}
		else if ( u8PinDirCopy == INPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: CLR_BIT(TRISA,u8PinIdCopy); break;
				case PORT_B: CLR_BIT(TRISB,u8PinIdCopy); break;
				case PORT_C: CLR_BIT(TRISC,u8PinIdCopy); break;
				case PORT_D: CLR_BIT(TRISD,u8PinIdCopy); break;
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

void DIO_VidSetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy)
{
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_D) && (u8PinIdCopy <= PIN7))
	{
		if (u8PinValCopy == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: SET_BIT(PORTA,u8PinIdCopy); break;
				case PORT_B: SET_BIT(PORTB,u8PinIdCopy); break;
				case PORT_C: SET_BIT(PORTC,u8PinIdCopy); break;
				case PORT_D: SET_BIT(PORTD,u8PinIdCopy); break;
			}
		}
		else if (u8PinValCopy == LOW)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
				case PORT_A: CLR_BIT(PORTA,u8PinIdCopy); break;
				case PORT_B: CLR_BIT(PORTB,u8PinIdCopy); break;
				case PORT_C: CLR_BIT(PORTC,u8PinIdCopy); break;
				case PORT_D: CLR_BIT(PORTD,u8PinIdCopy); break;
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

u8 DIO_u8GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy)
{
	/* Define Local Variable to get the BIT Value */
	u8 u8ResultLocal;

	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORT_D) && (u8PinIdCopy <= PIN7))
	{
		/* Check on the Required PORT Number */
		switch (u8PortIdCopy)
		{
			case PORT_A: u8ResultLocal= GET_BIT(PORTA,u8PinIdCopy); break;
			case PORT_B: u8ResultLocal= GET_BIT(PORTB,u8PinIdCopy); break;
			case PORT_C: u8ResultLocal= GET_BIT(PORTC,u8PinIdCopy); break;
			case PORT_D: u8ResultLocal= GET_BIT(PORTD,u8PinIdCopy); break;
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
void DIO_VidSetPortDirection (u8 u8PortId, u8 u8PortDir)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
		case     PORT_A: TRISA = u8PortDir; break;
		case     PORT_B: TRISB = u8PortDir; break;
		case     PORT_C: TRISC = u8PortDir; break;
		case     PORT_D: TRISD = u8PortDir; break;
		default: /* Wrong Port ID */       break;
	}
}

void DIO_VidSetPortValue (u8 u8PortId, u8 u8PortVal)
{
	/* Check on the Required PORT Number */
	switch (u8PortId)
	{
		case     PORT_A: PORTA = u8PortVal; break;
		case     PORT_B: PORTB = u8PortVal; break;
		case     PORT_C: PORTC = u8PortVal; break;
		case     PORT_D: PORTD = u8PortVal; break;
		default: /* Wrong Port ID */        break;
	}
}