`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 22.11.2021 15:02:08
// Design Name: 
// Module Name: vga_all
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


module vga_all1(
    input   CLK,
    input RESET,
    input [11:0]Colour_in,
    input   [1:0]Master_state,
    output  [11:0] COLOUR_OUT,
    output  HS,
    output  VS,
    output [18:0]Pixel_Address,
    input DIE
    );
    
    
    reg [11:0]COLOUR;
    reg  [15:0]FrameCount;
    wire [9:0]ADDRH;
    wire [8:0]ADDRV; 
    assign Pixel_Address = {ADDRH , ADDRV};
    
    VGA1 vga(
        .CLK(CLK),
        .COLOUR_IN(COLOUR),
        .COLOUR_OUT(COLOUR_OUT),
        .ADDRV(ADDRV),
        .ADDRH(ADDRH),
        .HS(HS),
        .VS(VS)
    );
    
    always@(posedge CLK) begin
        if(ADDRV == 479) begin
            FrameCount <= FrameCount + 1;
        end
    end
    
    always@(posedge CLK) begin
          if(RESET) begin
           COLOUR <= 12'hF00;
           end
          else if(Master_state == 2'd2) begin
            if(ADDRV[8:0] > 240) begin
                if(ADDRH[9:0] >320)
                    COLOUR <= FrameCount[15:8] + ADDRV[7:0] + ADDRH[7:0] - 240 - 320;
                else
                    COLOUR <= FrameCount[15:8] + ADDRV[7:0] - ADDRH[7:0] - 240 + 320;
            end
            else begin
                if(ADDRH >320)
                    COLOUR <= FrameCount[15:8] - ADDRV[7:0] + ADDRH[7:0] + 240 - 320;
                else
                    COLOUR<= FrameCount[15:8] - ADDRV[7:0] - ADDRH[7:0] + 240 + 320; 
                end
            end
        else if(Master_state ==2'd1)begin
        COLOUR <= Colour_in;
        end
       else if(DIE)begin
         COLOUR <= 12'h000;
       end
        else COLOUR <= 12'hF00;
            
    end
 endmodule
