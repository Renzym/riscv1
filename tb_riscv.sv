`timescale 1ns/1ps

// Expected register values match Program.hex (see Program.hex.txt).
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

        // Enough cycles for full Program.hex through JAL x0,0 (see Program.hex.txt).
        repeat (150) @(posedge Clk);

        // Stage 1 smoke (Section A)
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
            $fatal(1, "x9 mismatch. JAL link expected 48, got %0d", dut.RegfileInst.Regs[9]);
        end

        // Byte / halfword loads (Sections C–D)
        if (dut.RegfileInst.Regs[14] !== 32'h000000ab) begin
            $fatal(1, "x14 LBU mismatch. Expected 0xAB, got 0x%08h", dut.RegfileInst.Regs[14]);
        end
        if (dut.RegfileInst.Regs[15] !== 32'h000000cd) begin
            $fatal(1, "x15 LBU mismatch. Expected 0xCD, got 0x%08h", dut.RegfileInst.Regs[15]);
        end
        if (dut.RegfileInst.Regs[16] !== 32'hffffffcd) begin
            $fatal(1, "x16 LB mismatch. Expected 0xFFFFFFCD, got 0x%08h", dut.RegfileInst.Regs[16]);
        end
        if (dut.RegfileInst.Regs[17] !== 32'hffffff80) begin
            $fatal(1, "x17 LB (-128) mismatch. Expected 0xFFFFFF80, got 0x%08h", dut.RegfileInst.Regs[17]);
        end
        if (dut.RegfileInst.Regs[21] !== 32'hffffbee0) begin
            $fatal(1, "x21 LH mismatch. Expected 0xFFFFBEE0, got 0x%08h", dut.RegfileInst.Regs[21]);
        end
        if (dut.RegfileInst.Regs[22] !== 32'h0000bee0) begin
            $fatal(1, "x22 LHU mismatch. Expected 0xBEE0, got 0x%08h", dut.RegfileInst.Regs[22]);
        end
        if (dut.RegfileInst.Regs[23] !== 32'hffffbee0) begin
            $fatal(1, "x23 LH high-half mismatch. Expected 0xFFFFBEE0, got 0x%08h", dut.RegfileInst.Regs[23]);
        end

        // Branches + ALU (Sections E–F)
        if (dut.RegfileInst.Regs[26] !== 32'd100) begin
            $fatal(1, "x26 mismatch. Branch sequence expected 100, got %0d", dut.RegfileInst.Regs[26]);
        end
        if (dut.RegfileInst.Regs[27] !== 32'd16) begin
            $fatal(1, "x27 SLLI mismatch. Expected 16, got %0d", dut.RegfileInst.Regs[27]);
        end
        if (dut.RegfileInst.Regs[28] !== 32'd1) begin
            $fatal(1, "x28 SUB mismatch. Expected 1, got %0d", dut.RegfileInst.Regs[28]);
        end

        $display("PASS: Program.hex regression (smoke + load/store + branch + ALU).");
        $finish;
    end
endmodule
