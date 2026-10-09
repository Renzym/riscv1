# A simulator can finish successfully without the test passing. Require both
# the expected completion marker and the absence of error/fatal reports.
proc require_sim_pass {log_file marker} {
    if {![file exists $log_file]} { error "Missing simulation log: $log_file" }
    set fh [open $log_file r]
    set result [read $fh]
    close $fh
    if {[regexp {UVM_(ERROR|FATAL)\s*:\s*[1-9]} $result] ||
        [regexp -line {^(UVM_(ERROR|FATAL)[ \t]+[^ \t:\r\n]|Fatal:|ERROR:)} $result] ||
        [string first $marker $result] < 0} {
        error "Regression failed or did not complete; inspect $log_file"
    }
}
