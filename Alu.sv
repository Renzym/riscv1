`timescale 1ns/1ps

import Rv32iPkg::*;
module Alu #(
    parameter DATA_WIDTH=32,
    parameter INSTR_WIDTH=32
    ) (
    input  logic [DATA_WIDTH-1:0]   AluOp1,
    input  logic [DATA_WIDTH-1:0]   AluOp2,
    output logic [DATA_WIDTH-1:0]   AluOut,
    input  logic [INSTR_WIDTH-1:0]  Instr,       // AluSel in diagram, rethink later
    output logic                    BrTaken
);
    InstructionT InstrT = InstructionT'(Instr);
    // Subtract drives the adder for (rs1 - rs2) equality checks (BEQ/BNE) and R-type SUB/SLT/SLTU.
    logic Subtract;
    logic Overflow;
    logic [DATA_WIDTH-1:0] AddrOp2;
    logic [DATA_WIDTH-1:0] AddrOut;

    logic [4:0] Shamt;
    logic [DATA_WIDTH-1:0] ShiftOut;

    logic [DATA_WIDTH-1:0] LogicOut;
    logic [DATA_WIDTH-1:0] AndOut;
    logic [DATA_WIDTH-1:0] OrOut ;
    logic [DATA_WIDTH-1:0] XorOut;
    logic [DATA_WIDTH-1:0] SltOut;
    logic [DATA_WIDTH-1:0] SltuOut;

    logic IsZero    ;
    logic IsNegative;
    logic IsLessThan;
    logic IsLessThanUnsigned;
    //----------------------------------------------------------------------------------
    // Adder/Subtractor
    assign AddrOp2 = {DATA_WIDTH{Subtract}} ^ AluOp2;
    assign {Overflow, AddrOut} = AluOp1 + AddrOp2 + DATA_WIDTH'(Subtract);

    assign Subtract = ((GetOpcode(Instr) == OP_MATH) &&
                       ((InstrT.RType.Funct3 == F3_ADD_SUB && InstrT.RType.Funct7 == F7_ALT) ||
                        (InstrT.RType.Funct3 == F3_SLT) ||
                        (InstrT.RType.Funct3 == F3_SLTU))) ||
                      ((GetOpcode(Instr) == OP_BRANCH) &&
                       (InstrT.BType.Funct3 == F3_BEQ || InstrT.BType.Funct3 == F3_BNE));
    //----------------------------------------------------------------------------------
    // Shifter (shamt = low 5 bits of rs2 for R-type shifts, of imm for I-type shifts; both on AluOp2)
    always_comb begin
        Shamt = AluOp2[4:0];
        case (InstrT.RType.Funct3)
            F3_SLL:  ShiftOut = AluOp1 << Shamt;
            F3_SR:   ShiftOut = InstrT.RType.Funct7 == F7_ALT ? (AluOp1 >>> Shamt) : (AluOp1 >> Shamt);
            default: ShiftOut = '0;
        endcase
    end

    //----------------------------------------------------------------------------------
    // Logical Operations
    assign AndOut = AluOp1 & AluOp2;
    assign OrOut  = AluOp1 | AluOp2;
    assign XorOut = AluOp1 ^ AluOp2;
    assign SltOut = {{(DATA_WIDTH-1){1'b0}}, IsLessThan};
    assign SltuOut = {{(DATA_WIDTH-1){1'b0}}, IsLessThanUnsigned};

    always_comb begin
        unique case(InstrT.RType.Funct3)
        F3_AND: LogicOut = AndOut;
        F3_OR:  LogicOut = OrOut;
        F3_XOR: LogicOut = XorOut;
        F3_SLT: LogicOut = SltOut;
        F3_SLTU: LogicOut = SltuOut;
        default: LogicOut = '0;
        endcase
    end
    //----------------------------------------------------------------------------------
    // Mux to select between Arithmetic, Shift and Logic Units
    always_comb begin
        AluOut = '0;
        case (InstrT.RType.Funct3)
            F3_ADD_SUB:             AluOut = AddrOut;
            F3_SLL, F3_SR:          AluOut = ShiftOut;
            F3_AND, F3_OR, F3_XOR, F3_SLT, F3_SLTU: AluOut = LogicOut;
            default:                AluOut = AddrOut;
        endcase
    end
    //----------------------------------------------------------------------------------
    assign IsZero     = AddrOut == '0;
    assign IsNegative = AddrOut[DATA_WIDTH-1];
    assign IsLessThan = ($signed(AluOp1) < $signed(AluOp2));
    assign IsLessThanUnsigned = (AluOp1 < AluOp2);
    assign BrTaken    = ((InstrT.BType.Funct3 == F3_BEQ)  &  IsZero) |       // BEQ
                        ((InstrT.BType.Funct3 == F3_BNE)  & ~IsZero) |       // BNE
                        ((InstrT.BType.Funct3 == F3_BLT)  &  IsLessThan) |   // BLT
                        ((InstrT.BType.Funct3 == F3_BGE)  & ~IsLessThan) |   // BGE
                        ((InstrT.BType.Funct3 == F3_BLTU) &  IsLessThanUnsigned) |   // BLTU
                        ((InstrT.BType.Funct3 == F3_BGEU) & ~IsLessThanUnsigned);    // BGEU
endmodule
