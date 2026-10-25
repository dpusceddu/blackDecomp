# History

Condensed results of the phases and studies, in order, with the numbers that still matter. Measurements are on USA retail
(`SLUS_213.76`); "bytes" are `.text` spans from `ninja progress`, including alignment. The current state is in
[status.md](status.md). Tool names refer to the layout of the time. One-off studies are no longer in the tree; their code is in the Git history of `tools/studies/`.

## Phase 0: inputs (see [inputs.md](inputs.md))

Nine disc images triaged. No executable has symbols, debug sections or compiler banners. PAL, Korean and Japanese
retail are the USA code plus small changes (member offsets shift by 0x80 in about a fifth of the code); the beta and demos
are earlier builds and only give naming and ordering hints. The USA retail executable became the target. SN GCC
2.95.3 build 1.36 (`ee-gcc2.95.3-136`, `-O2 -G0 -snas`) is the game compiler.

## Phase 1: identical rebuild

`ninja` rebuilds the boot ELF byte for byte for all five retail images. Facts that shaped the design:

- GNU `ld` cannot write the retail container, so `tools/build/pack_elf.py` re-packs the linked sections from
  `build/<GAME_ID>/layout.json`; DVP overlays and `.vutext`/`.vudata` are extracted payloads.
- One ld statement per object is quadratic (did not finish in 15 minutes for 12,000 objects): input sections are named
  `<section>.<address>` and placed by `SORT_BY_NAME`.
- 200 NOPs inserted into one function relink with every symbolic reference moved (the image is shiftable); the
  exceptions are raw numbers in data that look like addresses.

## Phase 2: one object per function, symbols, first sources

- 11,775 function objects, cached by input hash: a build from nothing takes about 40 s on a fast machine, one changed unit
  about 15 s.
- Constants travel with their function (74 % of `.rodata`, 88 % of `.lit4` migrate); `.gcc_except_table` belongs to whole
  object files and mostly stays shared.
- Function boundaries: 1,169 orphan `<instruction>; nop` pieces sit between functions and are not code of either
  neighbour; `tools/build/boundaries.py` splits them off (123 functions that splat had fused with a piece now match
  individually) and adds the `__CTOR_LIST__` entries as starts.
- An earlier analysis of the executable listed 9,946 functions (268 with a recovered name); splat finds 1,832 more starts. The
  names are now `alias` lines in `config/SLUS_213.76/symbols.txt` and the signatures live in `include/ps2/prototypes.h`.
- The first sources were ported from an unpublished companion project that reconstructs the Xbox build: 191 PS2-exact Kynapse
  bodies and 65 game functions (0.7 % of `.text`). The early sources were imported once from that project; the importers are
  not part of this repository, and the imported files keep a header comment naming their origin.

## Phase 3: translation units

`tools/build/tus.py` combines unwind-frame groups (822 CIE groups, exact object boundaries), the constructor list (116 entries,
certain TU ends), library strings and code style, data-order joins and call edges. Result: 599 object TUs of two or more
functions (120 exact), 1,586 isolated functions and 852 link-once sections, with library ranges, compiler and flags.
Orphan pieces, alignment and cross-build shifts do not mark boundaries. The Sony libraries (`sd` register saves, blocks
`0x28fab0-0x2a5038`, `0x355278-0x35c308`, `0x367e28-0x372d68`) match with `ee-gcc2.9-991111-01 -O2 -G0` and never
with SN 1.36. a former `tools/regroup.py` merged the units of a TU into one file (`-ffunction-sections`, assembly kept in place).
Evidence: [tus.md](tus.md).

## Phase 4: automatic pipeline

`tools/autodecomp.py`: m2c draft, mechanical cleaning, compile with flag variants (about 90 compiles per second on a
two-core container), relocation-aware scoring, decomp-permuter for up to 8 differing instructions, family cloning, inline-asm
templates for syscall stubs. Pilot rates: functions under 100 B 57.9 % (70.2 % after the boundary repair), 100-300 B 9-12 %,
0 % above 300 B. Progress went from 0.79 % to 7.7 % of `.text` (37.7 % of the functions). What blocks the rest is typing
(callee signatures, struct layouts, stack objects) and EE-specific code, not search time. Details: [pipeline.md](pipeline.md).

## Phase 5: file-by-file recovery

Work proceeded in rounds, each on a set of TUs with one owner per TU:

- **Pilot** (three parallel owners, one TU each): +31 functions, +3,936 bytes, 4.63 kB per person-hour. Blockers in order:
  types and object lifetimes, scheduling and register allocation, pipeline gaps (switch tables, mixed 64/128-bit EE code,
  small data).
- **Area queues** (seven areas, three rounds): +115, +147 and +53 functions (15.7 kB, 19.5 kB, 9.0 kB); stopped when two
  rounds gained under 1 % of `.text`. Tooling gains (argument and return evidence, switch sections, byte-address arithmetic,
  stack escapes) mattered more than manual throughput. No match above 1,000 B in 57 manual attempts.
- **Large-function study**: 77,715 source/compiler/flag combinations over 12 GCC and five Metrowerks builds on 25 near
  misses and eight controls. Only SN 1.36 reproduced all controls; no flag set helped consistently. Concrete failures were
  upstream of register allocation (byte increments on typed pointers, lost HI/LO displacement, narrowed 64-bit multiply,
  extra allocator arguments, missing cleanup calls). Fixing them gave +106 functions (12.2 kB).
- **Kynapse context follow-up**: whole-TU context and PS2 declarations helped a few cases (436-byte initializer, cache
  method); the 2,128-byte `ParameterTables` constructor matched once the assembler padding rule was recovered.
- **Short-loop padding**: of 1,278 SN-assigned short backward branches, 712 are padded and 566 not; six- and seven-word
  forms mix inside libraries and even identical bodies, and no position or content rule explains them .
  SN Ps2EeAs 1.9.25.758 pads displacement -1..-5 to six words; a two-byte hash-guarded derivative (`sn-min6`) gives the
  six-word family. A uniform substitution regresses 46 of 5,018 controls, so it is selected per unit only
  (`--assembler=sn-min6`, `assembler_evidence: weak` in `units.yaml`). +41 functions / 5,248 B.
- **RTTI class skeletons**: 189 class type-info records (166 Kaim classes), 171 base links, 3,830 vtable slots;
  `tools/maint/class_skeletons.py` generated `include/game/classes/` and `include/kynapse/classes/` (since then only the views the sources use are kept there; 189 named interfaces, 383
  unknown-owner views, 2,055 field views of which about 700 have scoped PS2 access proofs). +7 functions.
- **C++ class recovery** (seven rounds over four queues, then shared-context preparation): 5,066 -> 5,354 functions, 281.6 kB
  -> 362.0 kB. Shared PS2 helpers (`include/ps2/`, 26 exact consumers) cover the SN integer/vector ABI, VU0 transforms,
  Kynapse iterators and RenderWare operations. Stopped when throughput fell below 1,500 B per hour or declined twice in a
  row (1,912 B/h in the last round). Complete TUs: PathObject, XML reader, PathWay, constraint TU, ChildBuffers and others.
- **Camera, weapons, first-person animation and effects**: 5,354 -> 5,438 functions / 377,680 B; throughput fell from 2,536
  to 566 B/h and the round stopped. Complete original classes: none established.
- **Vector/matrix study**: 845 SN-assigned VU0 users; 8 inline recipes with two exact consumers each; `AUTODECOMP_VU0=1`
  lowering covers only 89 functions. Checkpoint **5,444 functions / 378,560 B (13.94 %)**.
- **Depth pass**: 40 hours on the hardest functions (see [status.md](status.md#recent-results-the-last-depth-pass)):
  **5,563 functions / 410,384 B (15.11 %)**.

Lessons that recurred: preserve PS2 types, float operand order and object lifetimes; define inline helpers before use;
check the callee's real arity and return use before blaming the compiler; one assembler recipe per verified unit rather
than one global rule; extrapolations from small-function rates do not hold for functions above 300 B (76 % of the
remaining bytes), and no function above 1 KB has matched from stock output except `ParameterTables`.

## Equivalence experiment (moved out)

A second evidence level was tried: readable source whose behavior agrees with the original on recorded machine states
(an EE interpreter and a differential tester; 50 candidates, 14 small functions agreed with full block coverage, none above
1 KB). It was not carried far enough to cover the hard functions and is not part of this repository: evidence here is exact
or draft.
