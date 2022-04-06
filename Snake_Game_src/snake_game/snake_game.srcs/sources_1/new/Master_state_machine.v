`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/22 14:10:13
// Design Name: 
// Module Name: Master_state_machine
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


module Master_state_machine(
input score,
input FAIL,
input BTNU,
input BTND,
input BTNL,
input BTNR,
input CLK,
input RESET,
output [1:0]Master_state
    );
    reg [1:0]Curr_state;
    reg [1:0]Next_state;
    assign Master_state = Curr_state;
    
always@(posedge CLK)begin
     if(RESET)
     Curr_state <= 2'd0;
     else
     Curr_state <= Next_state;
     end
     
always@(BTNU or BTND or BTNR or BTNL or Curr_state)begin
    case(Curr_state)
  
    2'd0: begin
    if(BTNU)
    Next_state <= 2'd1;
    
    else if(BTND)
    Next_state <= 2'd1;
    
    else if(BTNR)
    Next_state <= 2'd1;
    
    else if(BTNL)
    Next_state <= 2'd1;
    
    else
    Next_state <= Curr_state;
    end
    
    2'd1: begin
    if(score == 1)
    Next_state <= 2'd2;
    else if(FAIL ==1)
    Next_state <= 2'd3;
    else
    Next_state <= Curr_state;
    end
    
    2'd3: begin
    Next_state <= Curr_state;
    end
    
    2'd2: begin
    Next_state <= Curr_state;
    end
    endcase
end

    
    
    
    
    
    
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
endmodule
