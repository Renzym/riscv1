"""Checks for image conversion, capacity enforcement and configuration drift."""
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch
from pathlib import Path

from elf2memh import bin_to_memh
from verify_hex_format import verify_format
import generate_memory_config

ROOT = Path(__file__).resolve().parents[2]


class MemoryToolsTests(unittest.TestCase):
    def test_little_endian_and_zero_words(self):
        self.assertEqual(bin_to_memh(bytes.fromhex('7856341200000000')), ['12345678', '00000000'])

    def test_partial_word(self):
        self.assertEqual(bin_to_memh(bytes.fromhex('abcd')), ['0000cdab'])

    def test_base_padding(self):
        self.assertEqual(bin_to_memh(bytes.fromhex('78563412'), 8), ['00000000', '00000000', '12345678'])

    def test_invalid_base(self):
        for base in (-4, 1, 3):
            with self.assertRaises(ValueError):
                bin_to_memh(b'1234', base)

    def test_empty_input(self):
        self.assertEqual(bin_to_memh(b''), [])

    def test_plain_hex_format(self):
        verify_format(['12345678', 'ABCDEF00'])
        for lines in ([], ['@000'], ['123'], ['xxxxxxxx']):
            with self.assertRaises(ValueError):
                verify_format(lines)

    def test_capacity_and_overflow(self):
        with tempfile.TemporaryDirectory() as directory:
            src, out = Path(directory) / 'in.bin', Path(directory) / 'out.hex'
            src.write_bytes(b'1234')
            command = [sys.executable, str(ROOT / 'sw/scripts/elf2memh.py'), str(src), '-o', str(out)]
            subprocess.run(command + ['--words', '2'], check=True)
            self.assertEqual(out.read_text().splitlines(), ['34333231', '00000000'])
            previous = out.read_text()
            rejected = subprocess.run(command + ['--base-addr', '8', '--words', '2'], capture_output=True)
            self.assertNotEqual(rejected.returncode, 0)
            self.assertIn(b'exceeds configured RAM capacity', rejected.stderr)
            self.assertEqual(out.read_text(), previous)

    def test_configuration_matches_generated_files(self):
        subprocess.run([sys.executable, str(ROOT / 'sw/scripts/generate_memory_config.py'), '--check'], check=True)

    def test_configuration_drift_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for folder in ('config', 'rtl', 'sw'):
                (root / folder).mkdir()
            (root / 'config/memory.json').write_text((ROOT / 'config/memory.json').read_text())
            with patch.object(generate_memory_config, 'ROOT', root):
                with patch.object(sys, 'argv', ['generate_memory_config.py']):
                    generate_memory_config.main()
                with patch.object(sys, 'argv', ['generate_memory_config.py', '--check']):
                    generate_memory_config.main()
                    (root / 'sw/linker.ld').write_text('stale linker map')
                    with self.assertRaises(SystemExit) as rejected:
                        generate_memory_config.main()
                    self.assertEqual(rejected.exception.code, 1)


if __name__ == '__main__':
    unittest.main()
