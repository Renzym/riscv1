`ifndef RISCV_BASE_TEST_SV
`define RISCV_BASE_TEST_SV

import riscv_pkg::*;

class riscv_base_test extends uvm_test;
    `uvm_component_utils(riscv_base_test)

    riscv_env env;
    virtual riscv_if vif;

    function new(string name, uvm_component parent);
        super.new(name, parent);
    endfunction

    function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(virtual riscv_if)::get(this, "", "vif", vif))
            `uvm_fatal("NOVIF", "virtual riscv_if not set")
        uvm_config_db#(virtual riscv_if)::set(this, "env.agent.driver",  "vif", vif);
        uvm_config_db#(virtual riscv_if)::set(this, "env.agent.monitor", "vif", vif);
        uvm_config_db#(virtual riscv_if)::set(this, "env.scoreboard",    "vif", vif);
        env = riscv_env::type_id::create("env", this);
    endfunction

    task run_phase(uvm_phase phase);
        phase.raise_objection(this);
        wait (vif.stimulus_done === 1'b1);
        #1step;
        `uvm_info("TEST", "Stimulus complete — checking register file", UVM_LOW)
        env.scoreboard.check_all();
        if (env.scoreboard.errors != 0)
            `uvm_fatal("TEST", $sformatf("Regression failed with %0d errors", env.scoreboard.errors))
        phase.drop_objection(this);
    endtask
endclass

`endif
