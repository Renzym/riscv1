/*
    Generic flop based single port Ram with byte enables. Reads on same cycle
*/
`timescale 1ns/1ps

module RamSp
	#(
		parameter RAM_WIDTH 		= 32,
		parameter RAM_ADDR_BITS 	= 9,
		parameter DATA_FILE 		= "data_file.txt",
		parameter INIT_START_ADDR 	= 0,
		parameter INIT_END_ADDR		= 10
	)
	(
	input  	logic					    Clk,
	input	logic	[(RAM_WIDTH/8)-1:0] WrEn,
    input 	logic	[RAM_ADDR_BITS-1:0]	Addr,
    input 	logic	[RAM_WIDTH-1:0] 	WrData,
	output  logic	[RAM_WIDTH-1:0] 	RdData
	);
   reg [RAM_WIDTH-1:0] RamArray [(2**RAM_ADDR_BITS)-1:0];


   //  The forllowing code is only necessary if you wish to initialize the RAM 
   //  contents via an external file (use $readmemb for binary data)
   initial
      $readmemh(DATA_FILE, RamArray, INIT_START_ADDR, INIT_END_ADDR);

    always_ff @(posedge Clk) begin
        for(int i=0; i<(RAM_WIDTH/8);i++) begin
            if (WrEn[i])   RamArray[Addr][i*8 +: 8] <= WrData[i*8 +: 8];
        end
    end

    assign RdData = RamArray[Addr];

endmodule
