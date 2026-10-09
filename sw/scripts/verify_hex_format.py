#!/usr/bin/env python3
"""Verify the generated Program.hex format and, when available, build output."""
from __future__ import annotations

import re
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
GOLDEN = ROOT / "Program.hex"
GENERATED = ROOT / "sw" / "build" / "regression.hex"

WORD_RE = re.compile(r"^[0-9a-fA-F]{8}$")


def normalize(path: Path) -> list[str]:
    return [line.strip().lower() for line in path.read_text().splitlines() if line.strip()]


def verify_format(lines: list[str]) -> None:
    if not lines:
        raise ValueError("expected at least one 32-bit word")
    for idx, word_line in enumerate(lines):
        if not WORD_RE.match(word_line):
            raise ValueError(f"line {idx + 1}: invalid 32-bit word {word_line!r}")


def main() -> int:
    golden = normalize(GOLDEN)
    verify_format(golden)
    data = normalize(ROOT / "Data.hex")
    verify_format(data)
    cfg = json.loads((ROOT / "config/memory.json").read_text())
    if len(golden) != 1 << cfg['program_word_address_bits']:
        raise ValueError("Program.hex must contain exactly the configured program RAM word count")
    if len(data) != 1 << cfg['data_word_address_bits']:
        raise ValueError("Data.hex must contain exactly the configured data RAM word count")

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
        generated_data = ROOT / 'sw/build/regression.data.hex'
        if generated_data.exists() and normalize(generated_data) != data:
            print("MISMATCH: regression.data.hex differs from Data.hex")
            return 1
    else:
        print("OK: Program.hex format is valid (build/regression.hex not present)")

    return 0


if __name__ == "__main__":
    sys.exit(main())
