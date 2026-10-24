# Status

The goal, the method, the toolchain facts, the current numbers and the open problems. How to build and contribute is in
[README.md](../README.md) and [CONTRIBUTING.md](../CONTRIBUTING.md); how the pieces work is in the other files here; the
results history is in [history.md](history.md).

## Goal

Readable C/C++ source for the retail PS2 executable of Black (`SLUS_213.76`, the only first-class target: source, progress and routine checks; four more regional builds rebuild
from assembly and are checked before releases with `tools/check_versions.py`), organized into the original libraries and translation units (TUs), where every function carries explicit
evidence. Byte identity is the strongest tier and the matching build is mandatory in every commit; the other tiers say how
far a readable function is trusted.

| Tier | Meaning | Where it lives |
| --- | --- | --- |
| `exact` | the full rebuilt image stays byte-identical with the function compiled from source | a function without INCLUDE_ASM marker in its TU file ([units.md](units.md)); replaces the assembly in the build |
| `equivalent` | agrees with the original on recorded states with measured coverage; not a proof | `config/SLUS_213.76/equivalent.yaml`, candidate in the TU file's `#ifdef NON_MATCHING` block; never replaces assembly |
| `draft` | readable or machine draft with no evidence | `#ifdef NON_MATCHING` blocks in the TU files, marked `// Unmatched:` |

The same game code also ships on Xbox; this repository covers the PS2 side only. Names and types seen in the Xbox build are
leads, never proof of PS2 layouts.

## Method

1. **Full build from day one.** The executable is split into assembly and data that reassemble to the identical image;
   source replaces assembly inside that build, so linking, relocations and data are always real ([build.md](build.md)).
2. **Original TUs.** Boundaries come from unwind frames, the constructor list, library strings, code style and data joins
   (`tools/build/tus.py`, which `ninja` runs into the ignored `build/SLUS_213.76/tus.yaml`; [tus.md](tus.md)). Match whole files where the evidence is exact.
3. **One check for exactness**: `ninja` ends with `OK`. No per-function proof journals.
4. **Automate the routine path**: m2c draft, compile flag variants, relocation-aware scoring, permuter, family cloning
   ([pipeline.md](pipeline.md)). People spend their time on types, classes and the functions the pipeline cannot do.
5. **Parallel by file.** One person owns one TU or module at a time; shared headers (`include/ps2/`) have one owner each and
   generators own generated headers.
6. **Private inputs stay private.** Game bytes, generated assembly and data, compilers and build output are ignored by Git.

## Toolchain facts

| Piece | Choice |
| --- | --- |
| Compilers | `ee-gcc2.95.3-136` (SN build 1.36) with `-O2 -G0 -snas` for game, Kynapse, animation, physics, RenderWare Core/Audio, apt, libc stdio; `ee-gcc2.9-991111-01 -O2 -G0` (SN driver, GNU assembler) for the Sony libraries (`sd` saves: libipu/libmpeg, libdbc, libdma, libm, libcdvd, libmc2, libkernl, libstdc++ type info, libgs) |
| Scoped scalar exception | three audio getters use Sony `ee-gcc2.96` with `-mno-handle-ee-div-pipeline-bug`; measured divide controls scope this choice without identifying the original whole-TU compiler |
| Per-TU flag variants | `-O1` (about 130 functions), `-G8` where gp-relative small data is used, `-fno-schedule-insns`, `-fbyte-bool`, `-fno-rtti`, `-x c++`, `-ffunction-sections` (merged TUs), `-mvu0-use-vf0-vf31` / `-vf16` (VU0 inline helpers) |
| Assemblers | untouched compiler assembler (`-snas`) by default; `--assembler=sn-min6` (hash-guarded derivative of Ps2EeAs 1.9.25.758 that pads short loops to six words, reproduced by `tools/build/patch_ps2eeas.py`) on verified units only; `gas-2.40`, `gas-2.40-fix`, `sony-2.9`, `sn-2.73a` are explicit experiments. The 65 splits that select `assembler: sn-min6` in `config/SLUS_213.76/splits.yaml` use it because it reproduces their bytes, not because a recovered rule says the original used it: treat that choice as weak evidence (open problem 4) |
| Assembly files | EE GNU assembler 2.10 (from the `ee-gcc2.96` archive); short backward branches stay `.word`; gp-relative symbols need `.extern sym, 1` |
| Linker | mainline GNU `ld` 2.40 (`binutils-mipsel-linux-gnu`), generated script with `SORT_BY_NAME` input sections; `tools/build/pack_elf.py` writes the retail container (`e_flags 0x20924001`) |
| Everything else | splat/spimdisasm/rabbitizer split, Ninja, m2c (`-t mipsee-gcc-c`), decomp-permuter; names, prototypes and types are committed, hand-maintained files (`config/SLUS_213.76/symbols.txt`, `include/ps2/`) |
| Running the tools | the compilers are decomp.me archives pinned by SHA-256 (`config/toolchain-*.json`); the Windows programs run under wibo, the Sony tools are 32-bit Linux programs (`tools/toolchain.py`, [build.md](build.md)) |

## Source layout

`src/<library>/<name>.c|cpp`, one file per translation unit that has recovered code (`tu_<address>`, plus `_<address>` for
the further files of a TU that cannot be one: other flags, language or constants) or a descriptive name inherited from the
class or module. The file lists every function of the TU, the unrecovered ones as INCLUDE_ASM lines; drafts are
`#ifdef NON_MATCHING` blocks in it. TUs without recovered code have no file. Libraries: `game`, `apt` (EA Apt/Flash UI), `kynapse`,
`animation`, `physics`, `rw_core`, `rw_audio`, `sony`, `libc`. Compiler-emitted inline and template copies (link-once code) live in `src/<owner>/inline/` of the library that owns them (owners are computed into `build/SLUS_213.76/inline_owners.txt`). `config/SLUS_213.76/splits.yaml`
lists the files with their address ranges and flags; `tools/build/layout.py` owns the naming rules.

Headers follow the libraries: `include/<library>/` for `game`, `kynapse`, `animation`, `physics`, `rw_core`, `rw_audio`
and `apt`, and `include/ps2/` for helpers shared by all of them (EE types, VU0 operations, the draft prelude). Class
views (`include/game/classes/`, `include/kynapse/classes/`) sit beside the hand-written headers; recovered layouts that several files share
are plainly named headers there, the others are defined in the one source file that uses them.

## Current state (USA retail, `ninja progress`)

Everything below rebuilds byte-identical. Routine work checks USA only; the last all-versions check (`tools/check_versions.py`) passed for all five retail images (USA, Europe, Europe/Australia, Korea, Japan). Run it before releases and after changes to shared build tools. The same numbers feed the badges and the table in the README (`ninja badges`, `progress/`).

| Library (`src/`) | Functions | From source | Bytes (`.text` spans) | From source | Complete TUs |
| --- | ---: | ---: | ---: | ---: | ---: |
| game | 6,800 | 3,016 (44.4 %) | 1,470,016 | 179,840 (12.2 %) | 738 / 1,566 |
| kynapse | 1,558 | 1,277 (82.0 %) | 305,704 | 137,552 (45.0 %) | 614 / 735 |
| animation | 385 | 211 (54.8 %) | 77,904 | 27,528 (35.3 %) | 28 / 74 |
| rw_audio | 754 | 309 (41.0 %) | 109,560 | 23,368 (21.3 %) | 36 / 112 |
| apt | 777 | 223 (28.7 %) | 280,000 | 12,400 (4.4 %) | 57 / 209 |
| sony | 756 | 274 (36.2 %) | 142,096 | 9,000 (6.3 %) | 147 / 221 |
| rw_core | 449 | 85 (18.9 %) | 181,416 | 4,744 (2.6 %) | 7 / 44 |
| libc | 213 | 75 (35.2 %) | 70,472 | 4,088 (5.8 %) | 3 / 22 |
| physics | 207 | 93 (44.9 %) | 78,296 | 11,864 (15.2 %) | 6 / 53 |
| **Total** | **11,899** | **5,563 (46.75 %)** | **2,715,464** | **410,384 (15.11 %)** | **1,636 / 3,036** |

Evidence tiers: `exact` 5,563 functions / 410,384 B, `equivalent` 14 / 984 B, `draft` 6,322 / 2,304,096 B. Complete TUs
include many one- or two-function TUs (116,600 B in code-complete TUs). Of 2,671 splits (2,656 source files), 48,498 functions are INCLUDE_ASM lines and 189 files hold NON_MATCHING drafts. TU confidence by bytes: `exact` 14.5 %, `high` 2.9 %, `medium` 52.8 %, `low` 29.8 %.
The calibration of the automatic pipeline remains poor above 300 B; the large hand-shaped gains do not establish a new
automatic matching rate. Code completion alone does not establish owned-data completion.

The table above is the image measure of `ninja progress` (`.text` spans including alignment padding and the 672 orphan
`<instruction>; nop` pieces). The headline code figure uses objdiff's definition, matched function bytes / total function
bytes without padding and orphans: 14.95 % (401,428 / 2,685,060 bytes), equal to `ninja report`; see
[progress-reports.md](progress-reports.md).

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
- Equivalent-tier evidence needs measured original-code coverage and reviewed ABI, otherwise it stays a draft.

## Open problems

1. **Large functions** (over 300 B, 76 % of the rest): register allocation, scheduling and cleanup lifetimes after typing;
   algorithmic search code; EE vector and mixed 64/128-bit code (VU0 lowering covers only 89 functions).
2. **Types and classes**: complete class sizes, semantic names for the 376 unnamed vtables, tagged payloads, iterator
   and serialization helpers. Layouts verified only by matched accesses.
3. **Library code**: Sony and RenderWare code may need the vendor compilers' idioms or may never match from source;
   physics has six code/data-audited complete mapped TUs; uncertain boundaries remain leads from the Xbox build.
4. **Assembler provenance** is unresolved: six/seven-word loops mix inside libraries and no position or content rule
   explains them; `sn-min6` is a per-unit recipe, not a recovered rule.
5. **Equivalence track**: the gate for broad coverage is not passed (1,429 of 6,512 game functions have at least 20
   recorded states, 3,257 needed); the pilot reached 14 of 50 functions, none above 1 KB; no nonmatching ELF and no
   whole-program frame agreement.
6. **Data**: 27 additional mapped TUs have complete owned-data audits; this is not a repository-wide audit. Native CFI
   and shared pools still block several otherwise complete objects.
7. **Names and counterparts**: working names (`alias` lines of `config/SLUS_213.76/symbols.txt`), recovered prototypes
   (`include/ps2/prototypes.h`) and structures (`include/ps2/recovered_types.h`) are committed and edited by hand; no tool needs
   outside analysis data. An Xbox-to-PS2 counterpart map is an optional input that this repository does not ship.

## Next steps

1. Read the [matching handbook](matching-handbook.md) before each TU; reproduce its SN controls when changing a recipe.
2. Keep one owner per TU, protected exact statuses, owned-data audits and the durable offline permuter. Preserve the
   reviewed near misses.
3. Convert `auto` drafts into readable C++ (`provenance` stays; names and types improve) as classes are recovered; keep
   every function either `exact` or `// Unmatched:`.
4. Continue equivalence collection only for functions the matching track cannot reach: more savestates and gameplay
   coverage, then a nonmatching ELF.
5. Keep documentation current: this file (state table via `ninja progress` and `python3 tools/progress.py --libraries`),
   [history.md](history.md) (results), the other files in this directory (how the build and tools work).

## Recent results: the last depth pass

The latest pass spent about 40 hours of focused work on the hardest remaining functions, with a permuter running beside it,
and ended at a fixed time rather than when throughput declined. Cumulative from 5,444 exact functions / 378,560 text-span
bytes:

| Hours | Functions gained | Text-span bytes gained | Data-audited TUs | New matches >1 KB | Permuter search wins | Bytes / hour |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 10 | +52 | +15,664 | 24 | 2 | 3 | 1,565 |
| 20 | +107 | +27,384 | 26 | 2 | 3 | 1,367 |
| 30 | +112 | +29,064 | 26 | 2 | 3 | 969 |
| 40 | +119 | +31,824 | 27 | 3 | 4 | 795 |

The gain is **119 functions / 31,824 text-span bytes**, with every previously exact address retained. Code-complete TUs
increased by 28; 27 of them are also data-audited complete. New large exact bodies are BuildPose (1,944 B),
InitializeSkeleton (1,464 B) and PredictContacts (1,508 B). Early gains came from shared loop indices, reference-return
views, helper visibility and native capture order; later ones from scoped alias/null-branch and scalar-divide recipes and from
real expression lifetimes (the 1,508-byte predictor) and cursor scopes (the 732-byte animation builder). Preserve real
operations, ABI widths, fourth-lane payloads and cleanup extents; a lower instruction score alone is insufficient.

The durable permuter searched the sub-30-instruction queue in descending size order for hours per hard function, keeping
the best candidates across restarts. Four reviewed winning searches supplied five integrated functions; a helper search
fixed two callers. Manual matches, artificial wrappers and uninitialized-value candidates get no permuter credit.

Deep-TU endpoints: animation pose operations 16/19 exact with all native owned data, including 920 unwind bytes; physics
scene 21/26 exact with its 80 native storage bytes; audio 91/107 exact with 11,420/11,604 estimated owned-data bytes
source-backed; Kynapse steering 13/14 exact. The remaining allocation, scheduling, native unwind and shared-pool
obstructions have precise `// Unmatched:` notes in source. No source was promoted to the equivalent tier.

Projection: 2,305,080 text bytes remain. At the final rate (about 276 B/hour in the last interval) this is not a completion
estimate; depth produced substantial new large matches but did not remove the large-function bottleneck.
