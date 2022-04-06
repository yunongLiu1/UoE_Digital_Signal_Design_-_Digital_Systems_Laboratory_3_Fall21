/*
*
* File Name: traffic_light.c
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

#include "traffic_lights.h" //Added for definitions of variable and constants, and function prototypes.
#include "vga_display.h"	//Added for /region_select, colour_select, blinkingGreenLight	

#include "timer_interrupt_func.h"
#include "gpio_init.h" // Added for XGpio type definitions


/*
 * Initialise traffic lights.
 * 1. For every roads in the road array, set the colour of red light to red.
 * 2. Set pedestrian light to red.
 * */
void init_traffic_colour(struct road* rd, s8 numOfRoads,struct pedestrianLight* ped_light){
	int i;
	XGpio region;
	for(i = 0; i <numOfRoads; i++ ){//for all roads in the road array
		region = region_select(rd[i].red_light_address); //Get the VGA region of red light for current road
		XGpio_DiscreteWrite(&region, 1, colour_select( RED)); //Change the red traffic light of this road to red

		region = region_select(rd[i].green_light_address); //Get the VGA region of green light for current road
		XGpio_DiscreteWrite(&region, 1, colour_select(WHITE)); //Change the green traffic light of this road to red

		region = region_select(rd[i].yellow_light_address); //Get the VGA region of yellow light for current road
		XGpio_DiscreteWrite(&region, 1, colour_select(WHITE)); //Change the yellow traffic light of this road to red
	}
	region = region_select(ped_light->light_vga_address);////Get the region number of pedestrian light
	XGpio_DiscreteWrite(&region, 1, colour_select(RED));//Change pedestrian light to red
}

/*
 * Change the traffic lights colour in the road rd
 * to the states store in the states array rd.states_sequence
 * in current index rd.curr_state_index.
 *
 * For example if current state in the array is 'RY', this function
 * will active red and yellow lights and set green light to white.
 * */
void traffic_light_loop(struct road rd){
	XGpio region; //The region number on VGA
	u16 colour; //The colour code

	region = region_select(rd.red_light_address);  //Get the region number of red light of this road
	//Get the colour char of red light, 'r' for red and 'w' for white, and then
	//pass the character to colour_select() function in vga_display.c to get the code of colour
	colour = colour_select(rd.states_sequence[rd.curr_state_index].red_light_state);
	XGpio_DiscreteWrite(&region, 1, colour); //Display current colour on the region

	region = region_select(rd.yellow_light_address); //Get the region number of yellow light of this road
	//Get the colour char of yellow light, 'y' for red and 'w' for white, and then
	//pass the character to colour_select() function in vga_display.c to get the code of colour
	colour = colour_select(rd.states_sequence[rd.curr_state_index].yellow_light_state);
	XGpio_DiscreteWrite(&region, 1, colour);//Display current colour on the region

	region = region_select(rd.green_light_address);//Get the region number of green light of this road
	//Get the colour char of red light, 'g' for green and 'w' for white, and then
	//pass the character to colour_select() function in vga_display.c to get the code of colour
	colour = colour_select(rd.states_sequence[rd.curr_state_index].green_light_state);
	XGpio_DiscreteWrite(&region, 1, colour);//Display current colour on the region
}

/*
 * This function is used to initialise the road array and pedestrian light.
 * In this assessment, there will be three roads.
 * Each road display it's lights on the VGA region defined in
 * the traffic_light.h file
 * The locations of pedestrian light are also defined in the header file.
 * */
void init_roads(struct road* roads, struct trafficStates* lights_operation, struct pedestrianLight* ped_light){
	//All the constants below are defined in the traffic_light.h header file

	//Initialise the first road with: 1. the display address of traffic lights on led and vga,
	// 2. the operation array of traffic lights
	// 3. Set current index to 0
	roads[0].red_light_address = ROAD_1_RED_LOCATION;
	roads[0].yellow_light_address = ROAD_1_YELLOW_LOCATION;
	roads[0].green_light_address = ROAD_1_GREEN_LOCATION;;
	roads[0].red_light_led_address = ROAD_1_RED_LED_LOCATION;
	roads[0].yellow_light_led_address = ROAD_1_YELLOW_LED_LOCATION;
	roads[0].green_light_led_address = ROAD_1_GREEN_LED_LOCATION;;
	roads[0].states_sequence = &lights_operation[0];
	roads[0].curr_state_index = 0;

	//Initialise the second road with: 1. the display address of traffic lights on led and vga,
	// 2. the operation array of traffic lights
	// 3. Set current index to 0
	roads[1].red_light_address = ROAD_2_RED_LOCATION;
	roads[1].yellow_light_address = ROAD_2_YELLOW_LOCATION;
	roads[1].green_light_address =  ROAD_2_GREEN_LOCATION;
	roads[1].red_light_led_address = ROAD_2_RED_LED_LOCATION;
	roads[1].yellow_light_led_address = ROAD_2_YELLOW_LED_LOCATION;
	roads[1].green_light_led_address = ROAD_2_GREEN_LED_LOCATION;;
	roads[1].states_sequence = &lights_operation[0];
	roads[1].curr_state_index = 0;

	//Initialise the third road with: 1. the display address of traffic lights on led and vga,
	// 2. the operation array of traffic lights
	// 3. Set current index to 0
	roads[2].red_light_address = ROAD_3_RED_LOCATION;
	roads[2].yellow_light_address = ROAD_3_YELLOW_LOCATION;
	roads[2].green_light_address = ROAD_3_GREEN_LOCATION;
	roads[2].red_light_led_address = ROAD_3_RED_LED_LOCATION;
	roads[2].yellow_light_led_address = ROAD_3_YELLOW_LED_LOCATION;
	roads[2].green_light_led_address = ROAD_3_GREEN_LED_LOCATION;;
	roads[2].states_sequence = &lights_operation[0];
	roads[2].curr_state_index = 0;

	//Initialise pedestrian light's location on vga and led
	ped_light->light_vga_address = PED_VGA_LOCATION;
	ped_light->light_led_address = PED_LED_LOCATION;
}




