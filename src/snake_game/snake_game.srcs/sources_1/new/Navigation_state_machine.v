`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/22 14:44:37
// Design Name: 
// Module Name: Navigation_state_machine
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


module Navigation_state_machine(
input CLK,
input RESET,
input BTNR,
input BTNL,
input BTNU,
input BTND,
output [1:0]Navigation_state_out
    );
    reg [1:0]Curr_state;
    reg [1:0]Next_state;
    assign Navigation_state_out = Curr_state;
    
always@(posedge CLK)begin
         if(RESET)
         Curr_state <= 2'd0;
         else
         Curr_state <= Next_state;
         end
         
 always@(BTNU or BTND or BTNR or BTNL or Curr_state)begin
             case(Curr_state)
           
             2'd0: begin        //right
             if(BTNU)
             Next_state <= 2'd1; //up
             else if(BTND)    
             Next_state <= 2'd2;    //down
             else
             Next_state <= Curr_state;
             end
             
             2'd1: begin     //up
             if(BTNL)
             Next_state <= 2'd3;  //left
             else if(BTNR)
             Next_state <= 2'd0; //right
             else
             Next_state <= Curr_state;
             end
             
             2'd2: begin    //down 
             if(BTNL)
             Next_state <= 2'd3;  //left
             else if(BTNR)
             Next_state <= 2'd0; //right
             else
             Next_state <= Curr_state;
             end
             
             2'd3: begin        //left
             if(BTNU)
             Next_state <= 2'd1; //up
             else if(BTND)    
             Next_state <= 2'd2;    //down
             else
             Next_state <= Curr_state;
             end
             endcase        
    end
    
    
    
    
    
    
    
    
    
    
    
    
endmodule
