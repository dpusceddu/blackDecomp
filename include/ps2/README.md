# Shared PS2 inline context

The shared context maintainer owns this directory and `config/SLUS_213.76/ps2_header_evidence.json`.
`tools/maint/shared_context.py verify` runs the build, preserves the HEAD source-address set,
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
- `recovered_types.h` and `prototypes.h`: hand-maintained, UNVERIFIED recovered structures and the signatures (under the image's
  `func_XXXXXXXX` names) that use them; the m2c context and the automatic drafts read both. `recovered_types.h` is all a
  translation unit needs for the types; include `prototypes.h` to also get the declarations.
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

The exact 440-byte envelope registration caller at 0x1ED9C8 verifies the scoped argument order
`(receiver, field, label, group, path, control, float, float, control)`. A floats-first declaration
leaves 31 differing instructions despite identical EE banks. The final zero control can be declared
as int, bool or byte without changing this caller, so its width remains unverified. The caller also
owns seven DSP label strings; body equality alone did not establish full-build placement.

A controlled SN GCC 2.95.3 build 1.36 probe with `-O2 -G0 -snas` shows that a member
returning a 12-byte POD (three 32-bit words) receives the hidden output pointer in A0,
`this` in A1 and an explicit Actor pointer in A2. A free function returning that POD with
explicit receiver and Actor pointers uses the same order. An explicit output-parameter
method instead keeps `this` in A0, output in A1 and Actor in A2. These recipes are distinct;
this control does not establish an ABI for non-POD classes or other compiler versions.

The exact SN 1.36 `-O2 -G0 -snas` consumer `CGraphManager::Configure` at 0x2F2660
also verifies a native `double` return from `atof` (0x35E730), float-to-double `fptodp`
(0x291F58), double multiply `dpmul` (0x2914D0), and double-to-float `dptofp` (0x291C68).
Its coverage-distance expression retains an explicit `float` local before use; the unit binds
these software helpers to their original addresses. This is a scoped native-double recipe,
not verification of every floating operation or another compiler's ABI.

`vu0_math.h` exposes the C-compatible arithmetic blocks used by `vu0.hpp`.
Add, subtract, multiply, one-x, sum-xyz, sqrt-x and the animation quaternion and translation recipes each have two exact
source consumers; scale, cross and the two normalizations are provisional. Isolated, register-renamed dataflow equality
does not prove physical allocation or surrounding scheduling. XYZ writes do not define W;
normalize-with-copy and normalize-without-copy are distinct recipes. ACC and Q
are consumed inside one assembly block; MAC/status flags are not exported.

These generic names do not identify an original class. Game vector values have
128-bit argument/storage evidence; RenderWare's matrix kernels also preserve
flag/payload lanes that generic game affine transforms leave unspecified. Similar
arithmetic does not establish interchangeable types, load order or aliasing.

`vu0_quaternion.hpp` reconstructs a different animation macro family: its
Hamilton product uses VF1..4 at ten sites in six functions; the companion
translation add uses VF9..11 and preserves destination W. The wrappers declare
VF and memory clobbers and require ACC/MAC/status to be dead across calls.
Two full source consumers verify this fixed-register recipe; it is not a claim
that the generic `j`-allocated helpers choose those registers or identify an SDK.
