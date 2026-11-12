from pathlib import Path

root = Path(__file__).resolve().parents[1]
header = (root / 'src/fx1_alloc_report.h').read_text()
m7 = (root / 'src/delay_m7.c').read_text()
m4 = (root / 'src/delay_m4.h').read_text()

assert '0x38800e80u' in header
assert 'sizeof(struct fx1_alloc_report)==32' in header
assert 'r->cursor_before_fx1=cursor' in m7
assert 'r->cursor_after_fx1=after_fx1' in m7
assert 'r->cursor_after_fx2=after_fx2' in m7
assert 'r->remaining=(after_fx2>=0xc0000000u && after_fx2<=safe_limit)?safe_limit-after_fx2:0u;' in m7
assert 'FX1_ALLOC_REPORT_MAGIC' in m7
assert 'Cblt1.2 F:' in m4
assert 'FX1_ALLOC_REPORT_MAGIC' in m4
print('PASS FX1 allocator report layout, publication, safe ceiling and UI readout')
