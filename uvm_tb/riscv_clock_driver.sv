`ifndef RISCV_CLOCK_DRIVER_SV
`define RISCV_CLOCK_DRIVER_SV

class riscv_clock_driver extends uvm_driver #(uvm_sequence_item);
    `uvm_component_utils(riscv_clock_driver)

    virtual riscv_if vif;
    int unsigned reset_cycles = 2;

    function new(string name, uvm_component parent);
        super.new(name, parent);
    endfunction

    function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(virtual riscv_if)::get(this, "", "vif", vif))
            `uvm_fatal("NOVIF", "virtual riscv_if not set")
        void'(uvm_config_db#(int unsigned)::get(this, "", "reset_cycles", reset_cycles));
    endfunction

    task run_phase(uvm_phase phase);
        // Reset is applied in riscv_base_test::run_phase to avoid parallel races.
        forever @(posedge vif.clk);
    endtask
endclass

`endif
