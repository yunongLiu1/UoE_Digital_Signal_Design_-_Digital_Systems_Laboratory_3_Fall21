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

#include "display_control.h" //Added for definitions of variable and function prototypes
#include "gpio_init.h" // Added for XGpio type definitions
#include "seg7_display.h"	//Added for displayRoadNumberAndTimer() used to display time
#include "vga_display.h"	//Added for definiton of the character of colours and corresponding colour codes, 
							//region_select, colour_select, blinkingGreenLight	

#include "led_display.h"
#include "timer_interrupt_func.h"
/*
 * VGA, 7seg and led display when pedestrian light
 * is active.
 *
 * */
void pd_cross(struct pedestrianLight* ped_light) {
	s8 	ms = pd_counter * 10; // multiply by 10 to get counter in ms
	XGpio region= region_select(ped_light->light_vga_address);//get the vga region of pedestrian light
	char colour = GREEN; //initialise pedestrain colour to green
	// Change VGA display to the pedestrain mode, which display red to all roads and green to pedestrian light
	XGpio_DiscreteWrite(&LEDS_OUT, 1, PED_CROSS_LEDS);
	/* Display counter on the FPGA board in ms, and refresh pedestrian light(served for blinking)*/
	for (ms = pd_counter * 10; ms > 0; ms--) {
		XGpio_DiscreteWrite(&region, 1, colour_select(colour));//refresh pedestrian light(served for blinking)
		while (!timer_served) {
			//Display counter on the FPGA board in ms with decimal point
			displayRoadNumberAndTimer('p', pd_counter * 10 + ms % 10, TRUE);
		}
		timer_served = FALSE;//Reset to count for the next 0.1 second
		//If 1s passed, decrease the counter of pedestrian light remain seconds
		if (ms % 10 == 0) {pd_counter--;}
		//If remain time <= 2 second, blinking
		if (ms % 2 == 0 && ms < 20) {blinkingGreenLight(&colour);}//Implemented in traffic_lights.c
	}
	/*Reset pedestrian light to red and pedestrian button to FALSE*/
	colour = RED;
	XGpio_DiscreteWrite(&region, 1, colour_select(colour));
	ped_btn = FALSE;
}
/*
 * The main loop for vga, 7seg and led display,
 *
 * */
void roads_loop(struct road* roads, u8 rd_num,struct pedestrianLight* ped_light) {
	s8 ms;
	//While not reach the end of light's states sequence for current road roads[rd_num],
	//move to the next light's state
	while (roads[rd_num].curr_state_index < len_of_states_array) {
		//This function is defined in traffic_light.c, which displays current light state
		traffic_light_loop(roads[rd_num]);
		//Decrease the seg-7 display for every 0.1s
		for (ms = 10; ms > 0; ms--) {
			//While not reach 0.1s, keep updating pedestrian button status,
			//displaying led states and display the remain time of this light state
			while (!timer_served) {
				ped_btn = XGpio_DiscreteRead(&P_BTN_U, 1) || ped_btn; //update_ped_btn
				display_leds(ped_btn, roads, num_of_roads,ped_light); // Defined in led_display.c
				displayRoadNumberAndTimer(rd_num + 1, ms, TRUE);//display in ms with decimal point
			}
			timer_served = FALSE;//after reach 0.1s, reset timer_served and move to the next loop
		}
		//after reach 1s, move to the next state for this road
		roads[rd_num].curr_state_index = roads[rd_num].curr_state_index + 1;
	}
	//after reach the end of state sequence for this road, reset state, and end this function.
	roads[rd_num].curr_state_index = 0;
}
