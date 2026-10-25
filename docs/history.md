# History

How the project got where it is, in phases, with the findings that still shape the work. Progress numbers are not repeated
here: they are in the table of the [README](../README.md#progress). The current state is in [status.md](status.md); terms are in
the [glossary](glossary.md).

## Where the first sources came from

The first recovered sources were written by the author of this repository in a separate, unpublished project that
reconstructs the Xbox build of the game. They were imported once into this repository as the starting point (Kynapse
functions and a few game functions that are exact on PS2 as well); the importers are not part of it, and the imported files
keep a header comment naming their origin. Everything since was written, matched and checked here against the PS2 executable.

## Phase 0: inputs ([inputs.md](inputs.md))

Nine disc images were triaged. No executable has symbols, debug sections or compiler banners. The PAL, Korean and Japanese
retail builds are the USA code plus small changes (member offsets shift by 0x80 in about a fifth of the code); the beta and
the demos are earlier builds and only give naming and ordering hints. The USA retail executable became the target. SN GCC
2.95.3 build 1.36 (`ee-gcc2.95.3-136`, `-O2 -G0 -snas`) is the game compiler.

## Phase 1: identical rebuild

`ninja` rebuilds the boot ELF byte for byte, for all five retail images. Facts that shaped the design:

- GNU `ld` cannot write the retail container, so `tools/build/pack_elf.py` re-packs the linked sections; DVP overlays and
  `.vutext`/`.vudata` are extracted payloads.
- One linker statement per object is quadratic and did not finish for 12,000 objects: input sections are named
  `<section>.<address>` and placed by `SORT_BY_NAME` in a generated script.
- The rebuild is shiftable: inserting NOPs into one function relinks with every symbolic reference moved. The exceptions are
  raw numbers in data that look like addresses ([build.md](build.md#shiftability)).

## Phase 2: one object per function, symbols, first sources

- The image is split into one object per function plus data objects, cached by input hash. Constants travel with their
  function; `.gcc_except_table` belongs to whole object files and mostly stays shared.
- Function boundaries: small `<instruction>; nop` orphan pieces sit between functions and are not code of either neighbour;
  `tools/build/boundaries.py` splits them off (functions that splat had fused with a piece then match individually) and adds the
  `__CTOR_LIST__` entries as starts. A few real functions open with the same shape and are listed in `explicit_boundaries.txt`.
- An earlier analysis of the executable listed about 9,900 functions; splat finds more starts. Its names are `alias` lines in
  `config/SLUS_213.76/symbols.txt`, its signatures live in `include/ps2/prototypes.h`.

## Phase 3: translation units ([tus.md](tus.md))

`tools/build/tus.py` combines unwind-frame groups (exact object boundaries), the constructor list (certain TU ends), library
strings and code style, data-order joins and call edges into the TU map, with library ranges, compiler and flags. Orphan
pieces, alignment and cross-build shifts do not mark boundaries. The Sony libraries match with `ee-gcc2.9-991111-01 -O2 -G0`
and never with SN 1.36.

## Phase 4: automatic pipeline ([pipeline.md](pipeline.md))

`tools/autodecomp.py`: m2c draft, mechanical cleaning, compile with flag variants, relocation-aware scoring, decomp-permuter for
near misses, cloning of identical bodies, inline-asm templates for syscall stubs. Small functions match at a good rate and
large ones almost never; what blocks the rest is typing (callee signatures, struct layouts, stack objects) and EE-specific
code, not search time.

## Phase 5: file-by-file recovery

Work proceeded file by file with one person per TU, in rounds that stopped when the gain per hour fell. What was learned:

- Tooling gains (argument and return evidence, switch sections, byte-address arithmetic, stack escapes) mattered more than
  manual throughput. A study of tens of thousands of source, compiler and flag combinations on near misses found that only
  SN 1.36 reproduces the controls and that no flag set helps consistently; the concrete failures were upstream of register
  allocation (byte increments on typed pointers, lost HI/LO displacements, narrowed 64-bit multiplies, missing cleanup calls),
  and fixing the tools recovered functions.
- Short-loop padding: six- and seven-word forms mix inside libraries and even identical bodies, and no position or content rule
  explains them. SN Ps2EeAs 1.9.25.758 pads short backward branches to six words; a two-byte, hash-guarded derivative
  (`sn-min6`) gives the six-word form. A uniform substitution regresses controls, so it is selected per unit only.
- RTTI gives the class hierarchy: the type-info records name the Kaim classes and some others, and give base links and
  virtual-table slots. `tools/maint/class_skeletons.py` turns them into class skeletons from which the hand-edited class views
  under `include/game/classes/` and `include/kynapse/classes/` began. Classes without a type-info name are known by their
  vtable only (`UnknownVtable_<address>`).
- C++ recovery of Kynapse, camera, weapons, first-person animation and effects added shared PS2 helpers (`include/ps2/`: the
  SN integer/vector ABI, VU0 transforms, Kynapse iterators, RenderWare operations). Complete original classes are rare.
- A VU0 study found that eight inline recipes have two exact consumers each; the pipeline's VU0 lowering covers only a small
  part of the vector code.
- The hardest functions were tried in a long pass with the permuter running beside it: new large exact bodies came from shared
  loop indices, reference-return views, helper visibility, scoped alias and divide recipes, and real expression lifetimes.

Lessons that recurred: preserve PS2 types, float operand order and object lifetimes; define inline helpers before use; check the
callee's real arity and return use before blaming the compiler; one assembler recipe per verified unit rather than one global
rule; extrapolations from small-function rates do not hold for large functions.

## Ownership of functions

Originally several source files could list the same function, and only the build decided which compiled it. Now every function
belongs to exactly one file and one split-list entry, ranges do not overlap, and a check enforces it ([units.md](units.md)).

## An equivalence experiment (moved out)

A third kind of evidence was tried: readable source whose behavior agrees with the original on recorded machine states (an EE
interpreter and a differential tester). A few small functions agreed with full block coverage and none of the large ones did.
It is not part of this repository: evidence here is exact or draft.
