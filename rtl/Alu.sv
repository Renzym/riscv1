`timescale 1ns/1ps

import Rv32iPkg::*;
module Alu #(
    parameter DATA_WIDTH = 32,
    parameter INSTR_WIDTH = 32
) (
    input  logic [DATA_WIDTH-1:0]  AluOp1,
    input  logic [DATA_WIDTH-1:0]  AluOp2,
    output logic [DATA_WIDTH-1:0]  AluOut,
    input  logic [INSTR_WIDTH-1:0] Instr,
    output logic                   BrTaken
);
    OpcodeE      Opc;
    Funct3T      Funct3;
    logic [6:0]  Funct7;

    logic Subtract;
    logic Overflow;
    logic [DATA_WIDTH-1:0] AddrOp2;
    logic [DATA_WIDTH-1:0] AddrOut;

    logic [4:0] Shamt;
    logic [DATA_WIDTH-1:0] ShiftOut;
    logic signed [DATA_WIDTH-1:0] SignedAluOp1;

    logic [DATA_WIDTH-1:0] LogicOut;
    logic [DATA_WIDTH-1:0] AndOut;
    logic [DATA_WIDTH-1:0] OrOut;
    logic [DATA_WIDTH-1:0] XorOut;
    logic [DATA_WIDTH-1:0] SltOut;
    logic [DATA_WIDTH-1:0] SltuOut;

    logic IsZero;
    logic IsNegative;
    logic IsLessThan;
    logic IsLessThanUnsigned;

    assign Opc    = GetOpcode(Instr);
    assign Funct3 = Instr[14:12];
    assign Funct7 = Instr[31:25];

    assign AddrOp2 = {DATA_WIDTH{Subtract}} ^ AluOp2;
    assign {Overflow, AddrOut} = AluOp1 + AddrOp2 + DATA_WIDTH'(Subtract);

    // Use raw opcode/funct fields (not union) so Vivado xsim does not propagate X on R-type view.
    assign Subtract = ((Opc == OP_MATH) &&
                       ((Funct3 == F3_ADD_SUB && Funct7 == F7_ALT) ||
                        (Funct3 == F3_SLT) ||
                        (Funct3 == F3_SLTU))) ||
                      ((Opc == OP_BRANCH) &&
                       (Funct3 == F3_BEQ || Funct3 == F3_BNE));

    always_comb begin
        Shamt = AluOp2[4:0];
        SignedAluOp1 = AluOp1;
        unique case (Funct3)
            F3_SLL:  ShiftOut = AluOp1 << Shamt;
            F3_SR:   begin
                if (Instr[30])
                    ShiftOut = SignedAluOp1 >>> Shamt;
                else
                    ShiftOut = AluOp1 >> Shamt;
            end
            default: ShiftOut = '0;
        endcase
    end

    assign AndOut  = AluOp1 & AluOp2;
    assign OrOut   = AluOp1 | AluOp2;
    assign XorOut  = AluOp1 ^ AluOp2;
    assign SltOut  = {{(DATA_WIDTH-1){1'b0}}, IsLessThan};
    assign SltuOut = {{(DATA_WIDTH-1){1'b0}}, IsLessThanUnsigned};

    always_comb begin
        unique case (Funct3)
            F3_AND:  LogicOut = AndOut;
            F3_OR:   LogicOut = OrOut;
            F3_XOR:  LogicOut = XorOut;
            F3_SLT:  LogicOut = SltOut;
            F3_SLTU: LogicOut = SltuOut;
            default: LogicOut = '0;
        endcase
    end

    always_comb begin
        AluOut = AddrOut;
        if (Opc == OP_MATH || Opc == OP_MATH_IMM) begin
            unique case (Funct3)
                F3_SLL, F3_SR:                          AluOut = ShiftOut;
                F3_AND, F3_OR, F3_XOR, F3_SLT, F3_SLTU: AluOut = LogicOut;
                default:                                AluOut = AddrOut;
            endcase
        end
    end

    assign IsZero               = AddrOut == '0;
    assign IsNegative           = AddrOut[DATA_WIDTH-1];
    assign IsLessThan           = ($signed(AluOp1) < $signed(AluOp2));
    assign IsLessThanUnsigned   = (AluOp1 < AluOp2);
    assign BrTaken              = (Opc == OP_BRANCH) && (
                                  ((Funct3 == F3_BEQ)  &  IsZero) |
                                  ((Funct3 == F3_BNE)  & ~IsZero) |
                                  ((Funct3 == F3_BLT)  &  IsLessThan) |
                                  ((Funct3 == F3_BGE)  & ~IsLessThan) |
                                  ((Funct3 == F3_BLTU) &  IsLessThanUnsigned) |
                                  ((Funct3 == F3_BGEU) & ~IsLessThanUnsigned));
endmodule
