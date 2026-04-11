`timescale 1ns/1ps

import Rv32iPkg::*;
module Riscv (
    input  logic                  Clk,
    input  logic                  Reset
);
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
    logic [PC_WIDTH-1:0]    PcPlus4;
    logic [INSTR_WIDTH-1:0] Instr;
    logic                   JalPcSel;
    logic                   BrPcSel;
    logic [DATA_WIDTH-1:0]  RegSrc1;
    logic [DATA_WIDTH-1:0]  RegSrc2;
    logic [DATA_WIDTH-1:0]  ImmExt;
    logic [DATA_WIDTH-1:0]  AluOp1;
    logic [DATA_WIDTH-1:0]  AluOp2;
    logic [DATA_WIDTH-1:0]  AluOut;
    logic [PC_WIDTH-1:0]    BrPcOff;   
    logic                   Op2Sel; // SrcSel in diagram
    logic                   AuipcSel;
    logic [DATA_WIDTH-1:0]  DmemDout;
    logic [1:0]             RegWb;
    logic [DATA_WIDTH-1:0]  RegWrData;
    logic [DATA_WIDTH-1:0]  RegWrImm;
    logic                   DmemWr;
    logic                   RegWrEn;
    logic [3:0]             DmemWrEn;
    logic                   BrTaken;
    InstructionT            InstrT;
    logic [8:0]             DmemWordAddr;
    logic [1:0]             DmemByteOff;
    logic [DATA_WIDTH-1:0]  LoadWbData;
    logic [3:0]             StoreWrEnMask;
    logic [DATA_WIDTH-1:0]  DmemWrData;

    // Program Counter
    always_ff @(posedge Clk) begin
        if(Reset)   Pc <= 0;
        else        Pc <= PcNxt;
    end

    assign PcPlus4 = Pc + 32'd4;
    assign BrPcOff = ImmExt;
    assign PcNxt = JalPcSel ? AluOut : (Pc + (BrPcSel ? BrPcOff : 32'd4));
    // Program memory
    RamSp
    #(
        .RAM_WIDTH 		 (32               ),
        .RAM_ADDR_BITS 	 (9                ),
        .DATA_FILE 		 ("Program.hex"    ),
        .INIT_START_ADDR (0                ),
        .INIT_END_ADDR	 (255              )
    ) ProgMemInst (
        .Clk    (Clk            ),
        .WrEn   ('0             ),
        .Addr   (Pc[8:0]        ),
        .WrData ('0             ),
        .RdData (Instr          )
    );

    assign InstrT = InstructionT'(Instr);

    // Register file
    Regfile #(
    .ADDR_WIDTH(5),
    .DATA_WIDTH(32)
    ) RegfileInst (
    .Clk        (Clk                          ),
    .Reset      (Reset                        ),
    .RdAddr1    (Instr[SRC1_MSB-:REGADDR_WIDTH]),
    .RdAddr2    (Instr[SRC2_MSB-:REGADDR_WIDTH]),
    .RdData1    (RegSrc1                       ),
    .RdData2    (RegSrc2                       ),
    .WrAddr     (Instr[DST_MSB-:REGADDR_WIDTH] ),
    .WrData     (RegWrData                     ),
    .WrEn       (RegWrEn)
    );
    // ALU
    assign AluOp1 = AuipcSel ? Pc     : RegSrc1;
    assign AluOp2 = Op2Sel   ? ImmExt : RegSrc2;
    Alu #(
        .DATA_WIDTH   (DATA_WIDTH  ),
        .INSTR_WIDTH  (INSTR_WIDTH )
    ) AluInst (
        .AluOp1          (AluOp1),
        .AluOp2          (AluOp2),
        .AluOut          (AluOut),
        .Instr           (Instr ),
        .BrTaken         (BrTaken)
    );

    always_comb begin
        DmemWrData = RegSrc2;
        if (GetOpcode(Instr) == OP_STORE) begin
            unique case (InstrT.SType.Funct3)
                F3_LB_SB: DmemWrData = {4{RegSrc2[7:0]}};
                F3_LH_SH: DmemWrData = {2{RegSrc2[15:0]}};
                default: ; // SW
            endcase
        end
    end

    // Data memory
    RamSp
    #(
        .RAM_WIDTH 		 (32               ),
        .RAM_ADDR_BITS 	 (9                ),
        .DATA_FILE 		 ("Data.hex"       ),
        .INIT_START_ADDR (0                ),
        .INIT_END_ADDR	 (255              )
    ) DataMemInst (
        .Clk             (Clk             ),
        .WrEn            (DmemWrEn        ),
        .Addr            (DmemWordAddr    ),
        .WrData          (DmemWrData      ),
        .RdData          (DmemDout        )
    );

    assign DmemWordAddr = AluOut[10:2];
    assign DmemByteOff  = AluOut[1:0];

    always_comb begin
        if (GetOpcode(Instr) != OP_LOAD)
            LoadWbData = DmemDout;
        else unique case (InstrT.IType.Funct3)
            F3_LW_SW:   LoadWbData = DmemDout;
            F3_LB_SB:   unique case (DmemByteOff)
                            2'b00: LoadWbData = {{24{DmemDout[7]}}, DmemDout[7:0]};
                            2'b01: LoadWbData = {{24{DmemDout[15]}}, DmemDout[15:8]};
                            2'b10: LoadWbData = {{24{DmemDout[23]}}, DmemDout[23:16]};
                            2'b11: LoadWbData = {{24{DmemDout[31]}}, DmemDout[31:24]};
                        endcase
            F3_LH_SH:   unique case (DmemByteOff[1])
                            1'b0: LoadWbData = {{16{DmemDout[15]}}, DmemDout[15:0]};
                            1'b1: LoadWbData = {{16{DmemDout[31]}}, DmemDout[31:16]};
                        endcase
            F3_LBU:     unique case (DmemByteOff)
                            2'b00: LoadWbData = {24'b0, DmemDout[7:0]};
                            2'b01: LoadWbData = {24'b0, DmemDout[15:8]};
                            2'b10: LoadWbData = {24'b0, DmemDout[23:16]};
                            2'b11: LoadWbData = {24'b0, DmemDout[31:24]};
                        endcase
            F3_LHU:     unique case (DmemByteOff[1])
                            1'b0: LoadWbData = {16'b0, DmemDout[15:0]};
                            1'b1: LoadWbData = {16'b0, DmemDout[31:16]};
                        endcase
            default:    LoadWbData = DmemDout;
        endcase
    end

    always_comb begin
        StoreWrEnMask = 4'b0000;
        if (GetOpcode(Instr) == OP_STORE) begin
            unique case (InstrT.SType.Funct3)
                F3_LW_SW:   StoreWrEnMask = 4'b1111;
                F3_LH_SH:   StoreWrEnMask = DmemByteOff[1] ? 4'b1100 : 4'b0011;
                F3_LB_SB:   unique case (DmemByteOff)
                                2'b00: StoreWrEnMask = 4'b0001;
                                2'b01: StoreWrEnMask = 4'b0010;
                                2'b10: StoreWrEnMask = 4'b0100;
                                2'b11: StoreWrEnMask = 4'b1000;
                            endcase
                default:    StoreWrEnMask = 4'b0000;
            endcase
        end
    end

    // Write back Mux
    always_comb begin
        unique case(RegWb)
        SEL_REG_WB_ALU:  RegWrData = AluOut;
        SEL_REG_WB_DMEM: RegWrData = LoadWbData;
        SEL_REG_WB_PC:   RegWrData = PcPlus4;
        SEL_REG_WB_IMM:  RegWrData = RegWrImm;
        default:         RegWrData = '0;
        endcase
    end

    // Control logic (Putting here instead of new module as it would change with pipelined implementation)
    assign ImmExt = GetImmediate(Instr);
    assign RegWrImm = ImmExt;
    assign Op2Sel   = ~(GetOpcode(Instr) == OP_MATH  | GetOpcode(Instr) == OP_BRANCH);
    assign DmemWr   =   GetOpcode(Instr) == OP_STORE;
    assign DmemWrEn = DmemWr ? StoreWrEnMask : 4'b0000;
    assign RegWrEn  = ~(GetOpcode(Instr) == OP_STORE | GetOpcode(Instr) == OP_BRANCH);
    assign RegWb    =  (GetOpcode(Instr) == OP_MATH  | GetOpcode(Instr) == OP_MATH_IMM | GetOpcode(Instr) == OP_AUIPC) ? SEL_REG_WB_ALU :
                      ((GetOpcode(Instr) == OP_LOAD) ? SEL_REG_WB_DMEM : 
                       (GetOpcode(Instr) == OP_LUI ? SEL_REG_WB_IMM : SEL_REG_WB_PC)); 
    assign AuipcSel =   GetOpcode(Instr) == OP_AUIPC;
    assign BrPcSel  =   GetOpcode(Instr) == OP_JAL   | ((GetOpcode(Instr) == OP_BRANCH) & BrTaken);
    assign JalPcSel =   GetOpcode(Instr) == OP_JALR;
endmodule
