`timescale 1ns/1ps

module Regfile #(
    parameter ADDR_WIDTH = 5,
    parameter DATA_WIDTH = 32
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
);

    localparam int REGFILE_DEPTH = 2**ADDR_WIDTH;
    logic [DATA_WIDTH-1:0] Regs [REGFILE_DEPTH];
    logic [REGFILE_DEPTH-1:0] WrDecVec;

    always_comb begin
        WrDecVec = '0;
        WrDecVec[WrAddr] = WrEn;
    end

    assign RdData1 = (RdAddr1 == '0) ? '0 : Regs[RdAddr1];
    assign RdData2 = (RdAddr2 == '0) ? '0 : Regs[RdAddr2];

    for (genvar i = 1; i < REGFILE_DEPTH; i++) begin : GenRegs
        always_ff @(posedge Clk) begin
            if (Reset)
                Regs[i] <= '0;
            else if (WrDecVec[i])
                Regs[i] <= WrData;
        end
    end
endmodule
