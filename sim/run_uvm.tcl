# Vivado 2021.2+ UVM simulation for single-cycle RISC-V core.
# Usage (Windows cmd, from repo root):
#   vivado -mode batch -source sim/run_uvm.tcl
# Optional: build Program.hex first in WSL: cd sw && make install-hex

set repo_dir [file normalize [file join [file dirname [info script]] ..]]
source [file join $repo_dir sim check_sim_result.tcl]
source [file join $repo_dir sim check_memory_config.tcl]
require_memory_config $repo_dir
cd $repo_dir

set part_name xc7a35tcpg236-1
set proj_name riscv_uvm_sim
# Use a fresh subdir name if proj is locked; default proj/ can grow very large (~GB wdb).
set proj_dir [file join $repo_dir sim proj]

file mkdir $proj_dir
set xpr_file [file join $proj_dir ${proj_name}.xpr]
if {[file exists $xpr_file]} {
    open_project $xpr_file
} else {
    create_project $proj_name $proj_dir -part $part_name
}

set flist [file join $repo_dir sim filelist.f]
set fh [open $flist r]
while {[gets $fh line] >= 0} {
    set line [string trim $line]
    if {$line eq ""} continue
    if {[string index $line 0] eq "#"} continue
    add_files -norecurse [file join $repo_dir $line]
}
close $fh

set_property top tb_top_uvm [get_filesets sim_1]
set_property top_lib xil_defaultlib [get_filesets sim_1]
set_property -name {xsim.compile.xvlog.more_options} -value {-L uvm} -objects [get_filesets sim_1]
set_property -name {xsim.elaborate.xelab.more_options} -value {-L uvm} -objects [get_filesets sim_1]
set_property -name {xsim.simulate.runtime} -value {10us} -objects [get_filesets sim_1]
set_property -name {xsim.simulate.log_all_signals} -value {false} -objects [get_filesets sim_1]

update_compile_order -fileset sources_1
update_compile_order -fileset sim_1

# xsim cwd is .../behav/xsim — $readmemh paths in RamSp are relative to that directory.
set xsim_dir [file join $proj_dir ${proj_name}.sim sim_1 behav xsim]
file mkdir $xsim_dir
foreach mem_file {Program.hex Data.hex} {
    set src [file join $repo_dir $mem_file]
    if {![file exists $src]} {
        puts "ERROR: Missing memory image $src (build with: cd sw && make install-hex)"
        exit 1
    }
    file copy -force $src [file join $xsim_dir $mem_file]
}

set failed [catch {
    launch_simulation -simset sim_1
    close_sim -force
    require_sim_pass [file join $xsim_dir simulate.log] "All expected registers matched"
} message]
catch {close_sim -force}
close_project
if {$failed} { puts stderr $message; exit 1 }
