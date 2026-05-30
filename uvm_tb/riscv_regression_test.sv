`ifndef RISCV_REGRESSION_TEST_SV
`define RISCV_REGRESSION_TEST_SV

class riscv_regression_test extends riscv_base_test;
    `uvm_component_utils(riscv_regression_test)

    function new(string name, uvm_component parent);
        super.new(name, parent);
    endfunction

    function void end_of_elaboration_phase(uvm_phase phase);
        super.end_of_elaboration_phase(phase);
        `uvm_info("TEST", "riscv_regression_test: Program.hex ISA regression", UVM_LOW)
    endfunction
endclass

`endif
