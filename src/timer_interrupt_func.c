/*
*
* File Name: timer_interrupt_func.h
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
#include "seg7_display.h"	//Added for displayDigit() used to display number at interrupt time
#include "timer_interrupt_func.h" //Added for definitions of variable and constants, and function prototypes.


void hwTimerISR(void *CallbackRef) {
	timer();
	displayDigit(); //Defined in seg7-display.c
}

/*
 * This function is used to count time, will be called by hwTimerISR(void *CallbackRef) at each interrupt*/
void timer(){
	interruptCounter++;
	if (interruptCounter == REQUIRED_TIME/INTERRUPT_SYSTEM_TIME) { //0.1s
		interruptCounter = 0; //Reset counter
		timer_served = TRUE; //contain information of timer served or not
	}

}
