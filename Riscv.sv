import Rv32iPkg::*;
module Riscv (
    input  logic                  Clk,
    input  logic                  Reset
)
    localparam PC_WIDTH      = 32;
    localparam INSTR_WIDTH   = 32;
    localparam DATA_WIDTH    = 32;
    localparam SRC1_MSB      = 19;
    localparam SRC2_MSB      = 24;
    localparam DST_MSB       = 11;
    localparam REGADDR_WIDTH = 5;
    localparam SEL_REG_WB_ALU  = 0;
    localparam SEL_REG_WB_DMEM = 1;
    localparam SEL_REG_WB_PC   = 2;
    localparam SEL_REG_WB_IMM  = 3;

    logic [PC_WIDTH-1:0]    Pc;
    logic [PC_WIDTH-1:0]    PcNxt;
    logic [INSTR_WIDTH-1:0] Instr;
    logic                   JalPcSel;
    logic                   BrPcSel;
    logic [DATA_WIDTH:0]    Src1;
    logic [DATA_WIDTH:0]    Src2;
    logic [DATA_WIDTH:0]    AluOut;
    logic [PC_WIDTH-1:0]    BrPcOff;   
    logic                   Op2Sel; // SrcSel in diagram
    logic                   AuipcSel;
    logic [DATA_WIDTH-1:0]  DmemDout;
    logic [1:0]             RegWb;
    logic [DATA_WIDTH-1:0]  RegWrData;
    logic [DATA_WIDTH-1:0]  RegWrImm;
    logic                   DmemWr;
    logic                   RegWrEn;
    logic                   BrTaken; // TODO

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
    ) ProgMemInst (
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
    ) RegfileInst (
    .Clk        ,
    .Reset      ,
    .RdAddr1    (Instr[SRC1_MSB-:REGADDR_WIDTH]),
    .RdAddr2    (Instr[SRC2_MSB-:REGADDR_WIDTH]),
    .RdData1    (RegSrc1                       ),
    .RdData2    (RegSrc2                       ),
    .WrAddr     (Instr[DST_MSB-:REGADDR_WIDTH] ),
    .WrData     (RegWrData                     ),
    .WrEn       (RegWrEn)
    )
    // ALU
    assign AluOp1 = AuipcSel ? Pc     : RegSrc1;
    assign AluOp2 = Op2Sel   ? ImmExt : RegSrc2;
    Alu #(
        .DATA_WIDTH   (DATA_WIDTH  ),
        .INSTR_WIDTH  (INSTR_WIDTH )
    ) AluInst (
        .AluOp1          ,
        .AluOp2          ,
        .AluOut          ,
        .Instr           ,
        .BrTaken         

    )

    // Data memory
    RamSp
    #(
        .RAM_WIDTH 		 (32               ),
        .RAM_ADDR_BITS 	 (9                ),
        .DATA_FILE 		 ("Data.hex"       ),
        .INIT_START_ADDR (0                ),
        .INIT_END_ADDR	 (10               )
    ) DataMemInst (
        .Clk,
        .WrEn            (DmemWr          ),
        .Addr            (AluOut          ),
        .WrData          (RegSrc2         ),
        .RdData          (DmemDout        )
    );
    // Write back Mux
    always_comb begin
        unique case(RegWb)
        SEL_REG_WB_ALU:  RegWrData = AluOut;
        SEL_REG_WB_DMEM: RegWrData = DmemDout; // TODO: Handle byte and half word cases
        SEL_REG_WB_PC:   RegWrData = Pc;
        SEL_REG_WB_IMM:  RegWrData = RegWrImm;
        endcase
    end

    // Control logic (Putting here instead of new module as it would change with pipelined implementation)
    InstructionT InstrT = InstructionT'(Instr);
    assign Op2Sel   = ~(InstrT.GetOpcode() == OP_MATH  | InstrT.GetOpcode() == OP_BRANCH);
    assign DmemWr   =   InstrT.GetOpcode() == OP_STORE;
    assign RegWrEn  = ~(InstrT.GetOpcode() == OP_STORE | InstrT.GetOpcode() == OP_BRANCH);
    assign RegWb    =  (InstrT.GetOpcode() == OP_MATH  | InstrT.GetOpcode() == OP_MATH_IMM | InstrT.GetOpcode() == OP_AUIPC) ? SEL_REG_WB_ALU :
                      ((InstrT.GetOpcode() == OP_LOAD) ? SEL_REG_WB_DMEM : 
                       (InstrT.GetOpcode() == OP_LUI ? SEL_REG_WB_IMM : SEL_REG_WB_PC)); 
    assign AuipcSel =   InstrT.GetOpcode() == OP_AUIPC;
    assign BrPcSel  =   InstrT.GetOpcode() == OP_JAL   | ((InstrT.GetOpcode() == OP_BRANCH) & BrTaken);
    assign JalPcSel =   InstrT.GetOpcode() == OP_JALR;
endmodule