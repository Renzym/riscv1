`timescale 1ns/1ps
import uvm_pkg::*;
`include "uvm_macros.svh"
import riscv_pkg::*;
`include "riscv_if.sv"
`include "riscv_scoreboard.sv"

module tb_scoreboard_checks;
    logic clk = 0;
    riscv_if vif(clk);
    riscv_scoreboard scoreboard;
    initial begin
        scoreboard = new("scoreboard", null);
        scoreboard.vif = vif;
        scoreboard.expects.push_back('{5, 32'd0});
        // Deliberate mismatches must increment the scoreboard count; avoid
        // emitting errors which would obscure the verdict of this unit check.
        scoreboard.set_report_severity_action(UVM_ERROR, UVM_NO_ACTION);
        vif.regs[5] = 'x;
        #1;
        scoreboard.check_all();
        if (scoreboard.errors != 1) $fatal(1, "Scoreboard accepted X as zero");
        vif.regs[5] = 'z;
        #1;
        scoreboard.check_all();
        if (scoreboard.errors != 2) $fatal(1, "Scoreboard accepted Z as zero");
        vif.regs[5] = 0;
        #1;
        scoreboard.check_all();
        if (scoreboard.errors != 2) $fatal(1, "Scoreboard rejected valid zero");
        $display("PASS: scoreboard preserves X/Z and checks valid zero.");
        $finish;
    end
endmodule
