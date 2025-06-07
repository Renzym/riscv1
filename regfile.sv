module Regfile #(
    param ADDR_WIDTH=5,
    param DATA_WIDTH=32,
    localparam REGFILE_DEPTH=2**ADDR_WIDTH
    ) (
    input  logic                  Clk,
    input  logic                  Reset,
    input  logic [ADDR_WIDTH-1:0] RdAddr1,
    input  logic [ADDR_WIDTH-1:0] RdAddr2,
    output logic [DATA_WIDTH-1:0] RdData1,
    output logic [DATA_WIDTH-1:0] RdData2,
    input  logic [ADDR_WIDTH-1:0] WrAddr,
    input  logic [DATA_WIDTH-1:0] WrData,
    input  logic                  WrEn
)

    logic [REGFILE_DEPTH-1:0][DATA_WIDTH-1:0] Regs;
    logic [REGFILE_DEPTH-1:0] WrDecVec;

    // Write demux
    always_comb begin
        WrDecVec = '0;
        WrDecVec[WrAddr] = WrEn;        
    end

    assign Regs[0] = '0;    // X0 always 0
    for(genvar i=1; i<REGFILE_DEPTH; i++) begin: GenRegs
        always_ff @(posedge Clk)
            if(Reset)           Regs[i] <= 0;
            else if(WrDecVec)   Regs[i] <= WrData;
    end

    assign RdData1 = Regs[RdAddr1];
    assign RdData2 = Regs[RdAddr2];
endmodule