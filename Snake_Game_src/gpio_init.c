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
#include "gpio_init.h" //Added for definitions of variable and constants, and function prototypes.

/*
 * This file is used to initialise the GPIOs.
 * The corresponding Device IDs are in xparameters.h
 */
XStatus initGpio(void)
{
	XStatus status;
	//XPAR_GPIO_7SEG_HEX_OUT_DEVICE_ID 0
	status = XGpio_Initialize(&SEG7_HEX_OUT, 0);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_7SEG_SEL_DEVICE_ID 1
	status = XGpio_Initialize(&SEG7_SEL_OUT, 1);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_LEDS_DEVICE_ID 2
	status = XGpio_Initialize(&LEDS_OUT, 2);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_P_BTN_D_DEVICE_ID 3
	status = XGpio_Initialize(&P_BTN_D, 3);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_P_BTN_L_DEVICE_ID 4
	status = XGpio_Initialize(&P_BTN_L, 4);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_P_BTN_R_DEVICE_ID 5
	status = XGpio_Initialize(&P_BTN_R, 5);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_P_BTN_U_DEVICE_ID 6
	status = XGpio_Initialize(&P_BTN_U, 6);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_0_COLOUR_OUT_DEVICE_ID 7
	status = XGpio_Initialize(&REGION_0_COLOUR, 7);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_10_COLOUR_OUT_DEVICE_ID 8
	status = XGpio_Initialize(&REGION_10_COLOUR, 8);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_11_COLOUR_OUT_DEVICE_ID 9
	status = XGpio_Initialize(&REGION_11_COLOUR, 9);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_1_COLOUR_OUT_DEVICE_ID 10
	status = XGpio_Initialize(&REGION_1_COLOUR, 10);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_2_COLOUR_OUT_DEVICE_ID 11
	status = XGpio_Initialize(&REGION_2_COLOUR, 11);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_3_COLOUR_OUT_DEVICE_ID 12
	status = XGpio_Initialize(&REGION_3_COLOUR, 12);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_4_COLOUR_OUT_DEVICE_ID 13
	status = XGpio_Initialize(&REGION_4_COLOUR, 13);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_5_COLOUR_OUT_DEVICE_ID 14
	status = XGpio_Initialize(&REGION_5_COLOUR, 14);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_6_COLOUR_OUT_DEVICE_ID 15
	status = XGpio_Initialize(&REGION_6_COLOUR, 15);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_7_COLOUR_OUT_DEVICE_ID 16
	status = XGpio_Initialize(&REGION_7_COLOUR, 16);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_8_COLOUR_OUT_DEVICE_ID 17
	status = XGpio_Initialize(&REGION_8_COLOUR, 17);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_REG_9_COLOUR_OUT_DEVICE_ID 18
	status = XGpio_Initialize(&REGION_9_COLOUR, 18);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_S_SWITCHES_DEVICE_ID 19
	status = XGpio_Initialize(&SLIDE_SWICHES, 19);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_VGA_HS_DEVICE_ID 20
	status = XGpio_Initialize(&VGA_HS, 20);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	//XPAR_GPIO_VGS_VS_DEVICE_ID 21
	status = XGpio_Initialize(&VGA_VS, 21);
	if (status != XST_SUCCESS)
	{
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

