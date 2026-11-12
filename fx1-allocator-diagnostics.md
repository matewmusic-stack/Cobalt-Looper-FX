# FX1 SDRAM allocator diagnostics (experimental source patch)

This patch adds a read-only snapshot of the actual SDRAM allocator state after
stock FX1 construction, the Cobalt FX1 allocation, and the FX2 Shoegaze
allocation. It does not change allocation sizes, FX processing, boot code, or
the bootloader.

## Where the report is stored

A 32-byte report is published at backup-SRAM address `0x38800E80`. The M7
cleans the containing 32-byte D-cache line before publishing the valid magic.
The M4 Tools UI reads the report and displays the remaining contiguous bytes alongside the mod version as
`Cblt1.2 F:X.XMB`.

| Offset | Field | Meaning |
|---:|---|---|
| `0x00` | `magic` | `0x46584152` when the snapshot is valid |
| `0x04` | `cursor_before_fx1` | Allocator cursor after stock FX1 construction |
| `0x08` | `limit` | Allocator-reported limit |
| `0x0C` | `fx1_requested` | Cobalt FX1 allocation size; zero if preflight rejected it |
| `0x10` | `cursor_after_fx1` | Cursor after FX1 allocation attempt |
| `0x14` | `fx2_requested` | FX2 allocation size; zero if allocation failed |
| `0x18` | `cursor_after_fx2` | Cursor after FX2 allocation attempt |
| `0x1C` | `remaining` | Remaining bytes, capped at the existing `0xC3400000` safe allocation ceiling |

The report is diagnostic only. It does not yet establish that all reported
bytes are available to a phrase loop: the next allocation must preserve a
reserve for any other firmware consumers and be tested on the physical unit.

## Build and test status

- M7 `delay_m7.c`: compiled successfully with Clang targeting Cortex-M7.
- M4 `cm4_cpu.c` and included FX1 UI code: compiled successfully with Clang
targeting Cortex-M4 after disabling a Clang-only warning for existing naked
assembly function declarations.
- Existing Granular, delay-types, gate, Shoegaze, and Tape host tests: passed
under AddressSanitizer and UndefinedBehaviorSanitizer.
- Full release build: not completed. The repository uses GCC-specific absolute
Thumb branch assembly in `pc_m4.c`; Clang rejects those branches as out of
range. The required `arm-none-eabi-gcc` toolchain is not installed here.
- Unicorn firmware-emulator suite: not run because the Python `unicorn` package
is unavailable in this environment.
- No physical Bluebox runtime measurement or audio test has been performed.

## Next implementation gate

Read the displayed free-SDRAM figure from the Bluebox after a normal boot and
FX graph construction. Only then choose the Phrase Looper buffer capacity and
safety reserve. MIDI-clock/bar-boundary source tracing is also still required
before claiming sync-to-bar recording works. The existing FX1 modes and FX2
remain unchanged in this diagnostic patch.
