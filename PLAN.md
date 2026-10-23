# Black PS2 decompilation: plan

## Goal

Readable C/C++ source for the retail PS2 executable of Black (`SLUS_213.76`), organized into the original libraries and
translation units (TUs), where every function carries explicit evidence. Byte identity is the strongest tier and the
matching build is mandatory in every commit; the other tiers say how far a readable function is trusted.

| Tier | Meaning | Where it lives |
| --- | --- | --- |
| `exact` | the full rebuilt image stays byte-identical with the function compiled from source | `status: source` in `config/units.yaml`; replaces the assembly in the build |
| `equivalent` | agrees with the original on recorded states with measured coverage; not a proof | function `evidence:` in `units.yaml`, source under `src/<library>/nonmatching/` (or in a unit); never replaces assembly |
| `draft` | readable or machine draft with no evidence | the rest of `src/`, marked `// Unmatched:` |

The same code ships on Xbox and PS2; this repository is the PS2 side only. Counterparts from the Xbox build (Ghidra
`default.xbe`) are leads for names and types, never proof of PS2 layouts.

## Method

1. **Full build from day one.** The executable is split into assembly and data that reassemble to the identical image;
   source replaces assembly inside that build, so linking, relocations and data are always real (`docs/build.md`).
2. **Original TUs.** Boundaries come from unwind frames, the constructor list, library strings, code style and data
   joins (`tools/tus.py`, `config/tus.yaml`, `docs/tus.md`). Match whole files where the evidence is exact.
3. **One check for exactness**: `ninja` ends with `OK`. No per-function proof journals.
4. **Automate the routine path**: m2c draft, compile variants in the build backend, relocation-aware scoring, permuter,
   family cloning (`docs/pipeline.md`). Agents spend their time on types, classes and the functions the pipeline cannot do.
5. **Parallel by file.** One agent owns one TU or module; shared headers (`include/ps2/`, `include/classes/`,
   `include/recovered/`) have one owner each and generators own generated headers.
6. **Private inputs stay private.** Game bytes, generated assembly and data, compilers, savestates and build output are
   ignored by Git (`orig/ asm/ data/ build/ .local/ .venv/`).

## Toolchain facts

| Piece | Choice |
| --- | --- |
| Compilers | `ee-gcc2.95.3-136` (SN build 1.36) with `-O2 -G0 -snas` for game, Kynapse, animation, physics, RenderWare Core/Audio, apt, libc stdio; `ee-gcc2.9-991111-01 -O2 -G0` (SN driver, GNU assembler) for the Sony libraries (`sd` saves: libipu/libmpeg, libdbc, libdma, libm, libcdvd, libmc2, libkernl, libstdc++ type info, libgs) |
| Per-TU flag variants | `-O1` (about 130 functions), `-G8` where gp-relative small data is used, `-fno-schedule-insns`, `-fbyte-bool`, `-fno-rtti`, `-x c++`, `-ffunction-sections` (merged TUs), `-mvu0-use-vf0-vf31` / `-vf16` (VU0 inline helpers) |
| Assemblers | untouched compiler assembler (`-snas`) by default; `--assembler=sn-min6` (hash-guarded derivative of Ps2EeAs 1.9.25.758 that pads short loops to six words) on verified units only; `gas-2.40`, `gas-2.40-fix`, `sony-2.9`, `sn-2.73a` are explicit experiments. Units that use an alternative carry `assembler_evidence: weak` |
| Assembly files | EE GNU assembler 2.10 from the catalog; short backward branches stay `.word`; gp-relative symbols need `.extern sym, 1` |
| Linker | mainline GNU `ld` 2.40, generated script with `SORT_BY_NAME` input sections; `tools/pack_elf.py` writes the retail container (`e_flags 0x20924001`) |
| Everything else | splat/spimdisasm/rabbitizer split, Ninja, m2c (`-t mipsee-gcc-c`), decomp-permuter, Ghidra export for names |
| Isolation | every SDK, compiler or binutils binary runs only in the build backend (`tools/sandbox.py`, `.local/config.json`); never on the host |

## Source layout

`src/<library>/<name>.c|cpp`, one file per recovered TU (`tu_<address>`, plus `_<unit address>` for units that do not
start the TU) or a descriptive name inherited from the class or module. Units that are deliberately split keep separate
files. `src/<library>/nonmatching/` holds drafts that no unit uses. Libraries: `game`, `apt` (EA Apt/Flash UI), `kynapse`,
`animation`, `physics`, `rw_core`, `rw_audio`, `sony`, `libc`, `linkonce` (link-once area). `config/units.yaml` records per
unit `library`, `provenance` (`imported`, `auto`, `campaign`, `equivalent`) and `tier`; `tools/relayout.py` and
`tools/layout.py` own the rules. Headers stay in `include/`; the library directories there are `kynapse`, `animation`,
`physics`, `rw_core`, `rw_audio`, `game`, `ps2`, `classes` (generated), `recovered` (generated), and the older
`campaign`, `context`, `mod` directories.

## Current state (USA retail, `ninja progress`)

Everything below rebuilds byte-identical; all five retail images pass (USA, EU, EU/AU, Korean, Japanese).

| Library (`src/`) | Functions | From source | Bytes (`.text` spans) | From source | Complete TUs |
| --- | ---: | ---: | ---: | ---: | ---: |
| game | 6,650 | 2,897 (43.6 %) | 1,460,176 | 173,528 (11.9 %) | 620 / 1,435 |
| kynapse | 905 | 679 (75.0 %) | 257,240 | 104,784 (40.7 %) | 19 / 82 |
| animation | 350 | 180 (51.4 %) | 69,680 | 17,928 (25.7 %) | 6 / 39 |
| rw_audio | 754 | 250 (33.2 %) | 109,560 | 14,496 (13.2 %) | 36 / 112 |
| apt | 633 | 129 (20.4 %) | 267,744 | 7,520 (2.8 %) | 30 / 177 |
| sony | 756 | 274 (36.2 %) | 142,096 | 9,000 (6.3 %) | 147 / 221 |
| rw_core | 449 | 85 (18.9 %) | 181,416 | 4,744 (2.6 %) | 7 / 44 |
| libc | 213 | 75 (35.2 %) | 70,472 | 4,088 (5.8 %) | 3 / 22 |
| physics | 206 | 67 (32.5 %) | 78,240 | 3,176 (4.1 %) | 0 / 52 |
| linkonce | 983 | 808 (82.2 %) | 78,840 | 39,296 (49.8 %) | 740 / 852 |
| **Total** | **11,899** | **5,444 (45.75 %)** | **2,715,464** | **378,560 (13.94 %)** | **1,608 / 3,036** |

Evidence tiers: `exact` 5,444 functions / 378,560 B, `equivalent` 14 / 984 B, `draft` 6,441 / 2,335,920 B. Complete TUs
include many one- or two-function TUs (91,400 B in complete TUs). Of 2,954 units: 2,366 `auto`, 331 `campaign`, 256
`imported`, 1 `equivalent` provenance. TU confidence by bytes: `exact` 14.5 %, `high` 2.9 %, `medium` 52.8 %, `low` 29.8 %.
About 76 % of the remaining bytes are in functions over 300 B and no function above 1 KB has matched from stock output
except the 2,128-byte `ParameterTables` constructor. Automatic rates among the remaining real functions: under 100 B
about 5 %, 100-300 B about 1 %, above 300 B under 0.3 %.

## Key lessons

- Types decide most mismatches: callee arity and return use, float argument banks, PS2 vptr-first layouts, stack aggregates.
- Preserve float operand order, object lifetimes and inline-helper order; define inline helpers before their callers.
- Raw byte arithmetic on typed pointers (m2c) and lost HI/LO displacements were tool bugs, fixed in `ee_prep.py`/`autodecomp.py`.
- SN 1.36 `-O2 -G0 -snas` is right for the game; compiler or flag sweeps rarely help (only SN 1.36 reproduced all controls).
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
   physics has no complete TU and its boundaries are leads from the Xbox map.
4. **Assembler provenance** is unresolved: six/seven-word loops mix inside libraries and no position or content rule
   explains them; `sn-min6` is a per-unit recipe, not a recovered rule.
5. **Equivalence track**: Gate 2 not passed (1,429 of 6,512 game functions have at least 20 recorded states, 3,257 needed);
   the pilot reached 14 of 50 functions, none above 1 KB; no nonmatching ELF and no whole-program frame agreement.
6. **Data**: owned data completion is not audited per TU; `.rodata` migration covers 74 %.
7. Ghidra export and the counterpart map depend on private pages and the companion project (`docs/inputs.md`, `README.md`).

## Next steps

1. Write `docs/matching-handbook.md` (planned): the working method for a TU, typical mismatch causes with fixes, the unit
   claim and settle workflow, and which helpers to reuse. Agents start from it.
2. Run the final matching campaign on exact-boundary TUs with coherent classes, game and Kynapse first, using one agent per
   TU, a coordinator for headers and `units.yaml`, and `tools/merge_units.py` for integration. Stop by the throughput rule
   (below 1,500 B per agent-hour or two consecutive declines).
3. Convert `auto` drafts into readable C++ (`provenance` stays; names and types improve) as classes are recovered;
   keep every function either `exact` or `// Unmatched:`.
4. Continue equivalence collection only for functions the matching track cannot reach: more savestates and gameplay
   coverage, then the 50-function pilot target and a nonmatching ELF.
5. Keep documentation current: this file (state table via `ninja progress` and `python3 tools/progress.py --libraries`),
   `docs/history.md` (results), `docs/*.md` (how the build and tools work).

History of phases, campaigns and studies: `docs/history.md`. Inputs and variants: `docs/inputs.md`.
