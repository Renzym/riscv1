`timescale 1ns/1ps

module tb_c_smoke;
    logic clk = 0;
    logic reset = 1;
    logic fault;
    Riscv #(.PROG_FILE("sw/build/c_smoke.hex"), .DATA_FILE("sw/build/c_smoke.data.hex")) dut
        (.Clk(clk), .Reset(reset), .Fault(fault));
    always #5 clk = ~clk;
    initial begin
        #1;
        // Poison zero-filled RAM above the low scratch area. BSS must be
        // cleared by crt0, rather than passing only because RAM started zero.
        for (int i = MemoryConfigPkg::DATA_ORIGIN / 4; i < 2**MemoryConfigPkg::DATA_MEM_ADDR_BITS; i++)
            if (dut.DataMemInst.RamArray[i] == 0)
                dut.DataMemInst.RamArray[i] = 32'ha5a5a5a5;
        repeat (2) @(posedge clk);
        @(negedge clk) reset = 0;
        repeat (500) @(posedge clk);
        @(negedge clk);
        if (fault !== 0 || dut.DataMemInst.RamArray[16] !== 32'h12345678)
            $fatal(1, "C runtime signature mismatch: %08h", dut.DataMemInst.RamArray[16]);
        $display("PASS: C startup, initialized data, BSS, rodata, stack and calls.");
        $finish;
    end
endmodule
