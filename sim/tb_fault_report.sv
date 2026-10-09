`timescale 1ns/1ps

// Expected failure: normal simulation must terminate on an invalid instruction.
module tb_fault_report;
    logic clk = 0;
    logic reset = 1;
    logic fault;
    Riscv #(.PROG_FILE(""), .DATA_FILE("")) dut
        (.Clk(clk), .Reset(reset), .Fault(fault));
    always #5 clk = ~clk;
    initial begin
        repeat (2) @(posedge clk);
        @(negedge clk) reset = 0;
        #100;
        $fatal(1, "Expected core diagnostic was not emitted");
    end
endmodule
