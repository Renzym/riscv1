# Unit checks for pass/failure interpretation without launching a simulator.
source [file join [file dirname [info script]] check_sim_result.tcl]
source [file join [file dirname [info script]] check_memory_config.tcl]
require_memory_config [file normalize [file join [file dirname [info script]] ..]]
set channel [file tempfile log_file]
close $channel
foreach {contents should_pass} {
    {PASS: UVM_ERROR :    0
UVM_FATAL :    0} 1
    {PASS: UVM_ERROR :    1} 0
    {PASS:
UVM_ERROR @ 1: reporter [TEST] mismatch} 0
    {PASS:
UVM_FATAL file.sv(1) @ 1: reporter [TEST] mismatch} 0
    {PASS:
Fatal: mismatch} 0
    {Simulation ran for 10us} 0
} {
    set channel [open $log_file w]
    puts $channel $contents
    close $channel
    set accepted [expr {![catch {require_sim_pass $log_file "PASS:"}]}]
    if {$accepted != $should_pass} { error "Wrong verdict for: $contents" }
}
file delete $log_file
puts "PASS: simulator result interpretation"
