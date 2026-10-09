`timescale 1ns/1ps

// Directed tests deliberately fault the core, so disable automatic reporting
// and inspect Fault, PC, registers and memory instead.
module tb_core_checks;
    logic clk = 0;
    logic reset = 1;
    logic fault;
    Riscv #(.PROG_MEM_ADDR_BITS(4), .DATA_MEM_ADDR_BITS(4),
        .PROG_FILE(""), .DATA_FILE(""), .REPORT_FAULTS(0)) dut
        (.Clk(clk), .Reset(reset), .Fault(fault));
    always #5 clk = ~clk;

    task automatic prepare(input logic [31:0] instruction);
        @(negedge clk) reset = 1;
        dut.ProgMemInst.RamArray[0] = instruction;
        dut.ProgMemInst.RamArray[1] = 32'h0000006f;
        dut.DataMemInst.RamArray[0] = 32'h12345678;
        repeat (2) @(posedge clk);
        @(negedge clk) reset = 0;
        #1;
    endtask

    task automatic reject(input logic [31:0] instruction);
        prepare(instruction);
        if (fault !== 1) $fatal(1, "Instruction %08h did not fault", instruction);
        repeat (2) @(negedge clk);
        if (dut.Pc !== 0 || dut.RegfileInst.Regs[3] !== 0 ||
            dut.DataMemInst.RamArray[0] !== 32'h12345678)
            $fatal(1, "Fault failed to suppress side effects for %08h", instruction);
    endtask

    initial begin
        reject(32'h00000000); // unknown opcode
        reject(32'h050005b3); // former regression's reserved funct7
        reject(32'h022081b3); // MUL is outside RV32I
        reject(32'h02001193); // reserved SLLI upper immediate
        reject(32'h02005193); // reserved SRLI/SRAI upper immediate
        reject(32'h00003183); // reserved load width
        reject(32'h00303023); // reserved store width
        reject(32'h00002063); // reserved branch funct3
        reject(32'h000011e7); // invalid JALR funct3
        reject(32'h00000073); // ECALL unsupported
        reject(32'h00202183); // LW at byte 2
        reject(32'h00101183); // LH at byte 1
        reject(32'h00105183); // LHU at byte 1
        reject(32'h00302123); // SW at byte 2
        reject(32'h003010a3); // SH at byte 1
        reject(32'h04002183); // load at data RAM limit (64 bytes)
        reject(32'h04302023); // store at data RAM limit
        reject(32'h002001ef); // JAL target 2: no compressed ISA
        reject(32'h00000163); // taken BEQ target 2

        // Valid word at the final data RAM entry: index 15, byte address 60.
        prepare(32'h03c02183); // LW x3,60(x0)
        dut.DataMemInst.RamArray[15] = 32'h89abcdef;
        @(negedge clk);
        if (fault !== 0 || dut.RegfileInst.Regs[3] !== 32'h89abcdef)
            $fatal(1, "Last valid data word failed");

        // An odd JALR source must produce aligned PC 4 and link 8.
        prepare(32'h00500193); // ADDI x3,x0,5
        dut.ProgMemInst.RamArray[1] = 32'h000180e7; // JALR x1,0(x3)
        repeat (2) @(negedge clk);
        if (fault !== 0 || dut.Pc !== 4 || dut.RegfileInst.Regs[1] !== 8)
            $fatal(1, "JALR odd-target masking/link failed");

        // Fetch at the first address beyond program RAM must halt, not wrap.
        prepare(32'h0400006f); // JAL x0,64
        @(negedge clk);
        if (fault !== 1 || dut.Pc !== 64) $fatal(1, "Out-of-range fetch did not fault");
        @(negedge clk);
        if (dut.Pc !== 64) $fatal(1, "Out-of-range fetch wrapped");

        prepare(32'h03c0006f); // JAL x0,60: last valid instruction word
        dut.ProgMemInst.RamArray[15] = 32'h0000006f;
        repeat (2) @(negedge clk);
        if (fault !== 0 || dut.Pc !== 60) $fatal(1, "Last valid instruction word failed");

        // Reset during execution clears registers and restarts at PC zero.
        prepare(32'h00118193); // ADDI x3,x3,1
        dut.ProgMemInst.RamArray[1] = 32'hffdff06f; // JAL x0,-4
        repeat (6) @(negedge clk);
        if (dut.RegfileInst.Regs[3] !== 3) $fatal(1, "Reset test setup failed");
        reset = 1;
        @(negedge clk);
        if (dut.Pc !== 0 || dut.RegfileInst.Regs[3] !== 0 || dut.RegfileInst.Regs[0] !== 0)
            $fatal(1, "Reset during execution failed");
        reset = 0;
        @(negedge clk);
        if (dut.RegfileInst.Regs[3] !== 1) $fatal(1, "Execution did not restart after reset");
        $display("PASS: directed decode, fault isolation, alignment, bounds, JALR and reset checks.");
        $finish;
    end
endmodule
