`ifndef RISCV_IF_SV
`define RISCV_IF_SV

interface riscv_if (input logic clk);
    logic        reset;
    logic        stimulus_done;
    logic [31:0] regs [32];

    initial stimulus_done = 1'b0;

    clocking drv_cb @(posedge clk);
        output reset;
    endclocking

    clocking mon_cb @(posedge clk);
        input reset;
        input regs;
    endclocking

    modport drv_mp (clocking drv_cb, input clk);
    modport mon_mp (clocking mon_cb, input clk);
endinterface

`endif
