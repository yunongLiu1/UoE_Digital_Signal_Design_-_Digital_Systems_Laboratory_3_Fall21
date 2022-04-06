/*
*
* File Name: traffic_light.h
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


#ifndef TRAFFIC_LIGHTS_H_
#define TRAFFIC_LIGHTS_H_

/******************* Include Header Files ******************************/
#include "xil_types.h"		// Added for integer type definitions

/************************************Defince Traffic Lights Operations********************************/
// YELLOW,  RED,  GREEN,  WHITE are defined in vga_display.h
#define R		{RED,  WHITE,  WHITE} //Active red light to red and inactive others (set to white)
#define RY		{ RED,  YELLOW,  WHITE} //Active red and yellow light and inactive green light (set to white)
#define G		{ WHITE,  WHITE,  GREEN} //Active green light to red and inactive others (set to white)
#define Y		{ WHITE,  YELLOW,  WHITE} //Active yellow light to red and inactive others (set to white)


/************************************Define of corresponding VA regions of lights *******************/
/********************VGA Locations of each light(red, yellow, green) for the first road**************/
#define ROAD_1_RED_LOCATION 	0
#define ROAD_1_YELLOW_LOCATION 	1
#define ROAD_1_GREEN_LOCATION 	2

/**********************VGA Locations of each light(red, yellow, green) for the second road***********/
#define ROAD_2_RED_LOCATION 	3
#define ROAD_2_YELLOW_LOCATION 	4
#define ROAD_2_GREEN_LOCATION 	5

/*************VGA Locations of each light(red, yellow, green) for the third road*****************/
#define ROAD_3_RED_LOCATION 	6
#define ROAD_3_YELLOW_LOCATION 	7
#define ROAD_3_GREEN_LOCATION 	8

/*****************************VGA Locations for pedestrian light*********************************/
#define PED_VGA_LOCATION 	10


/*********************Define of corresponding LED regions of lights *****************************/
/*********************LED Locations of each light(red, yellow, green) for the first road*********/
#define ROAD_1_GREEN_LED_LOCATION 	0b0000000000000010
#define ROAD_1_YELLOW_LED_LOCATION 	0b0000000000000100
#define ROAD_1_RED_LED_LOCATION 	0b0000000000001000

/*************LED Locations of each light(red, yellow, green) for the second road*************/
#define ROAD_2_GREEN_LED_LOCATION 	0b0000000000010000
#define ROAD_2_YELLOW_LED_LOCATION 	0b0000000000100000
#define ROAD_2_RED_LED_LOCATION 	0b0000000001000000

/*************LED Locations of each light(red, yellow, green) for the third road*************/
#define ROAD_3_GREEN_LED_LOCATION 	0b0000000010000000
#define ROAD_3_YELLOW_LED_LOCATION 	0b0000000100000000
#define ROAD_3_RED_LED_LOCATION 	0b0000001000000000

/*************************VGA and LED Locations of pedestrian light *************************/
#define PED_LED_LOCATION 	0b0000000000000001 //led location for pedestrian light


/*************************The led states when pedestrian can cross the road *****************/
// Using logic OR to get location code on all three roads
#define PED_CROSS_LEDS		ROAD_1_RED_LED_LOCATION  | ROAD_2_RED_LED_LOCATION  | ROAD_3_RED_LED_LOCATION //Active all three red lights

/************************************Defince Structures used for traffic lights and roads********************************/
struct trafficStates{
	char red_light_state; 		//'r' for red 'w' for white
	char yellow_light_state;	//'y' for yellow 'w' for white
	char green_light_state;		//'g' for green 'w' for white
};

struct road{
	u8 red_light_address; 					//location of red light on VAG
	u8 yellow_light_address; 				//location of yellow light on VAG
	u8 green_light_address;					//location of green light on VAG
	u16 red_light_led_address;				//location of red light on LED display
	u16 yellow_light_led_address;			//location of yellow light on LED display
	u16 green_light_led_address;			//location of green light on LED display
	u8 curr_state_index;					//Current index of state in the state array like  {R, RY, G, Y, R}
	struct trafficStates *states_sequence; 	//The state array like  {R, RY, G, Y, R}
};

struct pedestrianLight{
	u8 light_vga_address;		//location of pedestrian light on VAG.
	u16 light_led_address;	//location of pedestrian light on LED display.
};

/************************** Function Prototypes ******************************/
//Function defined in traffic_light.c which used to initialize traffic lights (all reds).
void init_traffic_colour(struct road* rd, s8 numOfRoads,struct pedestrianLight* ped_light);
void traffic_light_loop(struct road rd); //Function defined in traffic_light.c which used to change the traffic lights colour to current state.
//Function defined in traffic_light.c which used to initialise three roads(specified in this coursework) with regions on vga display, 
//traffic light states sequence and pedestrian light.
void init_roads(struct road* roads, struct trafficStates* lights_operation,struct pedestrianLight* ped_light);

#endif /* TRAFFIC_LIGHTS_H_ */
