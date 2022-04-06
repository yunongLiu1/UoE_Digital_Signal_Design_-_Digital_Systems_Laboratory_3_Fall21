`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/23 20:53:49
// Design Name: 
// Module Name: Top_tb
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


module Top_tb(

    );
    
    reg CLK;
    reg RESET;
    reg BTNU;
    reg BTND;
    reg BTNL;
    reg BTNR;
    
    wire [11:0] COLOUR_OUT;
    wire HS;
    wire VS;
    top uut(
        .CLK(CLK),
        .RESET(RESET),
        .BTNR(BTNR),
        .BTNL(BTNL),
        .BTNU(BTNU),
        .BTND(BTND),
        .COLOUR_OUT(COLOUR_OUT),
        .HS(HS),
        .VS(VS));
endmodule
