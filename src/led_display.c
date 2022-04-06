/*
*
* File Name: led_display.c
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

#include "led_display.h" //Added for definitions of variable and constants, and function prototypes.
#include "vga_display.h"	//Added for definiton of the character of colours and corresponding colour codes, 


void display_leds(u8 ped_btn, struct road* roads, u8 numOfRoads,struct pedestrianLight* ped_light){
	u16 led_out = 0;
	u8 i = 0;
	for ( i= 0; i < numOfRoads ; i++){
		led_out = led_out | led_states(roads[i]);
	}
	if (ped_btn) {
		led_out = led_out | ped_light->light_led_address;
	}

	XGpio_DiscreteWrite(&LEDS_OUT, 1, led_out);

}

u16 led_states(struct road rd) {
	u16 states = 0;
	if (rd.states_sequence[rd.curr_state_index].yellow_light_state == YELLOW) { //If the yellow light is active
		states = states | rd.yellow_light_led_address;
	}
	if (rd.states_sequence[rd.curr_state_index].red_light_state == RED) { //If the red light is active
		states = states | rd.red_light_led_address;
	}
	if (rd.states_sequence[rd.curr_state_index].green_light_state == GREEN) { //If the green light is active
		states = states | rd.green_light_led_address;
	}
	return states;
}
