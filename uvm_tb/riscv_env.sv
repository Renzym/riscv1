`ifndef RISCV_ENV_SV
`define RISCV_ENV_SV

class riscv_env extends uvm_env;
    `uvm_component_utils(riscv_env)

    riscv_agent      agent;
    riscv_scoreboard scoreboard;

    function new(string name, uvm_component parent);
        super.new(name, parent);
    endfunction

    function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        agent      = riscv_agent::type_id::create("agent", this);
        scoreboard = riscv_scoreboard::type_id::create("scoreboard", this);
    endfunction
endclass

`endif
