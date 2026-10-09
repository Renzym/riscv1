#!/usr/bin/env python3
"""Convert a raw binary to dense, little-endian 32-bit $readmemh words."""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path


def bin_to_memh(data: bytes, base_addr: int = 0) -> list[str]:
    """Emit one word per line, padding any leading byte address with zeros."""
    if base_addr < 0 or base_addr % 4:
        raise ValueError("base address must be nonnegative and word aligned")
    lines: list[str] = ["00000000"] * (base_addr // 4)
    if not data:
        return lines
    if len(data) % 4:
        data += b"\x00" * (4 - len(data) % 4)
    for off in range(0, len(data), 4):
        w = struct.unpack_from("<I", data, off)[0]
        lines.append(f"{w:08x}")
    return lines


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("input", type=Path, help="raw .bin or path from objcopy -O binary")
    ap.add_argument("-o", "--output", type=Path, required=True)
    ap.add_argument("--base-addr", type=int, default=0, help="byte address of first instruction word")
    args = ap.parse_args()
    data = args.input.read_bytes()
    out_lines = bin_to_memh(data, args.base_addr)
    args.output.write_text("\n".join(out_lines) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
