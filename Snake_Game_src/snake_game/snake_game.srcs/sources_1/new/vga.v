`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 22.11.2021 14:59:57
// Design Name: 
// Module Name: vga
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


module VGA1(
    input   CLK,
    input   [11:0] COLOUR_IN,
    output reg [9:0] ADDRH,
    output reg [8:0] ADDRV,
    output reg [11:0] COLOUR_OUT,
    output reg HS,
    output reg VS
    );
    
parameter VerTimeToPulseWidthEnd  = 10'd2;
parameter VerTimeToBackPorchEnd   = 10'd31;
parameter VerTimeToDisplayTimeEnd = 10'd511;
parameter VerTimeToFrontPorchEnd  = 10'd521;

parameter HorzTimeToPulseWidthEnd  = 10'd96;
parameter HorzTimeToBackPorchEnd   = 10'd144;
parameter HorzTimeToDisplayTimeEnd = 10'd784;
parameter HorzTimeToFrontPorchEnd  = 10'd800;

wire SlowDownCounteroutput;
wire HorzCounteroutput;

wire [9:0]VerCounteroutputValue;
wire [9:0]HorzCounteroutputValue;

     Counter1 # (.COUNTER_WIDTH(2),
                .COUNTER_MAX(3)
                )
                SlowDownCounter(
               .CLK(CLK),
               .RESET(1'b0),
               .ENABLE(1'b1),
               .TRIG_OUT(SlowDownCounteroutput)
               );
               
     Counter1 # (.COUNTER_WIDTH(10),
                .COUNTER_MAX(799)
                )
                HorCounter(
               .CLK(CLK),
               .RESET(1'b0),
               .ENABLE(SlowDownCounteroutput),
               .TRIG_OUT(HorzCounteroutput),
               .COUNT(HorzCounteroutputValue)
               );
              
      Counter1 # (.COUNTER_WIDTH(9),
                 .COUNTER_MAX(520)
                 )
                 VerCounter(
                .CLK(CLK),
                .RESET(1'b0),
                .ENABLE(HorzCounteroutput),
                .COUNT(VerCounteroutputValue)
                );
    
    always@(posedge CLK) begin
    if (HorzCounteroutputValue <= HorzTimeToPulseWidthEnd)
        HS <= 0;
    else
        HS <= 1;
    end
    
    always@(posedge CLK) begin
    if (VerCounteroutputValue <= VerTimeToPulseWidthEnd)
        VS <= 0;
    else
        VS <= 1;
    end
    
    always@(posedge CLK) begin
    if((HorzCounteroutputValue >= HorzTimeToBackPorchEnd) && (HorzCounteroutputValue <= HorzTimeToDisplayTimeEnd) 
      && (VerCounteroutputValue >= VerTimeToBackPorchEnd) && (VerCounteroutputValue <= VerTimeToDisplayTimeEnd))
        COLOUR_OUT <= COLOUR_IN;
    else
        COLOUR_OUT <= 0;
    end
    
    always@(posedge CLK) begin
    if ((HorzCounteroutputValue >= HorzTimeToPulseWidthEnd) && (HorzCounteroutputValue <= HorzTimeToDisplayTimeEnd))
        ADDRH <= HorzCounteroutputValue - 144;
    else
        ADDRH <= 0;
    end
    
    always@(posedge CLK) begin
    if ((VerCounteroutputValue >= VerTimeToPulseWidthEnd) &&(VerCounteroutputValue <= VerTimeToDisplayTimeEnd))
        ADDRV <= VerCounteroutputValue - 31;
    else
        ADDRV <= 0;
    end
    
       

endmodule
