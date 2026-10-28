# Translation unit files and the split list

How source replaces assembly in the build. The inputs are `src/`, `config/SLUS_213.76/splits.yaml`, and
`symbols.txt`; nothing is generated into Git (`tools/build/units.py` derives the *units* into `build/`).

## One file per translation unit

`src/<library>/tu_<address>.c|cpp` (for the game library `src/game/<subsystem>/tu_<address>.c|cpp`, see
[src/game/README.md](../src/game/README.md)) lists every function of one translation unit (the generated `build/SLUS_213.76/tus.yaml`) in address order. A
recovered function is C or C++; the others are markers:

```c
#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100518);
void func_001005A0(void* arg0) { ... }               /* recovered */
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100628);

#ifdef NON_MATCHING
int func_001B78D8(BkEffectPoolPS2* pool) { ... }     /* draft, not exact yet */
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B78D8);
#endif
```

The marker names the function's assembly (`asm/SLUS_213.76/nonmatchings/func_XXXXXXXX.s`, written by the build). **Every function
is listed in exactly one file**: as an `INCLUDE_ASM` line while it is assembly, as a definition once it is recovered. The file
is the one whose entry in the split list owns the function (below); no other file mentions it. Every function of a file's
ranges that has no marker must be defined by the file; the build checks that the compiled function takes the original's place
and that the whole image stays identical. `python3 tools/where.py func_XXXXXXXX` prints the owning file and line (offline).
Hand-written files keep descriptive names (`kynapse/behaviors_pathway.cpp`). Link-once copies (compiler-emitted inline and
template code) live in `src/<library>/inline/` ([build.md](build.md#link-once-copies)).

## Drafts

A function that does not match yet keeps its `INCLUDE_ASM` line and its readable version sits above it in an
`#ifdef NON_MATCHING` block (the `#else` branch is the marker), with a one-line `// Unmatched:` note. `python3 configure.py
--non-matching` followed by `ninja` builds the drafts into a separate executable.

A draft sits right above the marker of the function it is for, in the file that owns the function. Readable code whose
function cannot be identified does not stay in the tree: `src/` has no `#if 0` blocks. A draft that needs headers or flags of
its own gets a small file of its own (`python3 tools/split_function.py func_XXXXXXXX --cpp`), so that it does not collide with
the declarations of the file around it.

## Source layout

`src/<library>/<name>.c|cpp`, one file per translation unit that has recovered code (`tu_<address>`, plus `_<address>` for
the further files of a TU that cannot be one: other flags, language or constants) or a descriptive name inherited from the
class or module. The file lists every function it owns, the unrecovered ones as INCLUDE_ASM lines; drafts are
`#ifdef NON_MATCHING` blocks in it. Libraries: `game`, `apt` (EA Apt/Flash UI), `kynapse`,
`animation`, `physics`, `rw_core`, `rw_audio`, `sony`, `libc`. Compiler-emitted inline and template copies (link-once code) live in `src/<library>/inline/` of the library that owns them (owners are computed into `build/SLUS_213.76/inline_owners.txt`). `config/SLUS_213.76/splits.yaml`
lists the files with their address ranges and flags; `tools/build/layout.py` owns the naming rules. File-name suffixes are
explained in [units.md](units.md#file-names).

Headers follow the libraries: `include/<library>/` for `game`, `kynapse`, `animation`, `physics`, `rw_core`, `rw_audio`
and `apt`, and `include/ps2/` for helpers shared by all of them (EE types, VU0 operations, the draft prelude). Class
views (`include/game/classes/`, `include/kynapse/classes/`) sit beside the hand-written headers; recovered layouts that several files share
are plainly named headers there, the others are defined in the one source file that uses them.

## File names

A file that has no descriptive name is named after addresses (the rules are in `tools/build/layout.py`):

| Name | Meaning |
| --- | --- |
| `tu_<A>.c` | the unit of the translation unit whose first function is at `A` (hexadecimal, no `0x`) |
| `tu_<A>_<B>.c` | a further unit of the same TU, starting at `B`: the part that needs other flags, another language or its own constants (`tu_103930_105228.c` is the unit at 0x105228 of the TU that starts at 0x103930); its `note:` in the split list says why |
| `linkonce_<A>.c`, `linkonce_<A>_<B>.c` | compiler-emitted inline and template copies (link-once code) in `src/<library>/inline/` |
| `<name>_<A>.cpp` | a file named after the class or module (`frontend_menu_load.cpp`, `animation_lifecycle_345500.cpp`), with the address of its first function when the name alone is not unique |

`.c` or `.cpp` is the language the file compiles as. A file moves to a descriptive name when the evidence shows what it is
([CONTRIBUTING.md](../CONTRIBUTING.md#naming)).

## The split list

`config/SLUS_213.76/splits.yaml`, one line per entry, ordered by address:

```yaml
defaults: {compiler: ee-gcc2.95.3-136, flags: [-O2, -G0, -snas]}
splits:
  - {src: src/game/unsorted/tu_100518.c, range: [0x100518, 0x103858]}
  - {src: src/game/ui/frontend_menu_notify.cpp, range: [0x103db0, 0x103df0], flags: [-O1, -G0, -snas]}
  - {src: src/physics/tu_32bc70.cpp, range: [0x32bc70, 0x32e3d0], flags: [-O2, -G8, -snas], assembler: sn-min6,
     data_ranges: [...], full_tu_context: true, note: "..."}
  - {src: src/game/unsorted/game_methods.cpp, range: [0x114160, 0x114168]}
  - {src: src/game/unsorted/game_methods.cpp, range: [0x1148d0, 0x114960]}
```

`range` is `[start, end)`. **An entry owns every function in its range, and ranges never overlap**, so each function has one
owner. A file whose functions are not adjacent (a class whose methods are spread over the executable, a function that needed
other flags and was carved out of its neighbours) has one entry per stretch: the first carries all the options, the others only
`src`, `range` and `note`, and the file is compiled once. `flags` and `compiler` replace the defaults; `assembler` names a per-unit
assembler variant (`sn-min6`, ... see [units.md](units.md#recovering-original-translation-units)); `note` says why a TU is several files. A file is compiled once, with the options of
its first entry; code that needs other options (another compiler flag, language or assembler) is a file of its own, however
small, so a function that sits between two functions of another file does not overlap them. Rare keys keep the options of the old unit format (`data_ranges`,
`rodata_type_splits`, `shared_exception_tables`, `full_tu_context`, `unlinked_context_helpers`, `externs`).

The rule is checked by `python3 tools/build/splits.py check` (no game files), by `python3 configure.py` and by the tests: ranges
that overlap by even one byte (also two stretches of one file), an `INCLUDE_ASM` line for a function outside the file's ranges or listed twice, and
(with a build) a function that no entry owns are errors. To give a function to a file of its own (other flags, `-x c++`, another compiler), run `python3 tools/split_function.py func_XXXXXXXX [--cpp] [--flags "..."]`: it removes the marker and
that stretch of the range from the old owner and creates the new file and entry (`tools/pipeline/tu_files.py` does the same when the
automatic pipeline makes a file for a function). `python3 tools/relocate_sources.py old new` renames or moves a whole file.

## Names

`symbols.txt` (splat's `name = 0xADDRESS; // type:func`) holds the names a compiled function may carry (a mangled C++
name; otherwise `func_XXXXXXXX`) and the addresses of names the code uses without defining them (`gClock`, a callee in
another TU). Add a line when the build says a symbol has no address, or when a function is defined under its mangled name.
A line ending in `alias` (`// type:func alias`) is only a readable name and never affects the build
([build.md](build.md#symbols-and-progress)).

SN gives compiler-generated static I/D wrappers a random filename suffix. A binding such as
`_GLOBAL_$I$002092B8 = 0x2092B8; // type:func` explicitly selects the unit's sole generated I wrapper;
`$D$` selects a destructor wrapper. The address must agree, and missing or ambiguous wrappers fail.
The object compiler renames symbols and their relocations without changing code.

## What the build does with it

The build compiles each file once with real assembler includes. `object_compile.py` normalizes SN objects and records
resolved symbols; `unit_link.py` orders ordinary input sections and invokes GNU ld. Function sections permit arbitrary
C/INCLUDE_ASM interleaving. Three complete C++ files retain `-fno-function-sections` to preserve their compiler's native CFI;
the object normalizer separates their text into named function sections without changing instructions or unwind ranges.
`units.py` and the source label reader still support ownership, editing and progress; assembly selection is performed by
the compiler and assembler. No source-unit function has a separate assembly object. See [build.md](build.md).

## Full TU context

With function sections, `full_tu_context: true` lets real unfinished function bodies stay visible to the compiler. Every
emitted function must be a function of the file or listed in `unlinked_context_helpers` (reviewed helpers, no claim about
originals); all other allocated inputs are discarded and their globals resolve to the original assembly. Kept functions
still require exact sizes, natural section tails, real callee bindings and the identical image.

The unfinished bodies sit in `#ifdef FULL_TU_CONTEXT` blocks, and the split entry of such a unit passes `-DFULL_TU_CONTEXT` to
the compiler. That is the only conditional besides `NON_MATCHING` that may surround function bodies in `src/`.

## Explicit source data

A file can take over storage with exact half-open ranges:

```yaml
data_ranges: [{section: .data, input: .data.my_tu, start: '0x3ea768', end: '0x3ea7e8'},
              {section: .data, input: .data, start: '0x3c9364', end: '0x3c94a4', kind: unwind},
              {section: .bss, input: .bss, start: '0x4513d8', end: '0x4514f0'}]
```

Supported sections are `.data`, `.sdata`, `.rodata`, `.bss` and `.sbss`. Each input must fill its range completely with the
right PROGBITS/NOBITS kind; ranges cannot overlap and each edge must be an existing splat `dlabel`, except `kind: unwind`,
which accepts a complete decoded original CIE/FDE group. Use typed definitions; SN 1.36 emits a custom `.bss.name` attribute
as PROGBITS. `rodata_type_splits: ['0x40a668']` splits a label that combines an ASCIZ with adjacent runtime type data.
`shared_exception_tables: ['0x...']` takes over an exception table shared by several functions when every handler is a
function of the same file. A full identical image is required in every case.

## Recovering original translation units

The PS2 build uses separate compilation with the GCC-based compilers below, rather than whole-game optimization.
Original object boundaries remain visible in exception-frame groups and constructor sequences; independently compiling
recovered files with the selected recipes reproduces their functions in the byte-identical image. This supports local
matching, though source files still depend on shared headers, inline helpers and data ownership. A proposed boundary
is not an exact one. See [toolchain facts](build.md#toolchain-facts) for the current recipes.

The executable has no symbols, so the object files are recovered from what the linker and compiler left behind. `python3 tools/build/tus.py
all` collects the signals (`evidence`), writes `build/SLUS_213.76/tus.yaml` (`map`, run by `ninja`, not committed; hand corrections in `config/tus_overrides.yaml`) and measures how
the signals agree (`validate`). Each TU in the map has a text range, data ranges (items only its functions use), compiler and flags (those of
its matched functions, else a guess from the code style), a confidence and its evidence. Confidence: `exact` = unwind frames (the TU is
one frame group, 822 of them, 120 outside the link-once area), `high` = both edges from constructor stubs, compiler-style or library changes, `medium` = proposed edges
but data joins inside, `low` = proposed edges only.

What the executable shows (USA retail):

- **Unwind frames** (.data). 822 CIE groups, each with one FDE per function of an object compiled with exceptions; the FDEs are
  contiguous in `.text`, so a group is one object (120 in the regular code: Kynapse, the animation library and a few Sony C++ pieces,
  12 % of `.text`) or, from `0x383b50` to the end of `.text`, one **link-once** section (702 groups: inline functions, virtual destructors, `GetClassInfo`,
  `__tf` type-info functions). The first CIE form (281 groups) has no exception table; the `eh` form (541) carries the address of its
  object's `.gcc_except_table` slice. Link-once code, vtables (426 runs of `(0, method)` pairs in `.data`) and their `.gnu.linkonce.*`
  constants come last in each section, in order of first use, so they say nothing about where an object starts.
- **Global constructors.** A TU with global objects ends with `__static_initialization_and_destruction_0(int, int)`, the `__tcf_N`
  destructor thunks and the `_GLOBAL__I_*` / `_GLOBAL__D_*` stubs (`li $a0, 1/0; ori $a1, $zero, 0xffff; jal sinit`). The linker collects
  the I stubs, in link order, into `__CTOR_LIST__` (`.data` 0x3d9cc8: count word, then 116 pointers); `func_0028FB08` walks it backwards
  from the start-up code (`crt0` = `func_00100008`, a hand-written function). The stub pair is the last thing in its object (all 29 in
  frame groups are followed by a frame-group edge), so each of the 116 entries is a certain TU end. Three entries are special: `0x339c28`
  lay inside the function `func_00339C00` (splat fused it with the orphan pieces before it; `boundaries.py` now splits it),
  `0x1f1220` is a 56-byte variant and `0x3822b8` a `j` to a registration helper.
- **Orphan pieces do not mark boundaries.** The 1,157 `<instruction>; nop` pieces (637 runs) are as frequent inside gaps that constants
  join (4.0 %) or that no relation crosses (5.5 %) as overall (6.2 %), occur in none of the 1,225 gaps inside frame groups and at 2.7 % of
  the certain boundaries. They look like the last two words of functions whose bodies were removed, and they exist only in code compiled
  without exceptions.
- **No alignment signal.** Objects start at 8 bytes like functions (multiples of 16/32/64/128 at known boundaries: 51/24/11/5 %, inside
  objects 50/26/13/6 %); frame groups start at 4 in `.data`; strings and tables are 8-aligned inside an object.
- **Data order.** Every data section follows the text order (95 % of consecutive private items of `.bss`, `.sbss`, `.data` and `.rodata` are
  in text order), so a constant used by several functions, or a static whose order is violated by functions between its users, forces
  those functions into one object. These joins are certain only where they are narrow (a shared global such as the ctype table or a CRC
  table is used from everywhere), so items used by more than 12 functions or by functions more than 0x4000 bytes apart are ignored.
  Of the 10,300 gaps between functions, data joins cover about 5,000, call edges 8,700 and shared items 2,400; a gap that nothing
  crosses is the evidence for a boundary.
- **Compilers.** Callee-saved registers are saved with `sq` in the SN 1.36 output (5,415 functions); 334 functions save them with `sd` in
  16-byte slots, in three solid blocks (`0x28fab0-0x2a5038`, `0x355278-0x35c308`, `0x367e28-0x372d68`: Sony's precompiled libraries).
  The compiler `ee-gcc2.9-991111-01 -O2 -G0` (no `-snas`) emits exactly that style: 36 of the functions of these blocks match
  with it and none matches with SN 1.36. `ee-gcc2.95.3-114`, `ee-gcc2.95.2-273a` and the 2.96 build match nothing more than SN 1.36 does.
  A later scoped scalar-leaf control at `0x3484d0` matches Sony 2.9 and 2.96 defaults because of their divide workaround;
  the larger methods in that TU still require SN 1.36, so this does not establish a new compiler zone.
  `-O1` (127 functions), `-G8` (22) and `-fno-schedule-insns2` (16) match in scattered TUs and need no zone of their own.
- **Libraries** (strings, style, frames; `libraries:` in `tus.yaml`, kept by hand as `config/SLUS_213.76/libraries.txt`; edges between libraries are certain only where a style or frame
  change marks them). Game code `0x100338-0x28fab0`, containing the EA Apt/Flash UI `0x218000-0x258000` and the Sony video decoder
  sample `vibuf.c` near `0x28f000`; then, all in the `sd` style, Sony's start-up and constructor walker `0x28fab0-0x292f08`, libipu/libmpeg
  `0x292f08-0x29b0a8`, libdbc, libdma/libpad2, libm `0x29d4c0-0x2a4410` and libcdvd `0x2a4410-0x2a50f8`; RenderWare Core
  `0x2a50f8-0x2d15a0` ("Core built at Feb 28 2005"); Kynapse `0x2d15a0-0x310278` (frames, `kyastar.cpp`); RenderWare Audio EE side and
  game audio glue `0x310278-0x32ae70` (`RwaRPCTransfer`; only one string identifies it); physics `0x32ae70-0x33faa8` and animation
  `0x3420e8-0x353118` (leads from the Xbox counterpart map; the animation library has frames); libmc2 `0x355278-0x35ebb0` (`sd`); a
  printf-style libc `0x35ebb0-0x367400` (SN-compiled); libkernl, stdio and TLB `0x367400-0x36f978` (`sd`); libstdc++ type info and
  exception support `0x36f978-0x371520` (`sd`, frames); libgs `0x371520-0x372fc0`; then game code to `0x383b50` and the link-once area.

Agreement, with the unwind-frame and constructor boundaries held out (`tus.py validate`): predicting boundaries from "no data join, call or
shared item crosses the gap" (edges up to 32 functions) finds 53 % of the 185 certain boundaries and wrongly cuts 5.1 % of the 1,225 gaps
inside frame groups (precision 61 % in that set); 63 % of the frame groups of two or more functions and 99 % of the constructor sequences
stay whole. Shorter edges find more boundaries and cut more (16: 69 % / 11.8 %; 8: 78 % / 22 %). The map (`build/SLUS_213.76/tus.yaml`) has object TUs of two or more functions, **isolated** functions that no relation
ties to a neighbour (each is an object of its own or a piece of a larger one: accessors and leaf code) and link-once sections;
every TU has a confidence (`exact`, `high`, `medium`, `low`). `ninja tus` writes it, and the counts and the share of `.text` by
confidence are in [status.md](status.md#progress).
Treat proposed edges as likely and the joins inside a TU as certain; a stretch of related functions that no cut separates may hold
several objects.

**Per-TU flags.** `AUTODECOMP_TU=1` (or `autodecomp.py run --tu all|COMPILER`) tries each function with its TU's compiler and flags first
(`--cc=NAME` in a flag set selects another compiler; `register` turns it into the unit's `compiler`). `object_compile.py` runs the selected compiler and assembler from the pinned local toolchain. `autodecomp.py run --cc NAME` and `permute --cc NAME` are for experiments.


## Assemblers and short-loop padding

**Short-loop padding.** Retail has both six- and seven-word patterns, including identical loop
bodies with different padding; a compiler's identity alone does not determine its assembler policy.
Disassembly of the assembler located SN 1.9.25.758's unconditional short-loop routine: it extends negative branch
word displacements −1…−5 to −6 (seven words including the delay slot). The separately written
`sn-min6` derivative changes two immediate bytes, extending −1…−4 to −5 instead. It reproduces the
six-word form while retaining division, FPU and other hazard handling. No compiler assembly or game
instruction bytes are edited. Existing recipes stay in place: uniform substitution regresses matches.

`python3 tools/toolchain.py install` writes the derivative next to the downloaded original.
`config/toolchain-assemblers.json` records original/output hashes, exact patch sites and upstream
references; `tools/build/patch_ps2eeas.py` retains the original, verifies full hashes/preimages and is idempotent.
Compilation checks the derivative hash again before execution. Add `--assembler=sn-min6` to a
unit's flags or pass it to `tools/compile.py`; the selected compiler emits untouched `-S` output.
Candidate caches include the recipe; production Ninja specifications record it. The automatic pipeline tries this verified
fallback before the older `sn-2.73a` assembler; `gas-2.40`, `gas-2.40-fix` and `sony-2.9` remain
explicit experiments. Every new match must pass the full image comparison.

Studies of the short loops (not kept in the tree) classified every
SN-assigned short branch by TU, library, compiler override, delay-slot and loop length, and tested linked, function-,
TU- and text-relative positions and alignment residues. The forms do not partition libraries or TUs cleanly; six- and
seven-word candidates still collide after accounting for candidate padding, and a static trace finds a section-relative
displacement check without an alignment or cache-line condition. Keep alternate assemblers as individually verified unit
recipes (the units serializer marks them `assembler_evidence: {strength: weak, ...}`: historical toolchain provenance is
unresolved); full-image byte identity remains mandatory. Consistent filtered cohorts are leads, not recovered build flags.
