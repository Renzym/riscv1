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

    // Function3 field encodings (enum values in ALL_CAPS)
    typedef enum logic [2:0] {
        // Arithmetic
        F3_ADD_SUB  = 3'b000,
        F3_SLL      = 3'b001,
        F3_SLT      = 3'b010,
        F3_SLTU     = 3'b011,
        F3_XOR      = 3'b100,
        F3_SR       = 3'b101,  // SRL/SRA
        F3_OR       = 3'b110,
        F3_AND      = 3'b111,
        
        // Branches
        F3_BEQ      = 3'b000,
        F3_BNE      = 3'b001,
        F3_BLT      = 3'b100,
        F3_BGE      = 3'b101,
        F3_BLTU     = 3'b110,
        F3_BGEU     = 3'b111,
        
        // Load/Store
        F3_LB_SB    = 3'b000,
        F3_LH_SH    = 3'b001,
        F3_LW_SW    = 3'b010,
        F3_LBU      = 3'b100,
        F3_LHU      = 3'b101
    } Funct3E;

    // Function7 field encodings (enum values in ALL_CAPS)
    typedef enum logic [6:0] {
        F7_BASE     = 7'b0000000,
        F7_ALT      = 7'b0100000,  // For SUB/SRA
        F7_SYSTEM   = 7'b0000001   // For ECALL/EBREAK
    } Funct7E;

    // R-type instruction format (struct in CamelCase)
    typedef struct packed {
        logic [6:0] Funct7;
        logic [4:0] Rs2;
        logic [4:0] Rs1;
        Funct3E     Funct3;
        logic [4:0] Rd;
        OpcodeE     Opcode;
    } RTypeT;

    // I-type instruction format (struct in CamelCase)
    typedef struct packed {
        logic [11:0] Imm;
        logic [4:0]  Rs1;
        Funct3E      Funct3;
        logic [4:0]  Rd;
        OpcodeE      Opcode;
    } ITypeT;

    // S-type instruction format (stores)
    typedef struct packed {
        logic [6:0] ImmHi;
        logic [4:0] Rs2;
        logic [4:0] Rs1;
        Funct3E     Funct3;
        logic [4:0] ImmLo;
        OpcodeE     Opcode;
    } STypeT;

    // B-type instruction format (branches)
    typedef struct packed {
        logic       Imm12;
        logic [5:0] ImmHi;
        logic [4:0] Rs2;
        logic [4:0] Rs1;
        Funct3E     Funct3;
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
        
        // Helper function to get opcode
        function OpcodeE GetOpcode();
            return OpcodeE'(Raw[6:0]);
        endfunction
    } InstructionT;

    // Function to extract immediate value from instruction
    function automatic logic [31:0] GetImmediate(InstructionT Instr);
        unique case (Instr.GetOpcode())
            OP_LOAD, OP_MATH_IMM, OP_JALR:  // I-type
                return {{20{Instr.IType.Imm[11]}}, Instr.IType.Imm};
            
            OP_STORE:  // S-type
                return {{20{Instr.SType.ImmHi[6]}}, Instr.SType.ImmHi, Instr.SType.ImmLo};
            
            OP_BRANCH:  // B-type
                return {{19{Instr.BType.Imm12}}, Instr.BType.Imm12, 
                        Instr.BType.Imm11, Instr.BType.ImmHi, 
                        Instr.BType.ImmLo, 1'b0};
            
            OP_LUI, OP_AUIPC:  // U-type
                return {Instr.UType.Imm, 12'b0};
            
            OP_JAL:  // J-type
                return {{11{Instr.JType.Imm20}}, Instr.JType.Imm20,
                        Instr.JType.ImmHi, Instr.JType.Imm11,
                        Instr.JType.ImmLo, 1'b0};
            
            default:
                return 32'b0;
        endcase
    endfunction

endpackage