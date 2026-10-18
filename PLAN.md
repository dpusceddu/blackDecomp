# Black PS2 matching decompilation: implementation plan

Goal: a source tree that rebuilds the retail PS2 executable of Black **byte for byte**, organized into
the original translation units (TUs), produced mostly by agents with standard decompilation tooling.
Progress is measured in one place: the bytes of the full rebuilt executable that come from C/C++ rather
than assembly.

This repository starts as a subdirectory of `the companion project` and becomes its own Git repository. It does not
depend on `the companion project` code at build time; useful pieces are copied in, not imported.

## Principles

1. **Full build from day one.** The executable is split into assembly and data that reassemble to the
   identical file. Every later change replaces assembly with C/C++ inside that full build, so linking,
   relocations and data are always real. No isolated-function placement.
2. **Original translation units.** Recover file boundaries early and match whole files: shared constants,
   static helpers, inline functions and data ordering then come out right naturally.
3. **One evidence type.** A function is done when the full build stays identical with it in C/C++. No
   per-function provenance records, cross-platform proof or journals.
4. **Automate the routine path.** Decompile with m2c, compile, diff and permute by script. Agents spend
   their attention on types, class layouts and the functions the pipeline cannot do.
5. **Parallel by file.** One agent owns one TU at a time. Shared headers have a single owner.
6. **Private inputs stay private.** Game executables, generated assembly, extracted data, compilers and
   build output are ignored by Git. Only hashes, configuration, symbols and authored source are committed.

## Inputs

| Input | Use |
| --- | --- |
| `SLUS_213.76` (USA retail), SHA-256 `141b0520…6254ffe4c` | Primary matching target unless a variant with symbols changes that (Phase 0) |
| Other variants (triaged in `docs/inputs.md`) | PAL, Korean and Japanese retail: layout and TU-boundary evidence (member offsets shift by 0x80 in about a fifth of the code); EU/AU: a second image for shiftability tests; USA beta (2005-08-16) and demos: class-name and ordering hints. No variant has symbols. |
| Ghidra `/SLUS_213.76` | Recovered names, prototypes and types, exported to symbol files |
| SN GCC 2.95.3 build 1.36 (`ee-gcc2.95.3-136`, decomp.me compiler release) | Game compiler; `-O2 -G0 -snas` reproduced 45/52 sample bodies in `the companion project` |
| `the companion project` results | 65 PS2-exact game functions, 213 PS2-exact Kynapse bodies, the Xbox-to-PS2 counterpart map, the VU0 inline-assembly study, RTTI-derived class names |

Executable layout (USA): `.text` 0x100000–0x396f48 (2.7 MB), `.vutext` (152 KB of VU microcode),
`.data`, `.rodata`, `.gcc_except_table`, `.lit4`, `.sdata`/`.sbss` (so some files use gp-relative small
data and are not `-G0`), `.bss`, and 88 `.DVP.overlay.*` sections. There are no symbols. The IOP
modules (`*.IRX`, including RenderWare Audio `RWA.IRX`) are separate binaries and out of scope.

## Repository layout

```
black-decomp/
  README.md            how to set up, build and pick work
  AGENTS.md            short agent rules (CLAUDE.md symlinks to it)
  PLAN.md              this file
  configure.py         writes build.ninja from config/
  config/
    SLUS_213.76.yaml   splat configuration (segments, TU splits)
    symbols.txt        address = name, type, size (from Ghidra export and recovered names)
    units.yaml         TU list: path, address ranges, flags, status
    checksums.sha1     hashes of supported input executables
  include/             shared headers (single owner)
  src/                 recovered C/C++, mirroring original TU paths where known
  tools/               setup, container compiler wrapper, m2c/permuter wrappers, progress, next-work
  asm/  data/  build/  orig/  .local/    ignored (generated or private)
```

## Toolchain

| Piece | Choice | Notes |
| --- | --- | --- |
| Splitting | splat (`splat64`), spimdisasm, rabbitizer | splat supports PS2/R5900; pin versions |
| Assembler for asm files | EE GNU assembler 2.10-ee from the compiler catalog | Reassembles the whole executable identically. Short backward branches (five words or fewer) are emitted as raw `.word` (the assembler rejects them); splat already emits undecoded words as `.word`. The assembler has no `.incbin` and no `%gp_rel`, is quadratic in file size (the code is cut into chunks of about 20,000 lines) and needs `.extern sym, 1` for gp-relative accesses |
| C/C++ compiler | SN `ee-gcc2.95.3-136` under Wine through the build backend | Same model as `the companion project/tools/ps2`; never run it directly on the host |
| Compiler output assembler | SN assembler (`-snas`) inside the same container | It mattered for matching in `the companion project` tests |
| Linker | Mainline GNU `ld` 2.40 (Debian `binutils-mipsel-linux-gnu` 2.40-2cross2, signed archive) | Per-section ordering from a generated script (sorted input-section names, not one statement per object); `tools/pack_elf.py` writes the retail container and `e_flags` `0x20924001`. SN-assembled objects need their symbol table normalised (`tools/elfobj.py`) before ld accepts them |
| Build | `configure.py` → Ninja | Standard decomp template; one command builds and verifies |
| Decompiler | m2c, little-endian MIPS GCC target | EE-specific instructions (MMI, 128-bit moves, VU0) will often need agent work |
| Diff and scoring | objdiff (CLI and report), asm-differ | objdiff report gives per-TU and overall progress |
| Search | decomp-permuter | Only for near-misses; run locally, never upload game code |
| Knowledge | Ghidra `/SLUS_213.76` via a scripted export | Names and types flow both ways |

Compilation runs either on the Linux laptop with a local container runtime or on the existing private
worker, selected in `.local/config.json`. Both keep the binary isolated.

## Phases

Each phase ends with a check that a fresh agent can run.

### Phase 0: inputs and environment (1–2 sessions)

- `tools/inputs.py` reads every procured variant and reports: SHA-256, sections, whether `.symtab`,
  `.strtab`, `.mdebug` (STABS) or DWARF sections exist, compiler banners, source file names in strings,
  assert messages with paths and line numbers, and how its code compares with the USA build.
- **Decide the target.** If a variant has symbols and is close to retail, it may become the primary
  target or at least the main source of names, types and file boundaries.
- `tools/compile.py` builds a trivial C and C++ file with SN 1.36 in the container. It checks that the
  output is an ELF object that GNU `ld` accepts.
- Set up the repo: `git init`, `.gitignore`, pinned Python requirements, the binutils check, and an
  ignore entry for `black-decomp/` in the parent repository.

Exit: `tools/inputs.py` summary committed (hashes and findings only); the container compiles both test
files; binutils assembles a sample of EE instructions identically.

### Phase 1: the identical rebuild (done)

Result: `ninja` rebuilds the whole boot ELF byte for byte (SHA-256 equal to retail) for USA, EU/AU, EU, Korean and
Japanese retail, in about 20 s of which 8 s are the build backend. Facts that changed the plan:

- ld cannot write the retail container (section-header order, non-loaded `.DVP.*`/`.reginfo`/`.debug_str`, `e_flags`),
  so `tools/pack_elf.py` re-packs ld's linked sections from `config/<boot>.layout.json`; code and data bytes still come
  only from the reassembled sources, and the DVP overlays and `.vutext`/`.vudata` are extracted blobs.
- The loaded sections are placed by alignment only. Splat finds 11,774 functions in `.text`; gp-relative accesses
  (2,997) exist, so some translation units use small data.
- Shiftable: 200 NOPs inserted into one function relink with every symbolic reference moved; the non-shiftable spots
  are raw numbers in data that look like addresses (see README).
- Splat's own linker script is not used (one output section); `tools/make_ld.py` writes the script.

Exit reached: `ninja` prints `OK`; the shifted test build links.

### Phase 2: symbols and existing results (done)

Result (details in `README.md`):

- **One object per function.** `tools/split_objects.py` cuts splat's `.text` into 11,775 function files; the objects are
  cached by input hash and linked in the original order. A build from nothing takes about 40 s, a changed source unit
  about 15 s. The linker script places input sections by sorted name (`.text.<address>`, `.rodata.<address>`, ...): one ld
  statement per object is quadratic and did not finish in 15 minutes for 12,000 objects.
- **Constants travel with their function** (rodata migration done by the same tool): 74 % of `.rodata`, 88 % of `.lit4`;
  the rest is shared (data references, several users) or, for `.gcc_except_table`, belongs to a whole object file.
- **Symbols.** `config/symbols.txt` holds Ghidra's 9,946 functions (268 with a recovered name, 272 with prototypes) and 175
  data labels; `tools/ghidra_export.py` rewrites it from raw Ghidra pages and reconciles with splat (9,943 common starts;
  1,832 functions only splat finds: Ghidra misses, mostly vtable/callback targets and 8-byte stubs).
- **Existing results imported as source units** (`config/units.yaml`, `src/`, `include/`): 191 of the 206 PS2-exact Kynapse
  bodies and all 65 PS2-exact game functions (7 of them using the VU0 vector layer) replace their assembly in the full
  build, which stays identical for all five retail images. `tools/progress.py` reports 256 functions and 0.7 % of `.text`
  (about 19 KB) from source.
- C++ emissions of a unit that the original placed elsewhere are not linked: unwind groups in `.data`, vtables and inline
  copies in `.gnu.linkonce.*`; the symbols they define are bound to the originals.

Exit reached: the full build is identical with every imported function in C/C++; `tools/progress.py` reports the first
non-zero percentage.

### Phase 3: translation-unit boundaries (first pass done; the map improves as functions are matched)

Evidence for file boundaries (README, "Translation units", has the numbers): unwind-frame groups in `.data` (one per object
compiled with exceptions, exactly), the `__CTOR_LIST__` and the `_GLOBAL__I/D` stubs that end a TU with global objects, string
signatures of libraries, the code-generation style (`sd` saves are Sony's precompiled libraries), data-order joins (constants and
statics only one object can own), call edges and shared items between neighbours. Alignment, orphan pieces and the cross-build
signals do not mark boundaries.

Result: `tools/tus.py` writes `config/tus.yaml`: 599 object TUs of two or more functions (120 exact from frames), 1,586 isolated
functions and 852 link-once sections, each with text and data ranges, compiler and flags, confidence and evidence; `progress.py`
reports by TU and library; `next.py tus` lists Phase 5 candidates. The automatic pipeline takes the TU's compiler and flags first
(`ee-gcc2.9-991111-01` for the `sd` libraries, 36 functions), `tools/regroup.py` merges source units into one file per TU (241 TUs
with `-ffunction-sections`, assembly left in place between their functions) and the build stays identical. `ninja progress`: 4,556 of
11,899 functions (38.3 %), 7.9 % of `.text` (from 4,490 and 7.73 %; the pipeline fixes for tail-call delay slots and byte arithmetic on untyped
globals gave 26 of the 66 new functions).

Left: the boundaries of the 2,000 proposed TUs are likelier than certain (a stretch of related functions may hold several objects);
Sony library code beyond the leaf functions needs the Sony compiler's idioms; the physics and animation libraries are leads from
the Xbox counterpart map, not verified; no signal marks the edge of a TU without exceptions or global objects except the gaps data
and calls leave open.

### Phase 4: the automatic pipeline (pilot done; the pipeline keeps running as units are claimed)

- `tools/autodecomp.py` (README, "Automatic pipeline"): m2c draft, mechanical cleaning, compile with a short list of
  flag variants in the build backend (hundreds of candidates per call), score against the original words with
  relocation targets compared, decomp-permuter for up to 8 differing instructions, family cloning for identical bodies,
  inline-asm templates for syscall and interrupt stubs, then `register` and `settle` turn exact drafts into units. Results
  stay in `build/auto.json` (ignored).
- `tools/next.py` lists near misses by differing instructions and kind, functions blocked on a missing type (grouped by
  what they need), families of identical bodies, owned-rodata blockers and EE instructions.
- Pilot result (USA retail): functions under 100 bytes 57.9 % automatic (3,516 of 6,075; 61.7 % without the 380
  one-instruction split fragments), 100-300 bytes 9.2 % (283 of 3,084; game region 9.0 %), a 400-function sample over
  300 bytes 0 %. The build stays identical; `ninja progress` went from 2.17 % to 34.4 % of the functions and from 0.79 %
  to 6.6 % of `.text`. Small functions are cheap and almost all sources are plain C over untyped pointers; what blocks the
  rest is typing (callee signatures, struct layouts, stack objects) and EE-specific code, not search time. `tools/next.py`
  prints the current failure table.
- Second pass (boundaries, types, EE moves, rodata, families; README, "Function boundaries" and "Automatic pipeline"): the
  123 functions that were fused with an orphan `<instruction>; nop` piece are separate now (48 match), the 1,169 orphan
  pieces are classified instead of counted as failures, and the rates are 70.2 % under 100 bytes, 11.6 % for 100-300 bytes
  and 0 % in a 400-function sample above 300 bytes. `ninja progress`: 4,490 of 11,898 functions (37.7 %), 7.7 % of `.text`.
  Left: VU0/MMI code (`lqc2`, `qmtc2`, `pcpyld`, `pextlw`), stack aggregates passed to callees, functions over 300 bytes.

### Phase 5: file-by-file campaigns (continuous)

- An agent claims one TU in `units.yaml`, recovers its types and classes, and matches its functions,
  using the pipeline for drafts. Then it moves the TU's data from binary to C/C++.
- **Done** means every function and the TU's data are in source and the build is identical.
- Functions that resist get a `NONMATCHING` C version behind a define plus the original assembly, so
  readable source exists for every function even before it matches.
- Order: TUs with the most automatic matches; then Kynapse (prior results); then game subsystems by
  dependency; library code last, or never if it is third-party SDK code.
- Run several agents in parallel on disjoint TUs; a coordinator owns `include/`, `units.yaml` and the
  generators.

### Phase 6: link to modding (later)

- Feed matched PS2 source into `the companion project` through the Xbox-to-PS2 counterpart map, where the Xbox
  runtime needs readable source.
- Keep the shiftable build, so PS2 mods remain possible.

### Phase 5 pilot results

Three parallel sessions on 2026-10-18 used separate worktrees, units files and build trees. Worker calls
were isolated by UUID-named containers with private scratch filesystems; no job collision occurred.
The higher-ranked `tu_353118` proved to be allocator code under a fallback game classification, so the
game session retained the requested `tu_105bc0`. Kynapse and animation have exact unwind boundaries;
the game boundary remains provisional.

| TU | Source functions, before → after | New text bytes | Full build attempts | Trial batches (candidate jobs) | Minutes including setup |
| --- | --- | ---: | ---: | ---: | ---: |
| `kynapse/tu_30ea38` | 15/22 → 16/22 | 856 | 5 | 38 (38) | 16.46 |
| `animation/tu_34b498` | 13/62 → 33/62 | 2,328 | 12 | 16 (684) | 16.63 |
| `tu_105bc0` | 54/99 → 64/99 | 752 | 7 | 32 (374) | 17.95 |

Bytes use `ninja progress` spans, including alignment. The sessions also made 61 matched functions
readable: eight Kynapse C++ functions, 31 animation C callbacks/handlers, and 22 game C++ functions and
callbacks (16 methods); 30 were existing matches rewritten. Trial counts exclude 12 compile-only
preparation passes and five standalone probes. Integration and final variant checks are outside the
session timings. Every commit and all three integrated merges rebuilt identically; all five retail
images passed. Overall: 4,556 → 4,587 source functions (38.29 → 38.55%), 214,376 → 218,312 text bytes
(7.89 → 8.04%). No whole TU, including its data, was completed; 70 functions remain in these three TUs.

Blockers, ranked by impact on remaining bytes:

1. Types and object lifetimes: callee/callback signatures, float arguments, polymorphic PS2 layouts,
   iterators and stack aggregates. Correcting these matched even an 856-byte initializer.
2. Scheduling and register allocation after typing; near-identical destructors and loops exhausted
   bounded attempts without yielding whole-TU completion.
3. Pipeline gaps: switch-table ownership, mixed EE 64/128-bit preparation, small-data flags, custom
   header packaging and assembly aliases whose function-section names differ from their symbols.

Continue with three agents on disjoint subsystems and one owner per shared header; there is no evidence
yet to justify more. Choose semantically checked, exact-boundary TUs with coherent classes and useful
counterpart sources, rather than ranking by existing match count alone. First improve callee arity and
float propagation, iterator/aggregate modeling, jump-table migration, custom-header packaging and
section-alias handling. Add automatic per-session build/candidate/time telemetry.

Observed throughput was 1,312 bytes and 10.3 new functions per session on average, or 4.63 kB per agent
hour (individual byte rates: 3.12, 8.40 and 2.51 kB/hour). Straight-line arithmetic for the remaining
2,497,152 text bytes gives about 1,900 comparable sessions / 540 agent-hours. This is optimistic, not a
completion forecast: about 76% of the remaining bytes are in functions over 300 bytes, this pilot mainly
finished smaller functions, and data completion was not measured. Measure another pilot after the type
and pipeline fixes, including a completed large-function TU, before estimating whole-project completion.

### Phase 5 campaign results

Bytes are full-image-verified `.text` spans including alignment. Code and owned-data completion are separate.

| Wave | New functions / bytes | Complete TUs (code / data) | Throughput | Functions >300 B | Main blockers |
| --- | --- | --- | --- | --- | --- |
| 0, tooling | 115 / 15,720 | 0 / 0 | about 1.8 h coordinator wall time; not a TU-agent rate | automatic 15/2,316 (0.65%); none >1,000 B | stack/tagged aggregates; code-generation mismatches; EE vector and mixed-width code |
| 1, seven area queues | 147 / 19,528 (0.719%) | 3 code; data not completed/audited | manual 3.66 kB/active agent-hour, 3.96 agent-hours | manual 18/173 (10.4%); 0/21 above 1,000 B; automatic 0/2,285 | stack/aggregate lifetimes; register allocation and scheduling; EE vector/mixed widths |
| 2, seven area queues | 53 / 9,008 (0.332%) | 0 / 0 | manual 3.33 kB/active or 2.25 kB/inclusive agent-hour; 2.68 active / 3.97 inclusive hours | manual 8/137 (5.8%); 0/36 above 1,000 B; automatic 0/2,277 | aggregate/iterator lifetimes; register allocation and scheduling; VU lanes/mixed widths |

Wave 0: 4,587 functions / 218,312 bytes became 4,702 / 234,032 (39.52% / 8.62%). Incremental
automatic rates among previously unmatched real functions were 65/1,586 (4.10%) below 100 B,
35/2,736 (1.28%) at 100–300 B, and 15/2,316 (0.65%) above 300 B. These are additional yields
after the earlier pipeline. Five unrestricted context passes used over 100,000 candidate compilations
in 507 worker batches; focused retries covered changed views/callers. Near-search solved one of ten
large candidates. All five retail images passed; no source addresses regressed.

Tooling now propagates argument and consumed-return evidence, exports PS2 access views, corrects SN
software-double/EE128 handling, recognizes switch sections/relocations and escaped instructions, and
retries scheduled stack prologues. Batch parse/worker failures stop explicitly. Complete class sizes,
tagged payloads, stack lifetimes, indirect calls and mixed EE widths remain unresolved; view verification
requires matching member users. The largest remaining automatic failure categories are stack objects
(587 kB), general mismatches (481 kB), and unsupported EE operations (401 kB).

Wave 1: 4,702 functions / 234,032 bytes became 4,849 / 253,560 (40.75% / 9.34%). Manual work
visited 24 TUs and added 79 functions / 14,512 bytes plus 1,416 owned-data bytes, using 109 Ninja
invocations; some early candidate counts are lower bounds. The ChildBuffers TU became code-complete;
automation completed two additional small TUs. Incremental automatic rates were 54/1,481 (3.65%) below
100 B, 14/2,678 (0.52%) at 100–300 B and 0/2,285 above 300 B. Three full context passes plus bounded
near search used 49,428 actual compilations in 366 worker batches; the pointer pass added nothing and
the void pass added eight object candidates. Four large near searches solved none. New tools preserve
variadics and direct return ABI evidence, recognize MIPS stack escapes and split switch extents, improve
GNU-assembler candidates and alignment/cache checks, protect prior source through settlement and retry
cleanup, and retain build telemetry. All five retail images passed; no prior source addresses were lost.

Wave 2: 4,849 functions / 253,560 bytes became 4,902 / 262,568 (41.20% / 9.67%). Manual work
visited 22 TUs and added 52 readable matches / 8,920 bytes plus 80 owned-data bytes. Every unmatched
function above 300 B in those queues received a full typed, worker-scored hypothesis; no partial probes
remain in the denominator. Worktrees recorded 61 link and 24 compile-only calls, including rebase
baselines, plus 9,999 candidate compilations in 443 deduplicated batches. Active time is approximate;
inclusive time includes integration waits. Coordinator tooling/integration and automatic runs are additional.
The unrestricted automatic pass, 460-function return-context retries and one bounded large near search
used 9,464 compilations in 123 batches. Fifteen exact objects yielded one placeable 88-byte function:
incremental rates were 1/1,405 (0.071%) below 100 B, 0/2,642 at 100–300 B, and 0/2,277 above 300 B.
All five retail images passed, with no source-address regressions.

Tooling now preserves implicit `this` in class-scoped declarations and scores resolved absolute-address
instructions strictly. PS2 leading-vptr layouts and C++ temporary lifetimes unlocked manual matches.
Return-demand propagation prevents unused 128-bit register temporaries from becoming return ABI
claims, preserving consumed/anchored returns and software doubles; 105 tool tests pass. This corrected
365 prototypes and reduced signature conflicts from 1,203 to 1,067; its focused retries added no matches.
Layout proof uses matched definitions independently of ABI signature ranking. VU helpers compile but
remain unverified hypotheses.

Stopped at the requested threshold: waves 1 and 2 both gained under 1% of text. Recommend three
focused agents for stack/iterator and ABI models, independently matched EE primitives, and TUs with
strong counterpart-source leads. Demonstrate a complete TU containing a function above 1,000 B before
another broad campaign; use context dependency changes to select retries. At this wave's manual rate,
the remaining 2.45 MB suggests about 740 active agent-hours (1,090 including observed waits), an
optimistic extrapolation. No new match above 1,000 B emerged from 57 full manual attempts across the
two waves; 893 kB remains in that band, so there is no defensible completion date yet.

Campaigns rotate seven area queues through three workers: four agent slots including the coordinator
are available; worker contention has not reduced concurrency. Integrate each TU checkpoint, then rerun
automation and all retail checks per wave. Two consecutive campaign waves below one percentage point
of text (27,155 bytes each) trigger the requested throughput stop.

## Agent rules (`AGENTS.md`)

- Build with `ninja`, check progress with `tools/progress.py`, pick work with `tools/next.py`.
- Claim a TU in `units.yaml` before editing it. Edit only that TU's sources unless you are the
  coordinator.
- Run the full build before committing. A commit must leave the build identical.
- Do not commit game bytes, generated assembly, compilers or build output.
- Keep docs short: the README for how-to, `units.yaml` for status. No per-function notes beyond a
  one-line comment on non-matching functions.

## Progress and throughput checkpoints

| Checkpoint | Signal |
| --- | --- |
| Phase 1 exit | Identical rebuild exists |
| Phase 2 exit | Imported functions build identically in place |
| Phase 4 exit | Reached: 57.9 % of the functions under 100 bytes, 9.2 % of 100-300 bytes, nothing above 300 without types |
| Every week | Matched bytes and functions, complete TUs, functions per agent session |

If the automatic rate in Phase 4 is low, investigate why before scaling up the agents: compiler flags,
missing types, or m2c gaps with EE instructions.

## Risks and open questions

- **Mixed assemblers.** C compiles through the SN assembler; asm files go through GNU `as`. Both must
  produce compatible ELF objects for `ld`. Checked in Phase 0.
- **Per-file flags.** `-G` values and other flags vary between files and must be recovered per TU; the Sony libraries need another compiler (`tools/tus.py`).
- **EE instructions.** MMI, 128-bit values and VU0 inline assembly need the study's header and agent
  work; m2c will not handle them (pilot: 307 of the 6,075 small functions and 320 of 3,084 in 100-300 bytes fail on them,
  `syscall` stubs excepted: those come from one asm template).
- **Function boundaries.** Repaired (`tools/boundaries.py`): the stray `<instruction>; nop` pieces are orphans between
  functions, not code of either neighbour; splat's other extents hold where Ghidra's differ.
- **VU microcode** (`.vutext`, DVP overlays) stays as binary data.
- **Third-party libraries** (Sony runtime, RenderWare, C++ runtime) may never be matched from source
  without their original libraries; count them separately.
- **No symbols** in any variant. Names come from Ghidra, RTTI strings, beta profiler names and Xbox knowledge.
- **Full-file identity** may need extra handling for ELF headers, `.reginfo` and `.mdebug` remnants.

## Variant findings

Phase 0 triaged nine disc images (`docs/inputs.md`). No EE executable carries symbols, debug sections or
compiler banners. The EU "beta" executable is identical to EU retail. The USA beta (2005-08-16) is an
earlier build with about ten `Class::Method` profiler names and RenderWare Studio development modules on
the IOP side; it is a source of naming hints, not a byte target.
