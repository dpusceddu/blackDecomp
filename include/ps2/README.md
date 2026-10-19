# Shared PS2 inline context

The shared context maintainer owns this directory and `config/shared_context.json`.
`tools/shared_context.py verify` runs the isolated build, preserves the HEAD source-address set,
and checks the manifest's real consumers against retail instructions and relocation targets.
The complete image must also remain identical. Verification details stay in ignored build output.

- `ee_types.h`: SN 2.95 target widths. `long` is 64 bits and `long long` is 128 bits;
  pointers and `int` are 32 bits. These are target assertions, not host or Sony compiler assumptions.
- `vector_storage.hpp` and `vu0.hpp`: existing movement storage and vector operations, with their
  historical `BlackGame` names preserved. `game/ai_vector.hpp` remains a compatible include.
  New consumers can include the shared headers without the full game class declarations.
- `matrix.hpp`: basis-vector direction and affine point transforms. Only xyz is defined; the W
  lane may be flags or unrelated payload. Matrix multiplication/inversion and axis-angle helpers
  are still unverified. A mathematical composition is not an established original inline recipe.
- `renderware_inline.h`: exact-backed flag invalidation, tolerance copy and pixel release.
  `kynapse/` supplies the underscore-key fallback, list/iterator prefixes and parameter owner getter.
  Their verification scopes are field-specific; unknown SDK/container fields remain unknown.

Use native fields when known. A reference-returning offset helper can evaluate its address early and
extend register lifetimes. Preserve helper-before-caller order, return widths and normal destructor
names: an assembler alias on a destructor can suppress automatic cleanup in SN 2.95.

VU operands use `j` constraints and names that cannot occur inside opcodes. Keep operation masks,
operand order, clobbers and spill shapes. `ReadXWord`/`Length3Word` deliberately read through a 32-bit
integer and `mtc1`; existing `BlackGame::X`/`Length3` retain their distinct exact-backed recipe.
Integer/128-bit and floating arguments occupy independent EE banks; source parameter order can still
change scheduling. Preserve the verified per-unit flags and assembler choice. All code is GCC 2.95
compatible; no C++11 language features are required.
