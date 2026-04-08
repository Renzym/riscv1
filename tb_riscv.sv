`timescale 1ns/1ps

module tb_riscv;
    logic Clk;
    logic Reset;

    Riscv dut (
        .Clk   (Clk),
        .Reset (Reset)
    );

    always #5 Clk = ~Clk;

    initial begin
        Clk = 1'b0;
        Reset = 1'b1;
        repeat (2) @(posedge Clk);
        Reset = 1'b0;

        // Allow program to execute and settle in the JALR loop.
        repeat (25) @(posedge Clk);

        // Basic datapath/control checks for Stage 1.
        if (dut.RegfileInst.Regs[1] !== 32'd5) begin
            $fatal(1, "x1 mismatch. Expected 5, got %0d", dut.RegfileInst.Regs[1]);
        end
        if (dut.RegfileInst.Regs[2] !== 32'd10) begin
            $fatal(1, "x2 mismatch. Expected 10, got %0d", dut.RegfileInst.Regs[2]);
        end
        if (dut.RegfileInst.Regs[3] !== 32'd15) begin
            $fatal(1, "x3 mismatch. Expected 15, got %0d", dut.RegfileInst.Regs[3]);
        end
        if (dut.RegfileInst.Regs[4] !== 32'd15) begin
            $fatal(1, "x4 mismatch. Expected 15, got %0d", dut.RegfileInst.Regs[4]);
        end
        if (dut.RegfileInst.Regs[5] !== 32'd0) begin
            $fatal(1, "x5 mismatch. Branch/JAL skip failed, got %0d", dut.RegfileInst.Regs[5]);
        end
        if (dut.RegfileInst.Regs[6] !== 32'd28) begin
            $fatal(1, "x6 mismatch. AUIPC expected 28, got %0d", dut.RegfileInst.Regs[6]);
        end
        if (dut.RegfileInst.Regs[7] !== 32'd36) begin
            $fatal(1, "x7 mismatch. JAL link expected 36, got %0d", dut.RegfileInst.Regs[7]);
        end
        if (dut.RegfileInst.Regs[8] !== 32'h12345000) begin
            $fatal(1, "x8 mismatch. LUI expected 0x12345000, got 0x%08h", dut.RegfileInst.Regs[8]);
        end
        if (dut.RegfileInst.Regs[9] !== 32'd48) begin
            $fatal(1, "x9 mismatch. JALR link expected 48, got %0d", dut.RegfileInst.Regs[9]);
        end
        $display("PASS: Stage 1 smoke test passed.");
        $finish;
    end
endmodule
