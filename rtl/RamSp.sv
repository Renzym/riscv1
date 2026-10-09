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
		parameter INIT_END_ADDR = (2**RAM_ADDR_BITS)-1
	)
	(
	input  	logic					    Clk,
	input	logic	[(RAM_WIDTH/8)-1:0] WrEn,
    input 	logic	[RAM_ADDR_BITS-1:0]	Addr,
    input 	logic	[RAM_WIDTH-1:0] 	WrData,
	output  logic	[RAM_WIDTH-1:0] 	RdData
	);
   localparam int RAM_DEPTH = 2**RAM_ADDR_BITS;
   logic [RAM_WIDTH-1:0] RamArray [0:RAM_DEPTH-1];

   initial begin
      // Empty filename is useful for directed benches which supply RAM words.
      for (int i = 0; i < RAM_DEPTH; i++)
         RamArray[i] = '0;
      if (DATA_FILE != "") begin
         // synthesis translate_off
         integer fd;
         fd = $fopen(DATA_FILE, "r");
         if (fd == 0) $fatal(1, "Cannot open memory image %s", DATA_FILE);
         $fclose(fd);
         // synthesis translate_on
         $readmemh(DATA_FILE, RamArray, INIT_START_ADDR, INIT_END_ADDR);
      end
   end

    always_ff @(posedge Clk) begin
        for(int i=0; i<(RAM_WIDTH/8);i++) begin
            if (WrEn[i])   RamArray[Addr][i*8 +: 8] <= WrData[i*8 +: 8];
        end
    end

    assign RdData = RamArray[Addr];

endmodule
