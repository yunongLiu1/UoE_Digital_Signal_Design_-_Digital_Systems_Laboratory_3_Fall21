`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/22 15:39:33
// Design Name: 
// Module Name: Target_generator
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


module Target_generator(
input Reached_target,
input CLK,
input RESET,
output reg[14:0]Random_target_address
//output reg[14:0]Random_target_address1
    );
    reg [6:0]LFSRY = 7'b0010010;
    reg [7:0]LFSRX = 8'b01001001;
//    reg [7:0]LFSRA = 8'b01110001;
//    reg [6:0]LFSRB = 7'b0010010;
    reg IN;
    reg IN1;
//    reg IN2;
//    reg IN3;
    reg enable = 1'b1;
    reg [14:0]ADDR;
//    reg [14:0]ADDR1;
    
    
    always@(posedge CLK)begin
        IN = LFSRX[7]~^LFSRX[5]~^LFSRX[4]~^LFSRX[3];
        LFSRX = {LFSRX[6:0], IN};
    end
//        always@(posedge CLK)begin
//        IN2 = LFSRA[7]~^LFSRA[5]~^LFSRA[4]~^LFSRA[3];
//        LFSRA = {LFSRA[6:0], IN};
//    end
    
    always@(posedge CLK)begin
        IN1 = LFSRY[6]~^LFSRY[5];
        LFSRY = {LFSRY[5:0], IN};
    end
//        always@(posedge CLK)begin
//        IN3 = LFSRB[6]~^LFSRB[5];
//        LFSRB = {LFSRB[5:0], IN};
//    end
    always@(posedge CLK)begin
     if(LFSRX <= 8'd160 && LFSRY <= 7'd120)begin
            ADDR <= {LFSRX,LFSRY};
            end
    end
//        always@(posedge CLK)begin
//     if(LFSRA <= 8'd160 && LFSRB <= 7'd120)begin
//            ADDR1 <= {LFSRA,LFSRB};
//            end
//    end
    always@(posedge CLK)begin
        if(enable) begin
        Random_target_address <= 15'b010010100100101;
        enable <= 1'b0;
        end
        
        else if(Reached_target == 1)
        Random_target_address <= ADDR;
//        Random_target_address1 <= ADDR1;
    end


    
    endmodule