module Alu #(
    param DATA_WIDTH=32,
    param INSTR_WIDTH=32
    ) (
    input  logic [DATA_WIDTH-1:0]   AluOp1,
    input  logic [DATA_WIDTH-1:0]   AluOp2,
    output logic [DATA_WIDTH-1:0]   AluOut,
    input  logic [INSTR_WIDTH-1:0]  Instr       // AluSel in diagram, rethink later
)

endmodule