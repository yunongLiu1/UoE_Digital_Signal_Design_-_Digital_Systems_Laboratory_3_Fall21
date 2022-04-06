/*
* File Name: vga_display.h
* Project Name: Traffic Light
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7 FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yunong Liu
* Company: University of Edinburgh
* Creation Date and Time: 20/11/2021; 07:23
* Description: This source file contains functions used to drive the 7 segment display. 
* Therearethreefunctionsinthisfile. ThedisplayNumber()functionreceivesan unsigned16-bitinteger. 
* Itisusedtoassignthedigitnumberandthevaluetobedisplayed perdigitwhenthetimerinterruptoccurs. 
* ThecalculateDigits()functionisusedtoextract the digits (of which a maximum of four can be displayed) 
* from the number to be displayed. The hwTimerISR() (which is defined in the xinterruptES3.c file) method 
* is used to call the displayDigit() method, which selects the segments and displays the digits on the 
* 7-segment display. All these functions are declared in the seg7_display.h header file.
*/

#ifndef VGA_DISPLAY_H_
#define VGA_DISPLAY_H_

/*************************** Include Header Files *************************************/
#include "xil_types.h"		// Added for integer type definitions
#include "gpio_init.h"		// Added for XGpio type definitions

/***************************Definition of the relationship between character and colour******************************/
#define RED 		'r' 
#define YELLOW 		'y'
#define GREEN 		'g'
#define WHITE		'w'

/***************************Definition of the relationship between colour and 12bits colour code********************/
#define VGA_COLOUR_RED 		0xF00
#define VGA_COLOUR_GREEN	0x0F0
#define VGA_COLOUR_YELLOW	0x770
#define VGA_COLOUR_WHITE	0xFFF

/************************************* Function Prototypes ***************************************/
XGpio region_select(u8 region_selector); //Function defined in vga_display.c which take a number (0-11) as input and return the corresponding XGpio object.
u16 colour_select(char colour_char);//Function defined in vga_display.c which take a char as input and return the corresponding 12 bits colour code.
void blinkingGreenLight(char* colour); //Function defined in vga_display.c which used to change colour.

#endif /* VGA_DISPLAY_H_ */
