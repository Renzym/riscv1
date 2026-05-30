# Quick check: run original tb_riscv in xsim (same memory images as UVM flow).
set repo_dir [file normalize [file join [file dirname [info script]] ..]]
cd $repo_dir
set proj_dir [file join $repo_dir sim proj_tb]
file mkdir $proj_dir
create_project -force riscv_tb_xsim $proj_dir -part xc7a35tcpg236-1
foreach f {Rv32iPkg.sv Alu.sv RamSp.sv Regfile.sv Riscv.sv tb_riscv.sv} {
    add_files [file join $repo_dir $f]
}
set_property top tb_riscv [get_filesets sim_1]
set_property -name {xsim.simulate.runtime} -value {5us} -objects [get_filesets sim_1]
set xsim_dir [file join $proj_dir riscv_tb_xsim.sim sim_1 behav xsim]
file mkdir $xsim_dir
foreach mem {Program.hex Data.hex} {
    file copy -force [file join $repo_dir $mem] [file join $xsim_dir $mem]
}
launch_simulation
run all
close_sim -force
close_project
