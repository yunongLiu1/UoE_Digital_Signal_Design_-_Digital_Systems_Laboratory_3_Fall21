/*
*
* File Name: gpio_init.c
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

#include "platform.h"		//Added for init_platform();
#include "xil_types.h"		// Added for integer type definitions
#include "gpio_init.h" 		// Added for XGpio type definitions
#include "traffic_lights.h" //Added for init_traffic_colour,
							//and structures: trafficStates,road, pedestrianLight
#include "display_control.h" 	//Added for roads_loop() and pd_cross() and definition of variables:
								//pd_counter, ped_btn, num_of_roads, len_of_states_array
#include "timer_interrupt_func.h" //Added for definiton of variable  timer_served and interruptCounter;

int main() {

	init_platform();
	// Initialize the GPIOs
	int status;
	status = initGpio();
	if (status != XST_SUCCESS) {
		print("GPIOs initialization failed!\n\r");
		cleanup_platform();
		return 0;
	}
	// Setup the Interrupt System
	status = setUpInterruptSystem();
	if (status != XST_SUCCESS) {
		print("Interrupt system setup failed!\n\r");
		cleanup_platform();
		return 0;
	}

	/*****Following variables are defined in display_control.h*******/
	ped_btn = FALSE;//Boolean of whether the pedestrian button has been pressed
	pd_counter = 5; // Seconds for each traffic loopthe counter of pedestrian light remain seconds
	len_of_states_array = 4; //Initialise the length of state sequence.The variable is defined in display_control.h 
	num_of_roads = 3;//Initialise the number of roads.The variable is defined in display_control.h 

	/*****Following variables are defined in timer_interrupt_func.h*******/
	interruptCounter = 0; //Initialize system counter, will be increased at each interrupt
	timer_served = FALSE; //contain information of timer served or not

	/*****Initialize roads, pedestrian light and state array*******/
	struct road roads[num_of_roads]; //The array used to store roads with structure road, which defined in traffic_lights.h
	struct pedestrianLight ped_light;//The variable used to store pedestrian light with structure pedestrianLight, which defined in traffic_lights.h
	/*Light states sequence Red -> Red Yellow -> Green -> Yellow */
	struct trafficStates lights_operation[] = {R, RY, G, Y};//The variable used to initialize state sequence, the structure defined in traffic_lights.h
	u8 rd_num = 0; //Current number of road, will be increased after the states loop finished

	/*****Initialise vga seting and display*******/
	init_roads(roads, lights_operation, &ped_light); //Define in traffic_lights.c
	init_traffic_colour(roads , num_of_roads, &ped_light); //Define in traffic_lights.c
	while (1) {
		/*Display Traffic Lights*/
		roads_loop(roads, rd_num, &ped_light); // Display the lights state sequence for current road
		rd_num = (rd_num + 1) % num_of_roads ; // Switch among 3 roads  0->1->2->0...
		init_traffic_colour(roads, num_of_roads , &ped_light); //Define in traffic_lights.c

		//Allow pedestrian to cross if the pedestrian button is pressed
		if (ped_btn) {
			//Define in display_control.c, which contains display of vga, led and seg-7
			pd_cross(&ped_light);
		}//else move to the next road
	}

	cleanup_platform(); 
	return 0;
}









