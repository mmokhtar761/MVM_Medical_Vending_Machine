/******************************************************************************/
/* Author        : Mohamed Mokhtar                                            */
/* Date          : 30 Sep 2021                                                */
/* Version       : V1.1                                                       */
/******************************************************************************/
#ifndef MANIPULATOR_H
#define MANIPULATOR_H
                      /* dealing with only 1 Bit */
#define MAN_BIT(VAR,BIT,_1BIT_VAL)                VAR=((VAR & ~((uint32)1<<BIT))|((uint32)_1BIT_VAL<<BIT))
#define BIT_H(VAR,BIT)                            VAR|=  ((uint32)1<<BIT)
#define BIT_L(VAR,BIT)                            VAR&= ~((uint32)1<<BIT)
#define GET_BIT(VAR,BIT)                          ((VAR>>BIT)&(uint32)1)
//#define TOG_BIT(VAR,BIT)                          VAR^=  (1<<BIT)
/*Bit banding regions and alies boarders*/
//SRAM
#define SRAM_BIT_BAND_REGION_ST       ((volatile uint32*)0x20000000)
#define SRAM_BIT_BAND_REGION_EN       ((volatile uint32*)0x20007FFF)
#define SRAM_BIT_BAND_ALIAS_ST        ((volatile uint32*)0x22000000)
#define SRAM_BIT_BAND_ALIAS_EN        ((volatile uint32*)0x220FFFFF)
//Peripheral
#define PERI_BIT_BAND_REGION_ST       ((volatile uint32*)0x40000000)
#define PERI_BIT_BAND_REGION_EN       ((volatile uint32*)0x400FFFFF)
#define PERI_BIT_BAND_ALIAS_ST        ((volatile uint32*)0x42000000)
#define PERI_BIT_BAND_ALIAS_EN        ((volatile uint32*)0x43FFFFFF)
/*Bit banding macros*/
#define SRAM_BB_H(VAR,BIT)            *(&VAR - SRAM_BIT_BAND_REGION_ST) * 32 + BIT * 4 + SRAM_BIT_BAND_ALIAS_ST) = 1                                                    
#define SRAM_BB_L(VAR,BIT)            *(&VAR - SRAM_BIT_BAND_REGION_ST) * 32 + BIT * 4 + SRAM_BIT_BAND_ALIAS_ST) = 0                
#define PERI_BB_H(VAR,BIT)            *(&VAR - PERI_BIT_BAND_REGION_ST) * 32 + BIT * 4 + PERI_BIT_BAND_ALIAS_ST) = 1                                    
#define PERI_BB_L(VAR,BIT)            *(&VAR - PERI_BIT_BAND_REGION_ST) * 32 + BIT * 4 + PERI_BIT_BAND_ALIAS_ST) = 0                                    

/*Efficient bit handler*/
/*#define BIT_H_W0TOLERANT(VAR,BIT)                 (VAR=(1<<BIT))*/
/*
The following formula shows how the alias region maps onto the bit-band region:
bit_word_offset = (byte_offset x 32) + (bit_number x 4)
bit_word_addr = bit_band_base + bit_word_offset
where:
bit_word_offset
	The position of the target bit in the bit-band memory region.
bit_word_addr
	The address of the word in the alias memory region that maps to the targeted bit.
bit_band_base
	The starting address of the alias region.
byte_offset
	The number of the byte in the bit-band region that contains the targeted bit.
bit_number
	The bit position, 0-7, of the targeted bit
*/
                     /* dealing with nibble (4 Bit) */
#define MAN_NIBBLE(VAR,START_BIT,_4BIT_VAL)        VAR=((VAR & ~((uint32)0xF<<START_BIT))|(_4BIT_VAL<<START_BIT))
#define SET_NIBBLE(VAR,START_BIT)                  VAR|=  (0xF<<START_BIT)
#define CLR_NIBBLE(VAR,START_BIT)                  VAR&= ~(0xF<<START_BIT)
#define GET_NIBBLE(VAR,START_BIT)                  ((VAR&(0XF<<START_BIT))>>START_BIT)
#define TOG_NIBBLE(VAR,START_BIT)        	         VAR^= (0XF<<START_BIT)

                      /* dealing with byte (8 Bit) */
#define MAN_BYTE(VAR,START_BIT,_8BIT_VAL)         (VAR=((VAR & ~(0xFF<<START_BIT))|(_8BIT_VAL<<START_BIT)))
#define SET_BYTE(VAR,START_BIT)                    MAN_BYTE(VAR,START_BIT,0XFF)
#define CLR_BYTE(VAR,START_BIT)                    MAN_BYTE(VAR,START_BIT,0X00)
#define GET_BYTE(VAR,START_BIT)                    ((VAR&(0XFF<<START_BIT))>>START_BIT)
#define TOG_BYTE(VAR,START_BIT)                    MAN_BIT(VAR,START_BIT,~GET_BYTE(VAR,START_BIT))





#endif  /*MANIPULATOR_H end*/



