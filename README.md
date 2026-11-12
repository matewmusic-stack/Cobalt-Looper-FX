# Cobalt-Looper-FX
1–2 bar Phrase Looper replacing the Granular mode in FX1

## FX1 Phrase Looper

The Phrase Looper occupies the existing FX1 Granular effect mode and keeps the same FX1 slot position and selector entry. It is not an additional effect slot and does not allocate a second effect beside the replaced mode.

The intended controls are:

- **Length:** 1 or 2 bars
- **Feedback:** optional recirculation, default 0%
- **Dry/Wet:** continuous blend
- **Sync:** arm capture for the next bar boundary when enabled; capture immediately when disabled
- **Stop:** stop loop playback
- **Clear:** empty and reset the phrase buffer

Capture automatically changes to playback after the selected phrase length. Playback repeats continuously. FX2 and the bootloader are outside the patch.

## Web patcher

The browser patcher is `patch_bluebox.html`; the GitHub Pages copy is `docs/index.html`. The selected firmware image is processed locally in the browser and is not uploaded.

- **Cobalt only** remains the currently verified build.
- **Cobalt + FX1 Phrase Looper** remains disabled until the compiled looper DSP/UI payload, hook changes, and matching firmware manifest are built and verified.
- The Looper buffer replaces the Granular buffer at the existing FX1 construction/allocation point, before the existing FX2 allocation. It must not be allocated after FX2.
- Buffer allocation is preflighted before calling the firmware bump allocator. If the requested buffer cannot fit, the Looper must remain unavailable without disturbing FX1's other modes or FX2.
- The bootloader is not patched. FX2 is not patched.

The emulator baseline in `tests/phrase-looper-emulator-baseline.json` validates the planned control/state behaviour; it is not target-firmware or hardware validation. The patcher must not label a Cobalt-only image as containing a working Phrase Looper.
