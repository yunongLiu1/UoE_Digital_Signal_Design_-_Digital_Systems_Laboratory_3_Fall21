`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/23 19:01:29
// Design Name: 
// Module Name: Top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Top(
input CLK,
input RESET,
input BTNR,
input BTND,
input BTNL,
input BTNU,
output [11:0] COLOUR_OUT,
output  HS,
output  VS,
output [3:0]SEG_SELECT,
output [7:0]DEC_OUT,
output [9:0]LED
    );
    

   wire[1:0]MS;
   wire score;
    wire DIE;
    wire FAIL;
    Master_state_machine MSM(
    .score(score),
    .FAIL(FAIL),
    .BTNU(BTNU),
    .BTND(BTND),
    .BTNL(BTNL),
    .BTNR(BTNR),
    .CLK(CLK),
    .RESET(RESET),
    .Master_state(MS)
    );
    
    wire[1:0] Navigation_state_out;
    Navigation_state_machine NSM(
       .CLK(CLK),
       .RESET(RESET),
       .BTNU(BTNU),
       .BTND(BTND),
       .BTNL(BTNL),
       .BTNR(BTNR),
       .Navigation_state_out(Navigation_state_out)
       );
       
     wire[3:0]SEG_SELECT;
     wire[7:0]DEC_OUT;
     wire Reached_target;
     
     Score_counter SC(
    .Reached_target(Reached_target),
    .RESET(RESET),
    .CLK(CLK),
    .SEG_SELECT(SEG_SELECT),
    .DEC_OUT(DEC_OUT),
    .score(score),
    .FAIL(FAIL),
    .Master_state(MS),
    .LED(LED)
    );
    
    wire[11:0]C_IN;
    wire[18:0]Pixel_Address;
    wire DIE;
    vga_all1 VGA_Display(
    .CLK(CLK),
    .RESET(RESET),
    .Colour_in(C_IN),
    .Master_state(MS),
    .COLOUR_OUT(COLOUR_OUT),
    .HS(HS),
    .VS(VS),
    .Pixel_Address(Pixel_Address),
    .DIE(DIE)
    );
    
    wire[14:0]Random_target_address;
    Target_generator TG(
    .Reached_target(Reached_target),
    .CLK(CLK),
    .RESET(RESET),
    .Random_target_address(Random_target_address)
    );

    Snake_control MAIN(
    .Pixel_Address(Pixel_Address),
    .Random_target_address(Random_target_address),
    .Master_state(MS),
    .Navigation_state_out(Navigation_state_out),
    .CLK(CLK),
    .RESET(RESET),
    .Reached_target(Reached_target),
    .Colour_in(C_IN)
    );
     
     
     
     
     
     
     
     
     
     
     
     
       
       
       
       
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
endmodule
