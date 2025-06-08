import Rv32iPkg::*;
module Alu #(
    param DATA_WIDTH=32,
    param INSTR_WIDTH=32
    ) (
    input  logic [DATA_WIDTH-1:0]   AluOp1,
    input  logic [DATA_WIDTH-1:0]   AluOp2,
    output logic [DATA_WIDTH-1:0]   AluOut,
    input  logic [INSTR_WIDTH-1:0]  Instr       // AluSel in diagram, rethink later
)
    InstructionT InstrT = InstructionT'(Instr);
    //----------------------------------------------------------------------------------
    // Adder/Subtractor
    logic Subtract;
    logic Overflow;
    logic [DATA_WIDTH-1:0] AddrOp2;
    logic [DATA_WIDTH-1:0] AddrOut;
    assign AddrOp2 = {DATA_WIDTH{Subtract}} ^ AluOp2;
    assign {Overflow, AddrOut} = AluOp1 + AddrOp2 + Subtract;

    assign Subtract = (InstrT.GetOpcode() == OP_MATH && 
                      InstrT.RType.Funct3 == F3_ADD_SUB && 
                      InstrT.RType.Funct7 == F7_ALT);
    //----------------------------------------------------------------------------------
    // Shifter
    logic [4:0] Shamt;
    logic [DATA_WIDTH-1:0] ShiftOut;
    
    always_comb begin
        // TODO: I think we can probably use AluOp2's LSBs instead of determining here, Rethink
        // Shamt = '0;
        // if      (InstrT.GetOpcode() == OP_MATH)     Shamt = AluOp2[4:0];            // R-type shifts
        // else if (InstrT.GetOpcode() == OP_MATH_IMM) Shamt = InstrT.IType.Imm[4:0];  // I-type shifts
        Shamt = AluOp2[4:0];
        case (InstrT.RType.Funct3)
            F3_SLL:  ShiftOut = AluOp1 << Shamt;
            F3_SRL:  ShiftOut = AluOp1 >> Shamt;
            F3_SRA:  ShiftOut = AluOp1 >>> Shamt;
            default: ShiftOut = '0;
        endcase
    end

    //----------------------------------------------------------------------------------
    // Logical Operations
    logic [DATA_WIDTH-1:0] LogicOut;
    logic [DATA_WIDTH-1:0] AndOut;
    logic [DATA_WIDTH-1:0] OrOut ;
    logic [DATA_WIDTH-1:0] XorOut;
    assign AndOut = AluOp1 & AluOp2;
    assign OrOut  = AluOp1 | AluOp2;
    assign XorOut = AluOp1 ^ AluOp2;

    always_comb begin
        unique case(InstrT.RType.Funct3)
        F3_AND: LogicOut = AndOut;
        F3_OR:  LogicOut = OrOut;
        F3_XOR: LogicOut = XorOut;
        endcase
    end
    //----------------------------------------------------------------------------------
    // Mux to select between Arithmetic, Shift and Logic Units
    always_comb begin
        AluOut = '0;
        case (instr.RType.Funct3)
            F3_ADD_SUB:             AluOut = AddrOut;
            F3_SLL, F3_SRL, F3_SRA: AluOut = ShiftOut;
            F3_AND, F3_OR, F3_XOR:  AluOut = LogicOut;
        endcase
    end
endmodule
