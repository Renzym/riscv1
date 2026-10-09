`ifndef RISCV_IF_SV
`define RISCV_IF_SV

interface riscv_if (input logic clk);
    logic        reset;
    logic        stimulus_done;
    logic [31:0] regs [32];

    initial stimulus_done = 1'b0;

endinterface

`endif
