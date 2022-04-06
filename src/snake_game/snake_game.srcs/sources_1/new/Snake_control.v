`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/23 14:16:36
// Design Name: 
// Module Name: Snake_control
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

module Snake_control(
input [18:0]Pixel_Address,
input [14:0]Random_target_address,
//input [14:0]Random_target_address1,
input [1:0]Master_state,
input [1:0]Navigation_state_out,
input CLK,
input RESET,
output reg Reached_target,
output [11:0]Colour_in,
output reg DIE


    );
    reg[11:0]colour;
    parameter MaxX = 160;
    parameter MaxY = 120;
    parameter SnakeLength = 30;
    reg [7:0]SnakeState_X [0:SnakeLength-1];
    reg [6:0]SnakeState_Y [0:SnakeLength-1];
    wire[23:0]MOVE;
    reg [4:0]Growth;
    
       Counter1 # (.COUNTER_WIDTH(24),     
               .COUNTER_MAX(9999999)
               )
               snake(
              .CLK(CLK),
              .RESET(RESET),
              .ENABLE(1'b1),
              .COUNT(MOVE)
              );
    
    genvar PixNo;         //make the snake move
    generate
    for(PixNo = 0; PixNo < SnakeLength - 1; PixNo = PixNo + 1)
    begin: PixShift
        always@(posedge CLK)begin
            if(RESET)begin
                SnakeState_X[PixNo + 1] <= 80;
                SnakeState_Y[PixNo + 1] <= 100;
            end
            else if(MOVE == 0)begin
            SnakeState_X[PixNo + 1] <= SnakeState_X[PixNo];
            SnakeState_Y[PixNo + 1] <= SnakeState_Y[PixNo];
            end
        end
    end
    endgenerate
    
    always@(posedge CLK)begin                       //reach edge case
         if(RESET)begin
         SnakeState_X[0] <= 80;
         SnakeState_Y[0] <= 100;
         end
         else if(MOVE == 0)begin
            case(Navigation_state_out)
            
            2'd0: begin
            if(SnakeState_X[0] == MaxX)
            SnakeState_X[0] <= 0;
            else SnakeState_X[0] <= SnakeState_X[0]+1;
            end
            
            2'd3:begin
            if(SnakeState_X[0] == 0)
            SnakeState_X[0] <= MaxX;
            else SnakeState_X[0]<= SnakeState_X[0]-1;
            end
            
            2'd1:begin
            if(SnakeState_Y[0] == 0)
            SnakeState_Y[0] <= MaxY;
            else SnakeState_Y[0] <= SnakeState_Y[0]-1;
            end
            
            2'd2:begin
            if(SnakeState_Y[0] == MaxY)
            SnakeState_Y[0] <= 0;
            else SnakeState_Y[0]<= SnakeState_Y[0]+1;
            end
            endcase
        end
    end
    wire [7:0]TargetX;
    wire [6:0]TargetY;
    //    wire [7:0]TargetA;
    //    wire [6:0]TargetB;
    assign TargetX = Random_target_address[14:7];
    assign TargetY = Random_target_address[6:0];
//    assign TargetX = Random_target_address1[14:7];
//    assign TargetY = Random_target_address1[6:0];
    
    always@(SnakeState_X[0] or Random_target_address or SnakeState_Y[0])begin
    if(SnakeState_X[0] == TargetX && SnakeState_Y[0] == TargetY)
    Reached_target <= 1;
    else 
    Reached_target <= 0;
    end
    
    integer i;
    always@(posedge CLK)begin
        if(Reached_target)            //snake gets longer
            Growth <= Growth + 1;
        else if(RESET)
            Growth <= 0;    
        for(i=1; i<20; i = i+1)begin   //if eat snake itself, snake gets shorter
            if(SnakeState_X[0] == SnakeState_X[i] && SnakeState_Y[0] == SnakeState_Y[i] && Growth != 0)
                Growth <= Growth - 1;
                DIE <= 1;     //trig out signal die to the VGA display
        end
    end
    
    always@(posedge CLK)begin
    for(i=0; i<30; i = i+1)begin                                                                    //initial length + change
        if(Pixel_Address[18:9]>>2 == SnakeState_X[i] && Pixel_Address[8:0]>>2 == SnakeState_Y[i] && i < 20 + Growth )
        colour <= 12'h0FF + Growth * 12;
    end
    if(Pixel_Address[18:9]>>2== TargetX && Pixel_Address[8:0]>>2 == TargetY)
    colour = 12'h00F;
    //    if(Pixel_Address[18:9]>>2== TargetA && Pixel_Address[8:0]>>2 == TargetB)
    //colour = 12'h00F;
    
    else
    colour = 12'hF00;
    end
    
    assign Colour_in = colour;

endmodule