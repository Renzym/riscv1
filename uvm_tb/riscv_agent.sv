`ifndef RISCV_AGENT_SV
`define RISCV_AGENT_SV

class riscv_agent extends uvm_agent;
    `uvm_component_utils(riscv_agent)

    riscv_clock_driver driver;
    riscv_monitor       monitor;

    function new(string name, uvm_component parent);
        super.new(name, parent);
    endfunction

    function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        driver  = riscv_clock_driver::type_id::create("driver", this);
        monitor = riscv_monitor::type_id::create("monitor", this);
    endfunction

    function void connect_phase(uvm_phase phase);
        super.connect_phase(phase);
    endfunction
endclass

`endif
