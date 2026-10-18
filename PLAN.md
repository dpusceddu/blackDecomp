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
(`ee-gcc2.9-991111-01` for the `sd` libraries, +37 functions), `tools/regroup.py` merges source units into one file per TU (241 TUs
with `-ffunction-sections`, assembly left in place between their functions) and the build stays identical.

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
