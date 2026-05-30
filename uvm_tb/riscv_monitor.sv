`ifndef RISCV_MONITOR_SV
`define RISCV_MONITOR_SV

class riscv_monitor extends uvm_monitor;
    `uvm_component_utils(riscv_monitor)

    virtual riscv_if vif;
    uvm_analysis_port #(uvm_sequence_item) ap;

    function new(string name, uvm_component parent);
        super.new(name, parent);
        ap = new("ap", this);
    endfunction

    function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(virtual riscv_if)::get(this, "", "vif", vif))
            `uvm_fatal("NOVIF", "virtual riscv_if not set")
    endfunction

    task run_phase(uvm_phase phase);
        forever @(posedge vif.clk);
    endtask
endclass

`endif
