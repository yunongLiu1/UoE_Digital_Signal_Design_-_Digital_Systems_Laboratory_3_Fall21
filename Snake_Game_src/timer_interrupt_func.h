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

#ifndef TIMER_INTERRUPT_FUNC_H_
#define TIMER_INTERRUPT_FUNC_H_

/******************* Definition of constants ******************************/
#define INTERRUPT_SYSTEM_TIME 	0.004//Interrupt System Clock, defined in hardware
#define REQUIRED_TIME			0.1 //Used to control frequency of timer

/******************* Variables used to control the interrupt system ******************************/
u8 timer_served; //Contain information of timer served or not
u8 interruptCounter;//System counter, will be increased at each interrupt

/************************** Function Prototypes ******************************/
int setUpInterruptSystem();
void hwTimerISR(void *CallbackRef);
void timer(); //Function defined in timer_interrupt_func.c which used to count real life time using counter.

#endif /* TIMER_INTERRUPT_FUNC_H_ */
