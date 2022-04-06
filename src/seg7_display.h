/*
*
* File Name: seg7_displayh
* Project Name: Traffic Light
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7 FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yunong Liu
* Company: University of Edinburgh
* Creation Date and Time: 20/11/2021; 07:23
* Description: This header file contains definitions used to drive the 7 segment display. 
* and declare function prototypes used in seg7_display.c. It contains three main part definitions
* one is for seg7 display which contains 8bits constants corresponding digit to 8bits segment code.
* the second part is the constant defined for display dashing and blank, will be used in switch-case 
* loop to determine when should display dash and blank. The thrid part of definition is for digit selection
* on the FPGA board corresponding to the four digit on the board.
*/
#ifndef __SEG7_DISPLAY_H_
#define __SEG7_DISPLAY_H_

#include "xgpio.h"		// Added for xgpio object definitions

/********** Definitions for 7-segment BCD codes ************/
#define DIGIT_BLANK		0xFF
#define DIGIT_ZERO 		0xC0
#define DIGIT_ONE  		0xF9
#define DIGIT_TWO  		0xA4
#define DIGIT_THREE  	0xB0
#define DIGIT_FOUR  	0x99
#define DIGIT_FIVE  	0x92
#define DIGIT_SIX  		0x82
#define DIGIT_SEVEN  	0xF8
#define DIGIT_EIGHT  	0x80
#define DIGIT_NINE  	0x90
#define DIGIT_DASH  	0xBF
#define CHAR_P  		0x8C

#define NUMBER_BLANK  	10 	// Note: since 10 cannot be a digit,
 						   	//       it is used to represent a blank digit
#define NUMBER_DASH  	11 	// Note: since 11 cannot be a digit,
 						   	//       it is used to represent "dash"

/*********** Definitions for digit selection codes ************/
#define EN_FIRST_SEG	0b0111
#define EN_SECOND_SEG	0b1011
#define EN_THIRD_SEG	0b1101
#define EN_FOURTH_SEG	0b1110

/************************** Function Prototypes ******************************/
void displayRoadNumberAndTimer(u8 roadNum, u16 number, u8 PointBool);
void displayDigit();

#endif
