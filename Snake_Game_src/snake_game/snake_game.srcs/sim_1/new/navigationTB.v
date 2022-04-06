`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/29 16:38:11
// Design Name: 
// Module Name: navigationTB
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


module navigationTB(

    );
    reg CLK,RESET,BTNR,TBNU,BTNL,BTND;
    reg [1:0]Curr_state;
    reg [1:0]Next_state;
   wire [1:0]Navigation_state_out;
       
       Navigation_state_machine NSM(
      .CLK(CLK),
      .RESET(RESET),
      .BTNU(BTNU),
      .BTND(BTND),
      .BTNL(BTNL),
      .BTNR(BTNR),
      .Navigation_state_out(Navigation_state_out)
      );
      
    initial begin
    CLK<= 0;
    forever #10 CLK <= ~CLK;
    end
     
     initial begin
     RESET <= 0;
     #50; BTNR <= 1;
     #50; BTNR <= 0;
     #50; BTNU <= 1;
     #50; BTNU <= 0;
     #50; BTNL <=1;
     #50; BTNL <= 0;
     #50; BTND <=1;
     #50; BTND <= 0;
     end
     
     
     

endmodule
