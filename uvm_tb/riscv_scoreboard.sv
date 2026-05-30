`ifndef RISCV_SCOREBOARD_SV
`define RISCV_SCOREBOARD_SV

import riscv_pkg::*;

class riscv_scoreboard extends uvm_scoreboard;
    `uvm_component_utils(riscv_scoreboard)

    virtual riscv_if vif;
    reg_expect_t expects[$];
    int unsigned errors;

    function new(string name, uvm_component parent);
        super.new(name, parent);
        errors = 0;
    endfunction

    function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(virtual riscv_if)::get(this, "", "vif", vif))
            `uvm_fatal("NOVIF", "virtual riscv_if not set")
        for (int i = 0; i < REGRESSION_N; i++)
            expects.push_back(REGRESSION_EXPECTS[i]);
    endfunction

    function void check_all();
        reg_expect_t exp;
        bit [31:0] actual;
        foreach (expects[i]) begin
            string rname;
            exp = expects[i];
            rname = reg_name(exp.addr);
            actual = vif.regs[exp.addr];
            if (actual !== exp.value) begin
                errors++;
                `uvm_error("REGCHK", $sformatf("%s mismatch: expected 0x%08x (%0d), got 0x%08x (%0d)",
                    rname, exp.value, exp.value, actual, actual))
            end else begin
                `uvm_info("REGCHK", $sformatf("%s OK (0x%08x)", rname, actual), UVM_MEDIUM)
            end
        end
        if (errors == 0)
            `uvm_info("REGCHK", "All expected registers matched", UVM_LOW)
    endfunction
endclass

`endif
