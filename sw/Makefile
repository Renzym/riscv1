# RISC-V bare-metal build for single-cycle core (Harvard ROM/RAM, 2 KiB each).
CROSS     ?= riscv64-unknown-elf
CC        := $(CROSS)-gcc
OBJCOPY   := $(CROSS)-objcopy
OBJDUMP   := $(CROSS)-objdump

ARCH      := -march=rv32i -mabi=ilp32
CFLAGS    := $(ARCH) -mno-relax -msmall-data-limit=0 -nostdlib -nostartfiles -ffreestanding -fno-builtin -O2 -Wall
LDFLAGS   := $(ARCH) -mno-relax -nostdlib -nostartfiles -T linker.ld -Wl,--gc-sections
PROG_WORDS := $(shell python3 -c 'import json; print(1 << json.load(open("../config/memory.json"))["program_word_address_bits"])')
DATA_WORDS := $(shell python3 -c 'import json; print(1 << json.load(open("../config/memory.json"))["data_word_address_bits"])')
DATA_ORIGIN := $(shell python3 -c 'import json; print(json.load(open("../config/memory.json"))["data_origin"])')

BUILD_DIR := build
PROG      ?= regression
SRC       := $(firstword $(wildcard programs/$(PROG).S programs/$(PROG).c))
ELF       := $(BUILD_DIR)/$(PROG).elf
BIN       := $(BUILD_DIR)/$(PROG).bin
HEX       := $(BUILD_DIR)/$(PROG).hex
DATA_BIN  := $(BUILD_DIR)/$(PROG).data.bin
DATA_IMG  := $(BUILD_DIR)/$(PROG).data.hex
STARTUP   := $(if $(filter %.c,$(SRC)),crt0.S)
ROOT_HEX  := ../Program.hex
DATA_HEX  := ../Data.hex

.PHONY: all clean install-hex dump check-toolchain check-config

all: $(HEX) $(DATA_IMG)

check-config:
	python3 scripts/generate_memory_config.py --check

check-toolchain:
	@command -v $(CC) >/dev/null || { \
	  echo "Missing $(CC). In WSL run: sudo apt install gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf"; \
	  exit 1; }

$(ELF): $(SRC) $(STARTUP) linker.ld memory_config.h ../config/memory.json | check-toolchain check-config
	@test -n "$(SRC)" || { echo "Missing programs/$(PROG).S or programs/$(PROG).c"; exit 1; }
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(STARTUP) $(SRC)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary -j .text $< $@

$(HEX): $(BIN) scripts/elf2memh.py ../config/memory.json
	python3 scripts/elf2memh.py $< -o $@ --words $(PROG_WORDS)

$(DATA_BIN): $(ELF)
	$(OBJCOPY) -O binary -j .data $< $@

$(DATA_IMG): $(DATA_BIN) scripts/elf2memh.py ../config/memory.json
	python3 scripts/elf2memh.py $< -o $@ --base-addr $(DATA_ORIGIN) --words $(DATA_WORDS)

install-hex: all
	cp $(HEX) $(ROOT_HEX)
	cp $(DATA_IMG) $(DATA_HEX)

dump: $(ELF)
	$(OBJDUMP) -d -M no-aliases,numeric $<

clean:
	rm -rf $(BUILD_DIR)
