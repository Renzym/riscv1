# Validate memory geometry on Windows without requiring Python on PATH.
proc read_config_text {path} {
    set fh [open $path r]
    set contents [read $fh]
    close $fh
    return $contents
}
proc require_memory_config {repo_dir} {
    set config [read_config_text [file join $repo_dir config memory.json]]
    foreach key {program_word_address_bits data_word_address_bits data_origin} {
        if {![regexp [format {"%s"\s*:\s*([0-9]+)} $key] $config ignored value]} {
            error "Missing or invalid memory configuration key: $key"
        }
        set values($key) $value
    }
    set prog_bits $values(program_word_address_bits)
    set data_bits $values(data_word_address_bits)
    set origin $values(data_origin)
    if {$prog_bits < 1 || $prog_bits > 20 || $data_bits < 1 || $data_bits > 20} {
        error "Memory word address widths must be in [1, 20]"
    }
    set prog_bytes [expr {4 << $prog_bits}]
    set data_bytes [expr {4 << $data_bits}]
    if {$origin % 4 || $origin >= $data_bytes} { error "Invalid data origin" }
    set pkg [read_config_text [file join $repo_dir rtl MemoryConfigPkg.sv]]
    set linker [read_config_text [file join $repo_dir sw linker.ld]]
    set header [read_config_text [file join $repo_dir sw memory_config.h]]
    foreach {text expected} [list \
        $pkg "PROG_MEM_ADDR_BITS = $prog_bits;" \
        $pkg "DATA_MEM_ADDR_BITS = $data_bits;" \
        $pkg "DATA_ORIGIN = $origin;" \
        $linker "rom (rx) : ORIGIN = 0, LENGTH = $prog_bytes" \
        $linker "ram (rw) : ORIGIN = $origin, LENGTH = [expr {$data_bytes - $origin}]" \
        $header "#define PROGRAM_MEMORY_BYTES ${prog_bytes}u" \
        $header "#define DATA_MEMORY_BYTES ${data_bytes}u" \
        $header "#define DATA_ORIGIN ${origin}u"] {
        if {[string first "$expected\n" "$text\n"] < 0} {
            error "Stale memory configuration. Run python3 sw/scripts/generate_memory_config.py"
        }
    }
}
