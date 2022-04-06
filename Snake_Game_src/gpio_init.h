/*
*
* File Name: gpio_init.h
* Project Name: Traffic Light
* Target Device/Platform: Basys3 Board (with Microblaze processor on the Artix-7 FPGA)
* Tool Version: Xilinx SDK 2015.2
* Name: Yunong Liu
* Company: University of Edinburgh
* Creation Date and Time: 20/11/2021; 07:23
* Description: This header file is used to defined XGpio objects. 
*/
#ifndef __GPIO_INIT_H_
#define __GPIO_INIT_H_

#include "xgpio.h"	// Added for xgpio object definitions

/*************LEDs and Swiches on FPGA board******************/
XGpio SLIDE_SWICHES;//input, connect with slides on the board, 16bits.
XGpio LEDS_OUT;//output, connect to leds on the board, 16bits.

/*************VGA Display Regions******************/
/*******VGA REGIONS DEFINED IN HARDWARE*****/
XGpio REGION_0_COLOUR; 
XGpio REGION_1_COLOUR;
XGpio REGION_2_COLOUR;
XGpio REGION_3_COLOUR;
XGpio REGION_4_COLOUR;
XGpio REGION_5_COLOUR;
XGpio REGION_6_COLOUR;
XGpio REGION_7_COLOUR;
XGpio REGION_8_COLOUR;
XGpio REGION_9_COLOUR;
XGpio REGION_10_COLOUR;
XGpio REGION_11_COLOUR;
/*******VGA DISPLAY COORDINATES*****/
XGpio VGA_HS; //Horizental Coordinate on vga display
XGpio VGA_VS; //Vertical Coordinate on vga display

/*************The Four Buttons On BOARD******************/
XGpio P_BTN_L;//Left button on the FPGA board.
XGpio P_BTN_R;//Right button on the FPGA board.
XGpio P_BTN_U;//Up button on the FPGA board.
XGpio P_BTN_D;//Down button on the FPGA board.

/*************SEG 7 Display Interface******************/
XGpio SEG7_HEX_OUT;//7 segment output, should be a 8bits signal.
XGpio SEG7_SEL_OUT;//output for 7 segment display selection.

/************************** Function Prototypes ******************************/
XStatus initGpio(void); //Function used to connect all the defined XGpios with board.
#endif
