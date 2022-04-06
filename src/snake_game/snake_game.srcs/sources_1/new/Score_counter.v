`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/22 16:24:36
// Design Name: 
// Module Name: Score_counter
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


module Score_counter(
input Reached_target,
input RESET,
input CLK,
input DIE,
output [3:0]SEG_SELECT,
output [7:0]DEC_OUT,
output score,
output FAIL,
input Master_state,
output reg[9:0]LED
    );
    wire [1:0]StrobeCount;
    wire Bit17TrigOut;
    assign DecCountAndDOT0 = {1'b0,DecCount0};
    assign DecCountAndDOT1 = {1'b0,DecCount1};
    assign DecCountAndDOT2 = {1'b0,DecCount2};
    assign DecCountAndDOT3 = {1'b0,DecCount3};
    
    wire [1:0] StrobeCount;
    wire [4:0] DecCountAndDOT0;
    wire [4:0] DecCountAndDOT1;
    wire [4:0] DecCountAndDOT2;
    wire [4:0] DecCountAndDOT3;
    wire [3:0] DecCount0;
    wire [3:0] DecCount1; 
    wire [3:0] DecCount2; 
    wire [3:0] DecCount3; 
    wire [4:0] MuxOut;   
    wire MOVE;
    
 Counter1 # (.COUNTER_WIDTH(17),      //slow down 100000times
                  .COUNTER_MAX(99999)
                  )
                  Bit17Counter(
                 .CLK(CLK),
                 .RESET(RESET),
                 .ENABLE(1'b1),
                 .TRIG_OUT(Bit17TrigOut)
                 );
                 
       Counter1 # (.COUNTER_WIDTH(2),       
                   .COUNTER_MAX(3)
                   )
                   Bit2Counter(
                  .CLK(CLK),
                  .RESET(RESET),
                  .ENABLE(Bit17TrigOut),
                  //.TRIG_OUT(Stri),
                  .COUNT(StrobeCount)
                  );
Counter1 # (.COUNTER_WIDTH(4),              //fail counter
                               .COUNTER_MAX(1)       
                               )
                               Faliure(
                               .CLK(CLK),
                               .RESET(RESET),
                               .ENABLE(DIE),
                               .TRIG_OUT(FAIL)
                          
                               );        

Counter1 # (.COUNTER_WIDTH(4),          //No.1 number
             .COUNTER_MAX(3)       //when reach 4, trig out score signal
             )
             Bit4(
             .CLK(CLK),
             .RESET(RESET),
             .ENABLE(Reached_target),
             .TRIG_OUT(score),
             .COUNT(DecCount0)
             );        
 always@(posedge CLK)begin
 LED = DecCount0 *2;
 end
                                         
Counter1 # (.COUNTER_WIDTH(1),          //No.2 number
            .COUNTER_MAX(0)
            )
            Bit1(
            .CLK(CLK),
            .RESET(RESET),
            .ENABLE(score),
            .COUNT(DecCount1)
            ); 
wire DOWN;
wire DOWN1;
Counter1 # (.COUNTER_WIDTH(30),     // 1s counter
             .COUNTER_MAX(99999999)
              )
              SLOWDOWN(
             .CLK(CLK),
             .RESET(1'b0),
             .ENABLE(1'b1),
             .TRIG_OUT(DOWN)
             );
Minus_Counter#(.COUNTER_WIDTH(4),
                .COUNTER_MAX(9))
                countdown1(
                .CLK(CLK),
                .RESET(RESET),
                .ENABLE(DOWN && Master_state == 2'd1),
                .TRIG_OUT(DOWN1),
                .COUNT(DecCount2)
                );
Minus_Counter#(.COUNTER_WIDTH(4),
               .COUNTER_MAX(9))
               countdown2(
               .CLK(CLK),
               .RESET(RESET),
               .ENABLE(DOWN1),
               .COUNT(DecCount3)
               );               

 
 
                                                                                        
                Multiplexer_4way Mux4(
                .CONTROL(StrobeCount),
                .IN0(DecCountAndDOT0),
                .IN1(DecCountAndDOT1),
                .IN2(DecCountAndDOT2),
                .IN3(DecCountAndDOT3),
                .OUT(MuxOut)
                );
                                                                          
                Seg7Display d7(
                .SEG_SELECT_IN(StrobeCount),
                .BIN_IN(MuxOut[3:0]),
                .DOT_IN(MuxOut[4]),
                .SEG_SELECT_OUT(SEG_SELECT),
                .HEX_OUT(DEC_OUT)
                );                                                                                                                                                       
    
endmodule
