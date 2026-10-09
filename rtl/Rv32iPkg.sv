`timescale 1ns/1ps

package Rv32iPkg;

    // Opcode definitions (enum values in ALL_CAPS)
    typedef enum logic [6:0] {
        OP_LOAD      = 7'b0000011,
        OP_STORE     = 7'b0100011,
        OP_MATH      = 7'b0110011,  // R-type
        OP_MATH_IMM  = 7'b0010011,  // I-type
        OP_BRANCH    = 7'b1100011,
        OP_JAL       = 7'b1101111,
        OP_JALR      = 7'b1100111,
        OP_LUI       = 7'b0110111,
        OP_AUIPC     = 7'b0010111,
        OP_SYSTEM    = 7'b1110011,
        OP_FENCE     = 7'b0001111
    } OpcodeE;

    // Function3 field encodings (constants; values overlap across instruction classes)
    typedef logic [2:0] Funct3T;
    localparam Funct3T F3_ADD_SUB = 3'b000;
    localparam Funct3T F3_SLL     = 3'b001;
    localparam Funct3T F3_SLT     = 3'b010;
    localparam Funct3T F3_SLTU    = 3'b011;
    localparam Funct3T F3_XOR     = 3'b100;
    localparam Funct3T F3_SR      = 3'b101;  // SRL/SRA
    localparam Funct3T F3_OR      = 3'b110;
    localparam Funct3T F3_AND     = 3'b111;
    localparam Funct3T F3_BEQ     = 3'b000;
    localparam Funct3T F3_BNE     = 3'b001;
    localparam Funct3T F3_BLT     = 3'b100;
    localparam Funct3T F3_BGE     = 3'b101;
    localparam Funct3T F3_BLTU    = 3'b110;
    localparam Funct3T F3_BGEU    = 3'b111;
    localparam Funct3T F3_LB_SB   = 3'b000;
    localparam Funct3T F3_LH_SH   = 3'b001;
    localparam Funct3T F3_LW_SW   = 3'b010;
    localparam Funct3T F3_LBU     = 3'b100;
    localparam Funct3T F3_LHU     = 3'b101;

    // Function7 field encodings (enum values in ALL_CAPS)
    typedef enum logic [6:0] {
        F7_BASE     = 7'b0000000,
        F7_ALT      = 7'b0100000   // For SUB/SRA
    } Funct7E;

    // R-type instruction format (struct in CamelCase)
    typedef struct packed {
        logic [6:0] Funct7;
        logic [4:0] Rs2;
        logic [4:0] Rs1;
        Funct3T     Funct3;
        logic [4:0] Rd;
        OpcodeE     Opcode;
    } RTypeT;

    // I-type instruction format (struct in CamelCase)
    typedef struct packed {
        logic [11:0] Imm;
        logic [4:0]  Rs1;
        Funct3T      Funct3;
        logic [4:0]  Rd;
        OpcodeE      Opcode;
    } ITypeT;

    // S-type instruction format (stores)
    typedef struct packed {
        logic [6:0] ImmHi;
        logic [4:0] Rs2;
        logic [4:0] Rs1;
        Funct3T     Funct3;
        logic [4:0] ImmLo;
        OpcodeE     Opcode;
    } STypeT;

    // B-type instruction format (branches)
    typedef struct packed {
        logic       Imm12;
        logic [5:0] ImmHi;
        logic [4:0] Rs2;
        logic [4:0] Rs1;
        Funct3T     Funct3;
        logic [3:0] ImmLo;
        logic       Imm11;
        OpcodeE     Opcode;
    } BTypeT;

    // U-type instruction format (lui/auipc)
    typedef struct packed {
        logic [19:0] Imm;
        logic [4:0]  Rd;
        OpcodeE      Opcode;
    } UTypeT;

    // J-type instruction format (jal)
    typedef struct packed {
        logic       Imm20;
        logic [9:0] ImmHi;
        logic       Imm11;
        logic [7:0] ImmLo;
        logic [4:0] Rd;
        OpcodeE     Opcode;
    } JTypeT;

    // Instruction union - all possible instruction formats
    typedef union packed {
        logic [31:0] Raw;
        RTypeT       RType;
        ITypeT       IType;
        STypeT       SType;
        BTypeT       BType;
        UTypeT       UType;
        JTypeT       JType;
    } InstructionT;

    // Helper function to get opcode from raw instruction bits
    function automatic OpcodeE GetOpcode(logic [31:0] RawInstr);
        GetOpcode = OpcodeE'(RawInstr[6:0]);
    endfunction

    // This core implements RV32I without traps/CSRs. Reject reserved encodings
    // instead of letting them fall through to an arbitrary ALU operation.
    function automatic logic IsSupportedInstruction(logic [31:0] instr);
        logic [2:0] f3;
        logic [6:0] f7;
        f3 = instr[14:12];
        f7 = instr[31:25];
        IsSupportedInstruction = 1'b0;
        case (GetOpcode(instr))
            OP_MATH: begin
                if (f3 == F3_ADD_SUB || f3 == F3_SR)
                    IsSupportedInstruction = (f7 == F7_BASE || f7 == F7_ALT);
                else
                    IsSupportedInstruction = (f7 == F7_BASE);
            end
            OP_MATH_IMM: begin
                case (f3)
                    F3_SLL: IsSupportedInstruction = (f7 == F7_BASE);
                    F3_SR:  IsSupportedInstruction = (f7 == F7_BASE || f7 == F7_ALT);
                    default: IsSupportedInstruction = 1'b1;
                endcase
            end
            OP_LOAD: IsSupportedInstruction = (f3 == F3_LB_SB || f3 == F3_LH_SH ||
                                               f3 == F3_LW_SW || f3 == F3_LBU || f3 == F3_LHU);
            OP_STORE: IsSupportedInstruction = (f3 == F3_LB_SB || f3 == F3_LH_SH || f3 == F3_LW_SW);
            OP_BRANCH: IsSupportedInstruction = (f3 == F3_BEQ || f3 == F3_BNE ||
                         f3 == F3_BLT || f3 == F3_BGE || f3 == F3_BLTU || f3 == F3_BGEU);
            OP_JALR: IsSupportedInstruction = (f3 == 3'b000);
            OP_JAL, OP_LUI, OP_AUIPC: IsSupportedInstruction = 1'b1;
            OP_FENCE: IsSupportedInstruction = (f3 == 3'b000);
            default: ;
        endcase
    endfunction

    // Function to extract immediate value from instruction
    function automatic logic [31:0] GetImmediate(logic [31:0] RawInstr);
        InstructionT Instr;
        Instr = InstructionT'(RawInstr);
        case (GetOpcode(RawInstr))
            OP_LOAD, OP_MATH_IMM, OP_JALR:  // I-type
                GetImmediate = {{20{Instr.IType.Imm[11]}}, Instr.IType.Imm};
            
            OP_STORE:  // S-type
                GetImmediate = {{20{Instr.SType.ImmHi[6]}}, Instr.SType.ImmHi, Instr.SType.ImmLo};
            
            OP_BRANCH:  // B-type
                GetImmediate = {{19{Instr.BType.Imm12}}, Instr.BType.Imm12, 
                                Instr.BType.Imm11, Instr.BType.ImmHi, 
                                Instr.BType.ImmLo, 1'b0};
            
            OP_LUI, OP_AUIPC:  // U-type
                GetImmediate = {Instr.UType.Imm, 12'b0};
            
            OP_JAL:  // J-type
                GetImmediate = {{11{Instr.JType.Imm20}}, Instr.JType.Imm20,
                                Instr.JType.ImmLo, Instr.JType.Imm11,
                                Instr.JType.ImmHi, 1'b0};
            
            default:
                GetImmediate = 32'b0;
        endcase
    endfunction

endpackage
