# Translation units and toolchain facts

Evidence for TU boundaries and libraries (`tools/build/tus.py`), per-TU compilers and flags, the assembler short-loop padding study, one file per TU.

## Translation units

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
- **Cross-build.** Adjacency of functions in the beta and demo builds and `+0x80` structure shifts in the PAL/Korean/Japanese builds
  barely differ at known boundaries and inside objects (breaks 6.5 % vs 3.0 %, shift changes 7.0 % vs 8.8 %): supporting evidence only.
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
stay whole. Shorter edges find more boundaries and cut more (16: 69 % / 11.8 %; 8: 78 % / 22 %). The map (`build/SLUS_213.76/tus.yaml`) has
599 object TUs of two or more functions (120 `exact`, 30 `high`, 165 `medium`, 284 `low`; the longest has 289 functions), 1,586
**isolated** functions that no relation ties to a neighbour (each is an object of its own or a piece of a larger one: accessors and
leaf code) and 852 link-once sections (702 `exact`). By bytes of `.text`: `exact` 14.5 %, `high` 2.9 %, `medium` 52.8 %, `low` 29.8 %.
Treat proposed edges as likely and the joins inside a TU as certain; a stretch of related functions that no cut separates may hold
several objects.

**Per-TU flags.** `AUTODECOMP_TU=1` (or `autodecomp.py run --tu all|COMPILER`) tries each function with its TU's compiler and flags first
(`--cc=NAME` in a flag set selects another compiler; `register` turns it into the unit's `compiler`). `build_job.py` runs the native
Sony compilers from the toolchain. `autodecomp.py run --cc NAME` and `permute --cc NAME` are for experiments.


## Assemblers and short-loop padding

**Short-loop padding.** Retail has both six- and seven-word patterns, including identical loop
bodies with different padding; a compiler's identity alone does not determine its assembler policy.
Disassembly of the assembler located SN 1.9.25.758's unconditional short-loop routine: it extends negative branch
word displacements −1…−5 to −6 (seven words including the delay slot). The separately written
`sn-min6` derivative changes two immediate bytes, extending −1…−4 to −5 instead. It reproduces the
six-word family while retaining division, FPU and other hazard handling. No compiler assembly or game
instruction bytes are edited. Existing recipes stay in place: uniform substitution regresses matches.

`python3 tools/toolchain.py install` writes the derivative next to the downloaded original.
`config/toolchain-assemblers.json` records original/output hashes, exact patch sites and upstream
references; `tools/build/patch_ps2eeas.py` retains the original, verifies full hashes/preimages and is idempotent.
Compilation checks the derivative hash again before execution. Add `--assembler=sn-min6` to a
unit's flags or pass it to `tools/compile.py`; the selected compiler emits untouched `-S` output.
Candidate and production caches include the recipe. The automatic pipeline tries this verified
fallback before the older `sn-2.73a` assembler; `gas-2.40`, `gas-2.40-fix` and `sony-2.9` remain
explicit experiments. Every new match must pass the full image comparison.

Studies of the short loops (since removed from the tree, see the Git history of `tools/studies/`) classified every
SN-assigned short branch by TU, library, compiler override, delay-slot and loop length, and tested linked, function-,
TU- and text-relative positions and alignment residues. The forms do not partition libraries or TUs cleanly; six- and
seven-word candidates still collide after accounting for candidate padding, and a static trace finds a section-relative
displacement check without an alignment or cache-line gate. Keep alternate assemblers as individually verified unit
recipes (the units serializer marks them `assembler_evidence: {strength: weak, ...}`: historical toolchain provenance is
unresolved); full-image byte identity remains mandatory. Consistent filtered cohorts are leads, not recovered build flags.


## One file per TU

Each TU of the map that has recovered code is one file (`src/<library>/tu_<address>.c|cpp`, [units.md](units.md)); the split list
records where a TU is several files. Compiled with `-ffunction-sections`, SN 1.36 writes `.text.<symbol>` per function without
changing a code byte, `make_ld.py` renames each section to the slot of its function and `units_verify.py` checks each section
against the span of the original function, so INCLUDE_ASM functions (orphan pieces, hard cases) stay between the compiled ones.
Constants keep one section per file (the literal pool of GCC 2.95 has no per-constant sections: `-fdata-sections` only splits
named variables), so a TU whose assembly functions between its compiled functions own constants is several files. Parts of a TU that disagree in
flags, language, declarations or constants are separate files (`note:` in the split list says why).
