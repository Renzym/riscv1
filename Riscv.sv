module Riscv (
    input  logic                  Clk,
    input  logic                  Reset
)
    localparam PC_WIDTH     = 32;
    localparam INSTR_WIDTH  = 32;
    localparam DATA_WIDTH   = 32;
    localparam SRC1_MSB     = 19;
    localparam SRC2_MSB     = 24;
    localparam DST_MSB      = 11;
    localparam REGADDR_WIDTH = 5;
    logic [PC_WIDTH-1:0]    Pc;
    logic [PC_WIDTH-1:0]    PcNxt;
    logic [INSTR_WIDTH-1:0] Instr;
    logic                   JalPcSel;
    logic                   BrPcSel;
    logic [DATA_WIDTH:0]    AluOut;
    logic [PC_WIDTH-1:0]    BrPcOff;   

    // Program Counter
    always_ff @(posedge clk) begin
        if(Reset)   Pc <= 0;
        else        Pc <= PcNext;
    end

    assign PcNxt = JalPcSel ? AluOut : (Pc + (BrPcSel ? BrPcOff : 32'd4));
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
        .Clk    ,
        .WrEn   ('0     ),
        .Addr   (Pc     ),
        .WrData ('0     ),
        .RdData (Instr  )
    );

    // Register file
    Regfile #(
    .ADDR_WIDTH(5),
    .DATA_WIDTH(32)
    )
    RegfileInst (
    .Clk        ,
    .Reset      ,
    .RdAddr1    (Instr[SRC1_MSB-:REGADDR_WIDTH]),
    .RdAddr2    (Instr[SRC2_MSB-:REGADDR_WIDTH]),
    .RdData1    ,
    .RdData2    ,
    .WrAddr     (Instr[DST_MSB-:REGADDR_WIDTH]),
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