/*
*
* File Name: seg7_displayh
* Project Name: Traffic Light
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7 FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yunong Liu
* Company: University of Edinburgh
* Creation Date and Time: 20/11/2021; 07:23
* Description: This source file contains definitions used to drive the 7 segment display. 
* There are two functions in this file. The displayRoadNumberAndTimer(() function receives an unsigned 
* 16-bit integer, a 8-bit integer for road number which will be displayed on the second digit
* and a boolean which decide whether the decimal point should be displayed. It is used to assign the digit 
* number and the value to be displayed per digit when the timer interrupt occurs.The hwTimerISR() (which 
* is defined in the xinterruptES3.c file) method is used to call the displayDigit() method, which selects 
* the segments and displays the digits on the 7-segment display. All these functions are declared in the 
* seg7_display.h header file.
*/

#include "xil_types.h"		// Added for integer type definitions
#include "seg7_display.h"	//Added for definitions of variable and constants, and function prototypes.
#include "gpio_init.h" 		// Added for XGpio type definitions

u8 digitDisplayed = FALSE;
u8 digitToDisplay;
u8 digitNumber;
u8 decimalPoint = FALSE;

void displayRoadNumberAndTimer(u8 roadNum, u16 number, u8 PointBool)
{
	u8 DisplayInfo[4]; //Used to store information that needed to display
	decimalPoint = PointBool;
	DisplayInfo[0] = roadNum;
	DisplayInfo[1] = NUMBER_DASH;

	/* Note that 99 is the maximum number that can be displayed
	 * Therefore, check if the number is less than or equal to 99
	 * and display the number otherwise, display dashes in all the four segments
	 */
	if (number <= 99)
	{
		DisplayInfo[2] = (number / 10) % 10; //Assign the tens digit in number
		DisplayInfo[3] = number % 10;//Assign the digit in number to the right most location
	}
	else
	{
		// Display dashes for out-of-range numbers
		DisplayInfo[2] = NUMBER_DASH;
		DisplayInfo[3] = NUMBER_DASH;
	}

	u8 count = 1;
	while (count < 5)
	{
		digitToDisplay = DisplayInfo[count-1];
		digitNumber = count;
		count++;
		/* Wait for timer interrupt to occur and ISR to finish
		 * executing digit display instructions
		 */
		while (digitDisplayed == FALSE);
		digitDisplayed = FALSE;
	}
}


void displayDigit()
{
	/*
	 * The timer ISR is used to call this function to display the digits
	 */
	u16 displayCode = 0;
	// Write the appropriate value to the SEG7_HEX_OUT object
	switch (digitToDisplay)
	{
		case NUMBER_BLANK :
			displayCode = DIGIT_BLANK;
			break;
		case 0 :
			displayCode =DIGIT_ZERO;
			break;
		case 1 :
			displayCode =DIGIT_ONE;
			break;
		case 2 :
			displayCode = DIGIT_TWO;
			break;
		case 3 :
			displayCode = DIGIT_THREE;
			break;
		case 4 :
			displayCode = DIGIT_FOUR;
			break;
		case 5 :
			displayCode = DIGIT_FIVE;
			break;
		case 6 :
			displayCode = DIGIT_SIX;
			break;
		case 7 :
			displayCode = DIGIT_SEVEN;
			break;
		case 8 :
			displayCode = DIGIT_EIGHT;
			break;
		case 9 :
			displayCode = DIGIT_NINE;
			break;
		case NUMBER_DASH :
			displayCode = DIGIT_DASH;
			break;
		case 'P' :
		case 'p':
			displayCode = CHAR_P;
			break;
			
	}

	if(decimalPoint && digitNumber ==3){//Turn on the decimal point at location 3
		displayCode = displayCode&0x7F; //logic AND with 01111111 to set decimal point 7 seg to 0

	}
	XGpio_DiscreteWrite(&SEG7_HEX_OUT, 1, displayCode);
	// Select the appropriate digit
	if (digitNumber == 1) {
		XGpio_DiscreteWrite(&SEG7_SEL_OUT, 1, EN_FIRST_SEG);
	}
	else if (digitNumber == 2) {
		XGpio_DiscreteWrite(&SEG7_SEL_OUT, 1, EN_SECOND_SEG);
	}
	else if (digitNumber == 3) {
		XGpio_DiscreteWrite(&SEG7_SEL_OUT, 1, EN_THIRD_SEG);
	}
	else if (digitNumber == 4) {
		XGpio_DiscreteWrite(&SEG7_SEL_OUT, 1, EN_FOURTH_SEG);
	}

	digitDisplayed = TRUE;
	return;
}
