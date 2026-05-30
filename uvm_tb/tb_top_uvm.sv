`timescale 1ns/1ps

import uvm_pkg::*;
`include "uvm_macros.svh"

import riscv_pkg::*;

`include "riscv_if.sv"
`include "riscv_clock_driver.sv"
`include "riscv_monitor.sv"
`include "riscv_agent.sv"
`include "riscv_scoreboard.sv"
`include "riscv_env.sv"
`include "riscv_base_test.sv"
`include "riscv_regression_test.sv"

module tb_top_uvm;
    logic clk;
    logic reset;

    riscv_if riscv_vif(clk);

    Riscv dut (
        .Clk   (clk),
        .Reset (reset)
    );

    assign riscv_vif.reset = reset;

    genvar gi;
    generate
        for (gi = 0; gi < 32; gi++) begin : g_reg_probe
            assign riscv_vif.regs[gi] = dut.RegfileInst.Regs[gi];
        end
    endgenerate

    initial clk = 1'b0;
    always #5 clk = ~clk;
    assign reset = riscv_vif.reset;

    // Same reset/run timing as tb_riscv.sv (before UVM check phase).
    initial begin
        int unsigned run_cycles;
        run_cycles = DEFAULT_RUN_CYCLES;
        if (!$value$plusargs("RUN_CYCLES=%d", run_cycles)) begin end

        riscv_vif.reset = 1'b1;
        repeat (2) @(posedge clk);
        riscv_vif.reset = 1'b0;
        repeat (run_cycles) @(posedge clk);
        riscv_vif.stimulus_done = 1'b1;
    end

    initial begin
        string test_name;
        test_name = "riscv_regression_test";
        if (!$value$plusargs("UVM_TESTNAME=%s", test_name)) begin end

        uvm_config_db#(virtual riscv_if)::set(null, "uvm_test_top", "vif", riscv_vif);

        run_test(test_name);
    end
endmodule
