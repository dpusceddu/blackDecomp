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
| Scoped scalar exception | three audio getters use Sony `ee-gcc2.96` with `-mno-handle-ee-div-pipeline-bug`; measured divide controls scope this choice without identifying the original whole-TU compiler |
| Per-TU flag variants | `-O1` (about 130 functions), `-G8` where gp-relative small data is used, `-fno-schedule-insns`, `-fbyte-bool`, `-fno-rtti`, `-x c++`, `-ffunction-sections` (merged TUs), `-mvu0-use-vf0-vf31` / `-vf16` (VU0 inline helpers) |
| Assemblers | untouched compiler assembler (`-snas`) by default; `--assembler=sn-min6` (hash-guarded derivative of Ps2EeAs 1.9.25.758 that pads short loops to six words) on verified units only; `gas-2.40`, `gas-2.40-fix`, `sony-2.9`, `sn-2.73a` are explicit experiments. Units that use an alternative carry `assembler_evidence: weak` |
| Assembly files | EE GNU assembler 2.10 from the catalog; short backward branches stay `.word`; gp-relative symbols need `.extern sym, 1` |
| Linker | mainline GNU `ld` 2.40, generated script with `SORT_BY_NAME` input sections; `tools/pack_elf.py` writes the retail container (`e_flags 0x20924001`) |
| Everything else | splat/spimdisasm/rabbitizer split, Ninja, m2c (`-t mipsee-gcc-c`), decomp-permuter, Ghidra export for names |
| Isolation rule | every SDK, compiler or binutils binary must run only in the build backend (`tools/sandbox.py`, `.local/config.json`); never on the host |

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
| game | 6,650 | 2,908 (43.7 %) | 1,460,176 | 176,864 (12.1 %) | 631 / 1,435 |
| kynapse | 905 | 687 (75.9 %) | 257,240 | 107,512 (41.8 %) | 24 / 82 |
| animation | 350 | 195 (55.7 %) | 69,680 | 26,128 (37.5 %) | 12 / 39 |
| rw_audio | 754 | 309 (41.0 %) | 109,560 | 23,368 (21.3 %) | 36 / 112 |
| apt | 633 | 129 (20.4 %) | 267,744 | 7,520 (2.8 %) | 30 / 177 |
| sony | 756 | 274 (36.2 %) | 142,096 | 9,000 (6.3 %) | 147 / 221 |
| rw_core | 449 | 85 (18.9 %) | 181,416 | 4,744 (2.6 %) | 7 / 44 |
| libc | 213 | 75 (35.2 %) | 70,472 | 4,088 (5.8 %) | 3 / 22 |
| physics | 206 | 93 (45.1 %) | 78,240 | 11,864 (15.2 %) | 6 / 52 |
| linkonce | 983 | 808 (82.2 %) | 78,840 | 39,296 (49.8 %) | 740 / 852 |
| **Total** | **11,899** | **5,563 (46.75 %)** | **2,715,464** | **410,384 (15.11 %)** | **1,636 / 3,036** |

Evidence tiers: `exact` 5,563 functions / 410,384 B, `equivalent` 14 / 984 B, `draft` 6,322 / 2,304,096 B. Complete TUs
include many one- or two-function TUs (116,600 B in code-complete TUs). Of 2,919 units: 2,316 `auto`, 347 `campaign`, 255
`imported`, 1 `equivalent` provenance. TU confidence by bytes: `exact` 14.5 %, `high` 2.9 %, `medium` 52.8 %, `low` 29.8 %.
The earlier stock-output calibration remains poor above 300 B; the large hand-shaped gains do not establish a new
automatic matching rate. Code completion alone does not establish owned-data completion.

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
   physics now has six code/data-audited complete mapped TUs; uncertain boundaries remain Xbox-map leads.
4. **Assembler provenance** is unresolved: six/seven-word loops mix inside libraries and no position or content rule
   explains them; `sn-min6` is a per-unit recipe, not a recovered rule.
5. **Equivalence track**: Gate 2 not passed (1,429 of 6,512 game functions have at least 20 recorded states, 3,257 needed);
   the pilot reached 14 of 50 functions, none above 1 KB; no nonmatching ELF and no whole-program frame agreement.
6. **Data**: 27 additional mapped TUs have complete owned-data audits; this is not a repository-wide audit. Native CFI
   and shared pools still block several otherwise complete objects.
7. Ghidra export and the counterpart map depend on private pages and the companion project (`docs/inputs.md`, `README.md`).

## Next steps

1. Read `docs/matching-handbook.md` before each TU; reproduce its SN controls when changing a recipe.
2. The fixed 40-agent-hour final campaign is complete; results and remaining limits are below. Future matching should
   retain one TU owner, protected exact statuses, owned-data audits and the durable offline permuter. Preserve the
   reviewed near misses; the broad Xbox import and unfinished deep TUs still require further work.
3. Convert `auto` drafts into readable C++ (`provenance` stays; names and types improve) as classes are recovered;
   keep every function either `exact` or `// Unmatched:`.
4. Continue equivalence collection only for functions the matching track cannot reach: more savestates and gameplay
   coverage, then the 50-function pilot target and a nonmatching ELF.
5. Keep documentation current: this file (state table via `ninja progress` and `python3 tools/progress.py --libraries`),
   `docs/history.md` (results), `docs/*.md` (how the build and tools work).

History of phases, campaigns and studies: `docs/history.md`. Inputs and variants: `docs/inputs.md`.

## Final depth campaign (2026-10-24)

Four occupied agent slots ran for the fixed ten-hour search window, about 40 aggregate agent-hours including tool waits;
worker permuter runtime is separate. The campaign ran to its budget rather than stopping on declining throughput.
Every checkpoint below is cumulative from 5,444 exact functions / 378,560 text-span bytes. TU counts here mean newly
complete mapped TUs audited through owned data; uncertain original boundaries remain proposals.

| Agent-hours | Functions gained | Text-span bytes gained | Data-audited TUs | New matches >1 KB | Permuter search wins | Bytes / agent-hour |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 10 | +52 | +15,664 | 24 | 2 | 3 | 1,565 |
| 20 | +107 | +27,384 | 26 | 2 | 3 | 1,367 |
| 30 | +112 | +29,064 | 26 | 2 | 3 | 969 |
| 40 | +119 | +31,824 | 27 | 3 | 4 | 795 |

The final gain is **119 functions / 31,824 text-span bytes**, with every previously exact address retained.
Code-complete TUs increased by 28; 27 are also newly data-audited complete. The additional Follower TU has all 18 bodies
exact but its native 648-byte unwind input remains assembly-backed. New large exact bodies are BuildPose (1,944 B),
InitializeSkeleton (1,464 B), and PredictContacts (1,508 B). Instruction-body sizes differ from original text spans.

The handbook was researched first and extended with measured recipes: 35 exact retail baselines, plus separately
identified synthetic controls and one near-body/native-CFI diagnostic. Early gains came from shared loop indices,
reference-return views, helper visibility and native capture order; the middle interval added scoped alias/null-branch
and scalar-divide recipes. The final interval's effective changes were genuine expression/CSE lifetimes for the
1,508-byte predictor and raw-base/input/output cursor scopes for the 732-byte animation builder. Preserve real operations,
ABI widths, fourth-lane payloads and cleanup extents; a lower instruction score alone is insufficient.

The durable offline permuter received the under-30-instruction queue in descending function-size order, including
status-mismatch candidates. It ran hours per hard function, retained best candidates across restarts, and used three
final disjoint lanes within the original two-CPU/two-GiB container cap. Four reviewed winning searches supplied five
integrated functions; a helper search fixed two callers. Manual matches, raw semantic failures, artificial wrappers and
uninitialized-value candidates receive no permuter-win credit. Feeding the queue does not mean every entry was attempted.
The final service receipt records 719,447 attempts, 9.643 container hours and 12.726 accumulated function-search hours.
The build backend stopped cleanly at the fixed deadline; reviewed seeds and durable checkpoints are retained separately from
rejected diagnostics.

Deep-TU endpoints: animation pose operations 16/19 exact with all native owned data, including 920 unwind bytes, exact;
physics scene 21/26 exact with its 80 native storage bytes exact; audio 91/107 exact with 11,420/11,604 estimated owned-data
bytes source-backed; Kynapse steering 13/14 exact. The remaining allocation, scheduling, native unwind and shared-pool
obstructions have precise source notes and retained private candidates. No source was promoted to equivalent tier.
Recorded-state checks and artificial diagnostics remain separate; Gate 2 and whole-program frame agreement remain open.

The Xbox import is partial: 281 eligible Xbox-exact functions (120 physics, 161 animation), with 13 newly exact eligible
ports / 3,300 instruction-body bytes. The supplied 75-function counterpart map rose from 41 to 47 exact; seven additional
exact counterparts were independently bound, giving a known-exact lower bound of 54/281 (19.2%). Two more have routed PS2
drafts; up to 225 remain inventory-only. The 278 extracted reference bodies are not 278 translated ports. Large animation
and storage-layout gains whose parent Xbox bodies are drafts are excluded from this eligible-source denominator.

Validation: all five retail images are byte-identical, 100 build/tooling tests and 312 additional tool tests pass, and the
complete handbook suite plus affected scene controls pass. Existing corrected EE-harness binaries passed Gate 1, including
1,506 semantic assertions, decoder/source checks, compiled fixtures, VU microprogram checks and all retail bytechecks.
Public-file checks found no machine-specific details or binary inputs; generated/private artifacts remain ignored.

Isolation deviation: an agent ran native C++/CMake harness and diagnostic builds on the host, contrary to the rule. No PS2
SDK/compiler/assembler ran on the host. Further native compilation stopped; Gate 1 now requires existing binaries and
cannot implicitly build them. The build backend has no authorized native harness compiler, so rebuilding those native
binaries remains a setup limitation rather than an isolation workaround.

Projection: 2,305,080 text bytes remain. The cumulative rate of about 795 B/agent-hour would imply roughly
2,898 additional agent-hours under an unrealistically flat rate; the final interval achieved only about 276 B/agent-hour.
Depth produced substantial new large matches but did not remove the large-function bottleneck. These rates are not a
completion estimate, and the unfinished Xbox import and deep TUs must not be described as complete.
