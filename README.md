# Cobalt-Looper-FX
1-2 Bar Phrase Looper FX on FX1

## Web patcher

The browser patcher is `patch_bluebox.html` and is published from `docs/index.html` for GitHub Pages. It runs locally in the browser: the selected firmware image is not uploaded.

- **Cobalt only** is the existing stable patch set.
- **Cobalt + FX1 Phrase Looper** is intentionally disabled until the complete compiled looper payload, hook patches, and matching firmware checksum manifest are available.
- The planned looper memory model is a separate optional SDRAM allocation after the stock FX1 and FX2 allocations have completed. If the safe contiguous-memory preflight fails, the looper must remain unavailable; existing FX1/FX2 allocations are not reduced or overwritten.
- The bootloader is not patched. FX2 is not patched.

The disabled option is deliberate: the current emulator and allocator model do not constitute a firmware implementation. The patcher must not label a Cobalt-only image as containing a working looper.
