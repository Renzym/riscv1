# Run directed RTL, C runtime and four-state scoreboard checks in xsim.
# Build C images first: cd sw && make PROG=c_smoke
set repo_dir [file normalize [file join [file dirname [info script]] ..]]
cd $repo_dir
source [file join $repo_dir sim check_sim_result.tcl]
source [file join $repo_dir sim check_memory_config.tcl]
require_memory_config $repo_dir
set proj_dir [file join $repo_dir sim proj_checks]
set checks {tb_core_checks tb_c_smoke tb_scoreboard_checks tb_fault_report}
if {$argc > 0} {
    foreach name $argv {
        if {[lsearch -exact $checks $name] < 0} { error "Unknown directed bench: $name" }
    }
    set checks $argv
}
create_project -force riscv_checks $proj_dir -part xc7a35tcpg236-1
foreach f {rtl/MemoryConfigPkg.sv rtl/Rv32iPkg.sv rtl/Alu.sv rtl/RamSp.sv
           rtl/Regfile.sv rtl/Riscv.sv uvm_tb/riscv_pkg.sv
           sim/tb_core_checks.sv sim/tb_c_smoke.sv sim/tb_scoreboard_checks.sv sim/tb_fault_report.sv} {
    add_files -norecurse [file join $repo_dir $f]
}
set_property include_dirs [list [file join $repo_dir uvm_tb]] [get_filesets sim_1]
set_property -name {xsim.compile.xvlog.more_options} -value {-L uvm} -objects [get_filesets sim_1]
set_property -name {xsim.elaborate.xelab.more_options} -value {-L uvm} -objects [get_filesets sim_1]
set_property -name {xsim.simulate.runtime} -value {10us} -objects [get_filesets sim_1]
set_property -name {xsim.simulate.log_all_signals} -value {false} -objects [get_filesets sim_1]
set xsim_dir [file join $proj_dir riscv_checks.sim sim_1 behav xsim]
file mkdir [file join $xsim_dir sw build]
foreach image {c_smoke.hex c_smoke.data.hex} {
    file copy -force [file join $repo_dir sw build $image] [file join $xsim_dir sw build $image]
}
set failed [catch {
    foreach top $checks {
        set_property top $top [get_filesets sim_1]
        update_compile_order -fileset sim_1
        launch_simulation -simset sim_1
        close_sim -force
        if {$top == "tb_fault_report"} {
            set fh [open [file join $xsim_dir simulate.log] r]
            set result [read $fh]
            close $fh
            if {[string first "Core fault:" $result] < 0} { error "Missing expected core diagnostic" }
            puts "PASS: normal simulation reports core faults."
        } else {
            require_sim_pass [file join $xsim_dir simulate.log] "PASS:"
        }
    }
} message]
catch {close_sim -force}
close_project
if {$failed} { puts stderr $message; exit 1 }
