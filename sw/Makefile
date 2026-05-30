# RISC-V bare-metal build for single-cycle core (Harvard ROM/RAM, 2 KiB each).
CROSS     ?= riscv64-unknown-elf
CC        := $(CROSS)-gcc
OBJCOPY   := $(CROSS)-objcopy
OBJDUMP   := $(CROSS)-objdump

ARCH      := -march=rv32i -mabi=ilp32
CFLAGS    := $(ARCH) -nostdlib -nostartfiles -ffreestanding -O2 -Wall
LDFLAGS   := $(ARCH) -nostdlib -nostartfiles -T linker.ld -Wl,--gc-sections

BUILD_DIR := build
PROG      ?= regression
ASM       := programs/$(PROG).S
ELF       := $(BUILD_DIR)/$(PROG).elf
BIN       := $(BUILD_DIR)/$(PROG).bin
HEX       := $(BUILD_DIR)/$(PROG).hex
ROOT_HEX  := ../Program.hex
DATA_HEX  := ../Data.hex

.PHONY: all clean install-hex dump check-toolchain

all: $(HEX)

check-toolchain:
	@command -v $(CC) >/dev/null || { \
	  echo "Missing $(CC). In WSL run: sudo apt install gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf"; \
	  exit 1; }

$(ELF): $(ASM) linker.ld | check-toolchain
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(ASM)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(BIN)
	python3 scripts/elf2memh.py $< -o $@ --sparse

install-hex: $(HEX)
	cp $(HEX) $(ROOT_HEX)
	@test -f $(DATA_HEX) || printf '@000\n00000000\n' > $(DATA_HEX)

dump: $(ELF)
	$(OBJDUMP) -d $<

clean:
	rm -rf $(BUILD_DIR)
