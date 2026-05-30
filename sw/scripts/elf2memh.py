#!/usr/bin/env python3
"""Convert raw binary or ELF section dump to Vivado $readmemh format (@word_addr)."""
from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path


def bin_to_memh(data: bytes, base_addr: int = 0, sparse: bool = False) -> list[str]:
    """Emit @addr lines matching this core's RAM indexing (PC[8:0] steps by 4)."""
    lines: list[str] = []
    if not data:
        return lines
    if len(data) % 4:
        data += b"\x00" * (4 - len(data) % 4)
    for off in range(0, len(data), 4):
        w = struct.unpack_from("<I", data, off)[0]
        if sparse and w == 0:
            continue
        addr = base_addr + off
        lines.append(f"@{addr:03x}")
        lines.append(f"{w:08x}")
    return lines


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("input", type=Path, help="raw .bin or path from objcopy -O binary")
    ap.add_argument("-o", "--output", type=Path, required=True)
    ap.add_argument("--base-addr", type=int, default=0, help="byte address of first instruction word")
    ap.add_argument("--sparse", action="store_true", help="omit all-zero words (matches hand-written Program.hex)")
    args = ap.parse_args()
    data = args.input.read_bytes()
    out_lines = bin_to_memh(data, args.base_addr, sparse=args.sparse)
    args.output.write_text("\n".join(out_lines) + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
