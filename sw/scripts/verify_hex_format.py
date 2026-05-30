#!/usr/bin/env python3
"""Verify the generated Program.hex format and, when available, build output."""
from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
GOLDEN = ROOT / "Program.hex"
GENERATED = ROOT / "sw" / "build" / "regression.hex"

ADDR_RE = re.compile(r"^@[0-9a-fA-F]+$")
WORD_RE = re.compile(r"^[0-9a-fA-F]{8}$")


def normalize(path: Path) -> list[str]:
    return [line.strip().lower() for line in path.read_text().splitlines() if line.strip()]


def verify_format(lines: list[str]) -> None:
    if len(lines) % 2:
        raise ValueError("expected address/word line pairs")

    last_addr = -1
    for idx in range(0, len(lines), 2):
        addr_line = lines[idx]
        word_line = lines[idx + 1]
        if not ADDR_RE.match(addr_line):
            raise ValueError(f"line {idx + 1}: invalid address marker {addr_line!r}")
        if not WORD_RE.match(word_line):
            raise ValueError(f"line {idx + 2}: invalid 32-bit word {word_line!r}")

        addr = int(addr_line[1:], 16)
        if addr % 4:
            raise ValueError(f"line {idx + 1}: address 0x{addr:x} is not word aligned")
        if addr <= last_addr:
            raise ValueError(f"line {idx + 1}: addresses must increase monotonically")
        last_addr = addr


def main() -> int:
    golden = normalize(GOLDEN)
    verify_format(golden)

    if GENERATED.exists():
        generated = normalize(GENERATED)
        verify_format(generated)
        if generated != golden:
            print("MISMATCH: sw/build/regression.hex differs from Program.hex")
            for i, (a, b) in enumerate(zip(generated, golden), start=1):
                if a != b:
                    print(f"  line {i}: generated {a!r} vs Program.hex {b!r}")
                    break
            else:
                print(f"  line count differs: generated={len(generated)} Program.hex={len(golden)}")
            return 1
        print("OK: generated regression.hex matches Program.hex")
    else:
        print("OK: Program.hex format is valid (build/regression.hex not present)")

    return 0


if __name__ == "__main__":
    sys.exit(main())
