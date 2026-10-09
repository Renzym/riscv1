`timescale 1ns/1ps

// Shared expectations with UVM; see REGRESSION_TESTS.md.
module tb_riscv;
    import riscv_pkg::*;
    logic Clk = 0;
    logic Reset = 1;
    logic Fault;
    Riscv dut (.Clk(Clk), .Reset(Reset), .Fault(Fault));
    always #5 Clk = ~Clk;

    initial begin
        repeat (2) @(posedge Clk);
        @(negedge Clk) Reset = 0;
        repeat (DEFAULT_RUN_CYCLES) @(posedge Clk);
        @(negedge Clk);
        foreach (REGRESSION_EXPECTS[i]) begin
            if (dut.RegfileInst.Regs[REGRESSION_EXPECTS[i].addr] !== REGRESSION_EXPECTS[i].value)
                $fatal(1, "x%0d mismatch: expected %08h, got %08h",
                    REGRESSION_EXPECTS[i].addr, REGRESSION_EXPECTS[i].value,
                    dut.RegfileInst.Regs[REGRESSION_EXPECTS[i].addr]);
        end
        if (Fault !== 0) $fatal(1, "Unexpected core fault");
        $display("PASS: Program.hex regression (33 self-checks, 21 registers).");
        $finish;
    end
endmodule
