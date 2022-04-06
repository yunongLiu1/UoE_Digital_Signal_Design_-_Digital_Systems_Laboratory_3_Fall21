/*
* File Name: vga_display.h
* Project Name: Traffic Light
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7 FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yunong Liu
* Company: University of Edinburgh
* Creation Date and Time: 24/11/2021; 09:37
* Description: This source file contains functions used to drive the 7 segment display. 
* Therearethreefunctionsinthisfile. ThedisplayNumber()functionreceivesan unsigned16-bitinteger. 
* Itisusedtoassignthedigitnumberandthevaluetobedisplayed perdigitwhenthetimerinterruptoccurs. 
* ThecalculateDigits()functionisusedtoextract the digits (of which a maximum of four can be displayed) 
* from the number to be displayed. The hwTimerISR() (which is defined in the xinterruptES3.c file) method 
* is used to call the displayDigit() method, which selects the segments and displays the digits on the 
* 7-segment display. All these functions are declared in the seg7_display.h header file.
*/
#include "vga_display.h" //Added for definitions of variable and constants(colours), and function prototypes.

/*
 * This function correspond number to regions
 * on VGA
 * All the constants correspond to XGpio objects are
 * defined in gpio_init.h header file
 * */
XGpio region_select(u8 region_selector){
	//correspond number 0 to 11 to the 12 regions on screen
	switch(region_selector){
		case 0:
			return REGION_0_COLOUR;
			break;
		case 1:
			return REGION_1_COLOUR;
			break;
		case 2:
			return  REGION_2_COLOUR;
			break;
		case 3:
			return REGION_3_COLOUR;
			break;
		case 4:
			return REGION_4_COLOUR;
			break;
		case 5:
			return REGION_5_COLOUR;
			break;
		case 6:
			return REGION_6_COLOUR;
			break;
		case 7:
			return  REGION_7_COLOUR;
			break;
		case 8:
			return REGION_8_COLOUR;
			break;
		case 9:
			return REGION_9_COLOUR;
			break;
		case 10:
			return REGION_10_COLOUR;
			break;
		case 11:
			return REGION_11_COLOUR;
			break;
		default:
			//If the number is not within 0-11, return region 0 by default
			return REGION_0_COLOUR;
			break;
	}
}

/*
 * This function correspond colour character to 12 bits colour code
 * All the constants related to colour characters and colour code
 * are defined in vga_display.h header file
 * */

u16 colour_select(char colour_char){
	u16 colour_out = 0;
	switch(colour_char){
		case  RED:		//character Red
			colour_out = VGA_COLOUR_RED; //set colour code to output
			break;
		case  YELLOW: 	//character Yellow
			colour_out = VGA_COLOUR_YELLOW; //set colour code to output
			break;
		case  GREEN:	//character Green
			colour_out = VGA_COLOUR_GREEN; //set colour code to output
			break;
		case  WHITE:	//character White
			colour_out = VGA_COLOUR_WHITE; //set colour code to output
			break;
		default:
			//If the character is not defined, return white by default
			colour_out = VGA_COLOUR_WHITE;
			break;
	}
	// return colour code which can be received by XGpio_DiscreteWrite() directly
	return colour_out;
}

/*
* This function will change the colour of input
* if input green, then return white
* otherwise return green
*/
void blinkingGreenLight(char* curr_colour){
	switch (*curr_colour) {
		case WHITE:
			*curr_colour = GREEN;
			break;
		case GREEN:
			*curr_colour = WHITE;
			break;
		}
}
