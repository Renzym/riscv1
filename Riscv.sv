module Riscv (
    input  logic                  Clk,
    input  logic                  Reset
)

    // Program Counter

    // Program memory
    RamSp
    #(
        .RAM_WIDTH 		 (32               ),
        .RAM_ADDR_BITS 	 (9                ),
        .DATA_FILE 		 ("Program.hex"    ),
        .INIT_START_ADDR (0                ),
        .INIT_END_ADDR	 (10               )
    )
    ProgMemInst
    (
        .Clk,
        .WrEn,
        .Addr,
        .WrData,
        .RdData
    );

    // Register file
    Regfile #(
    .ADDR_WIDTH(5),
    .DATA_WIDTH(32)
    )
    RegfileInst (
    .Clk        ,
    .Reset      ,
    .RdAddr1    ,
    .RdAddr2    ,
    .RdData1    ,
    .RdData2    ,
    .WrAddr     ,
    .WrData     ,
    .WrEn       
    )

    // ALU

    // Data memory
    RamSp
    #(
        .RAM_WIDTH 		 (32               ),
        .RAM_ADDR_BITS 	 (9                ),
        .DATA_FILE 		 ("Data.hex"       ),
        .INIT_START_ADDR (0                ),
        .INIT_END_ADDR	 (10               )
    )
    DataMemInst
    (
        .Clk,
        .WrEn,
        .Addr,
        .WrData,
        .RdData
    );

endmodule