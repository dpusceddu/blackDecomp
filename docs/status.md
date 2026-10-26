# Status

The goal, the method, the toolchain facts, the current numbers and the open problems. How to build and contribute is in
[README.md](../README.md) and [CONTRIBUTING.md](../CONTRIBUTING.md); how the pieces work is in the other files here; the
project history is in [history.md](history.md). Terms are in the [glossary](glossary.md).

## Goal

Readable C/C++ source for the retail PS2 executable of Black (`SLUS_213.76`, the only first-class target: source, progress and
routine checks; four more regional builds rebuild from assembly and are checked before releases with `tools/check_versions.py`),
organized into the original libraries and translation units (TUs). Evidence has two levels:

| Level | Meaning | Where it lives |
| --- | --- | --- |
| exact | the full rebuilt image stays byte-identical with the function compiled from source | a function without INCLUDE_ASM marker in its TU file ([units.md](units.md)); replaces the assembly in the build |
| draft | readable or machine-written source that does not match (yet) | an `#ifdef NON_MATCHING` block in the TU file, marked `// Unmatched:`; never replaces assembly |

The same game code also ships on Xbox; this repository covers the PS2 side only. Names and types seen in the Xbox build are
leads, never proof of PS2 layouts.

## Method

1. **Full build from day one.** The executable is split into assembly and data that reassemble to the identical image;
   source replaces assembly inside that build, so linking, relocations and data are always real ([build.md](build.md)).
2. **Original TUs.** Boundaries come from unwind frames, the constructor list, library strings, code style and data joins
   (`tools/build/tus.py`, which `ninja` runs into the ignored `build/SLUS_213.76/tus.yaml`; [tus.md](tus.md)). Match whole files where the evidence is exact.
3. **One check for exactness**: `ninja` ends with `OK`. No per-function proof journals.
4. **Automate the routine path**: m2c draft, compile flag variants, relocation-aware scoring, permuter, cloning of identical bodies
   ([pipeline.md](pipeline.md)). People spend their time on types, classes and the functions the pipeline cannot do.
5. **Parallel by file.** Contributors work on different TUs at the same time (claimed by pull request, see [CONTRIBUTING.md](../CONTRIBUTING.md#claiming-a-file)); every function belongs to exactly one file ([units.md](units.md)).
6. **Private inputs stay private.** Game bytes, generated assembly and data, compilers and build output are ignored by Git.

## Toolchain facts

| Piece | Choice |
| --- | --- |
| Compilers | `ee-gcc2.95.3-136` (SN build 1.36) with `-O2 -G0 -snas` for game, Kynapse, animation, physics, RenderWare Core/Audio, apt, libc stdio; `ee-gcc2.9-991111-01 -O2 -G0` (SN driver, GNU assembler) for the Sony libraries (`sd` saves: libipu/libmpeg, libdbc, libdma, libm, libcdvd, libmc2, libkernl, libstdc++ type info, libgs) |
| Scoped scalar exception | three audio getters use Sony `ee-gcc2.96` with `-mno-handle-ee-div-pipeline-bug`; measured divide controls scope this choice without identifying the original whole-TU compiler |
| Per-TU flag variants | `-O1`, `-G8` where gp-relative small data is used, `-fno-schedule-insns`, `-fbyte-bool`, `-fno-rtti`, `-x c++`, `-ffunction-sections` (merged TUs), `-mvu0-use-vf0-vf31` / `-vf16` (VU0 inline helpers) |
| Assemblers | untouched compiler assembler (`-snas`) by default; `--assembler=sn-min6` (hash-guarded derivative of Ps2EeAs 1.9.25.758 that pads short loops to six words, reproduced by `tools/build/patch_ps2eeas.py`) on verified units only; `gas-2.40`, `gas-2.40-fix`, `sony-2.9`, `sn-2.73a` are explicit experiments. The splits that select `assembler: sn-min6` in `config/SLUS_213.76/splits.yaml` use it because it reproduces their bytes, not because a recovered rule says the original used it: treat that choice as weak evidence (open problem 4) |
| Assembly files | Per-file assembler from `splits.yaml`, through real INCLUDE_ASM; fixed words and symbolic relocation records handle assembler quirks |
| Linker | mainline GNU `ld` 2.40 (`binutils-mipsel-linux-gnu`), explicitly ordered ordinary input sections; `tools/build/pack_elf.py` writes the retail container (`e_flags 0x20924001`) |
| Everything else | splat/spimdisasm/rabbitizer split, Ninja, m2c (`-t mipsee-gcc-c`), decomp-permuter; names, prototypes and types are committed, hand-maintained files (`config/SLUS_213.76/symbols.txt`, `include/ps2/`) |
| Running the tools | the compilers are decomp.me archives pinned by SHA-256 (`config/toolchain-*.json`); the Windows programs run under wibo, the Sony tools are 32-bit Linux programs (`tools/toolchain.py`, [build.md](build.md)) |

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

## Current state (USA retail)

The progress numbers are in the table of the [README](../README.md#progress), written by `ninja badges` (what a function is
there, and how the image measure differs). Everything counted rebuilds byte-identical. Routine work checks USA only; the
other four retail images (Europe, Europe/Australia, Korea, Japan) are checked with `tools/check_versions.py` before releases and
after changes to shared build tools. Facts about the sources, written by `ninja badges`:

<!-- facts:begin (tools/badges.py) -->

- The split list has 3,704 entries for 2,741 source files; 2,637 of the files hold recovered functions.
- 6,054 functions are still `INCLUDE_ASM` lines (one per function, in the one file that owns it).
- 217 files contain 542 `#ifdef NON_MATCHING` blocks (drafts that do not match yet, plus blocks that only carry includes and notes).
- 73 split entries select `assembler: sn-min6`.
- The TU map has 3,036 translation units; confidence of its boundaries by bytes of `.text`: `exact` 14.5 %, `high` 2.9 %, `medium` 52.8 %, `low` 29.8 %.

<!-- facts:end -->

The calibration of the automatic pipeline is poor above 300 bytes: large hand-shaped gains do not make a new automatic
matching rate. Code completion alone does not establish owned-data completion.

## Key lessons

- Types decide most mismatches: callee arity and return use, float argument banks, PS2 vptr-first layouts, stack aggregates.
- Preserve float operand order, object lifetimes and inline-helper order; define inline helpers before their callers.
- Raw byte arithmetic on typed pointers (m2c) and lost HI/LO displacements were tool bugs, fixed in `ee_prep.py`/`autodecomp.py`.
- SN 1.36 remains the game default. Verified per-unit scheduling, divide and Sony compiler exceptions stay scoped;
  broad sweeps rarely help.
- Assembler padding differs per unit (six- vs seven-word short loops); verify each recipe on the full image, never globally.
- Equal offsets, zero stores or matching bytes do not prove field semantics or class identity; keep views `UNVERIFIED`.
- Orphan `<instruction>; nop` pieces are not code; they stay assembly and do not count against a TU.
- Boundaries below `exact` confidence are proposals; a run of related functions may hold several objects.
- Constants travel with their function; `.gcc_except_table` and shared data belong to whole objects.
- Small-function rates do not extrapolate to large functions; measure each new band before forecasting.

## Open problems

1. **Large functions** (over 300 bytes, most of the remaining code): register allocation, scheduling and cleanup lifetimes after
   typing; algorithmic search code; EE vector and mixed 64/128-bit code (the VU0 lowering of the pipeline covers few functions).
2. **Types and classes**: complete class sizes, semantic names for the vtables without RTTI name (`UnknownVtable_<address>`,
   see [CONTRIBUTING.md](../CONTRIBUTING.md#naming)), tagged payloads, iterator and serialization helpers. Layouts verified
   only by matched accesses.
3. **Library code**: Sony and RenderWare code may need the vendor compilers' idioms or may never match from source;
   uncertain boundaries remain leads from the Xbox build.
4. **Assembler provenance** is unresolved: six/seven-word loops mix inside libraries and no position or content rule
   explains them; `sn-min6` is a per-unit recipe, not a recovered rule.
5. **Data**: only part of the TUs have complete owned-data audits. Native CFI and shared pools still block several otherwise
   complete objects.
6. **Names and counterparts**: working names (`alias` lines of `config/SLUS_213.76/symbols.txt`), recovered prototypes
   (`include/ps2/prototypes.h`) and structures (`include/ps2/recovered_types.h`) are committed and edited by hand; no tool needs
   outside analysis data. An Xbox-to-PS2 counterpart map is an optional input that this repository does not ship.

## Next steps

1. Read the [matching handbook](matching-handbook.md) before each TU; reproduce its SN controls when changing a recipe.
2. Keep protected exact statuses, owned-data audits and the durable offline permuter. Preserve the reviewed near misses.
3. Convert automatic drafts into readable C++ (names and types improve) as classes are recovered; keep every function either
   exact or `// Unmatched:`.
4. Keep documentation current: this file, [history.md](history.md) (what happened), the other files in this directory
   (how the build and tools work). Numbers belong to `ninja badges`, not to prose.
