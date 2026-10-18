# Black (PS2) matching decompilation

Goal: a source tree that rebuilds the retail PS2 executable byte for byte, organised into the original
translation units. See `PLAN.md` for the phases and `docs/inputs.md` for the Phase 0 findings.

Game bytes, disc contents, compilers and build output are never committed; they live in ignored
directories (`orig/`, `asm/`, `data/`, `build/`, `.local/`).

## Setup

```sh
python3 -m venv .venv && .venv/bin/pip install -r requirements.txt   # rabbitizer, splat64, spimdisasm
```

Machine-specific configuration goes in `.local/config.json`, which is ignored. SDK compilers and assemblers run only
through the build backend, never directly on the host.

## Build (the identical rebuild)

Needs the target executable in `orig/<variant>/files/` (see `tools/discs.py`), the build backend, and `ninja`.

```sh
python3 configure.py --variant usa-retail     # writes build.ninja (variants: usa-retail, eu-au-retail, eu-retail, kr-retail, jp-retail)
ninja                                          # ends with `OK  SLUS_213.76 ...` or a mismatch report
ninja progress                                 # share of .text provided by source (see below)
```

Stages (one `ninja` rule each; everything generated is under the ignored `asm/`, `data/`, `build/`):

1. extract: `tools/splat_config.py` writes `config/<boot>.yaml` (splat segments from the ELF section table) and the
   headerless image splat reads; `tools/elf_layout.py` writes `config/<boot>.layout.json` (ELF header, program
   header and one record per section) and extracts the opaque non-loaded payloads (DVP overlays) to `data/`.
2. split: `splat split` (spimdisasm, rabbitizer) writes `asm/<variant>/text.s` (all functions, one file) and one data
   file per section; `.vutext` and `.vudata` stay binary blobs.
3. `tools/link_support.py` defines the symbols splat cannot (labels inside code, offsets into data objects, section
   ends and plain constants).
4. `tools/split_objects.py` cuts `.text` into **one assembly file per function** (`build/<variant>/s/text/func_XXXXXXXX.s`,
   with the function's own `.extern` block) and migrates the constants that only one function uses into that
   function's file (see "Constants" below). `.rodata`, `.lit4` and `.gcc_except_table` keep their remaining shared objects
   as runs; the other data sections stay one object each. It also writes `placement.json` (every object and the original
   order of every section) and `labels.json`.
5. `tools/make_ld.py` writes the linker script. Every function and constant run is an input section named
   `<section>.<its original address>`, and the script places them with `*(SORT_BY_NAME(<section>.*))`, which restores the
   original order (one ld statement per object would take hours for 12,000 objects). Source units from
   `config/units.yaml` replace functions here (see "Replacing a function with source").
6. `tools/build_objects.py` runs, in one call to the build backend, the EE assembler 2.10 on the objects that changed
   and the SN compiler on changed source units, then mainline GNU `ld` on everything. Objects are cached by the hash of
   their inputs in `build/<variant>/cache/`, so an incremental build re-assembles or recompiles only what changed.
7. `tools/pack_elf.py` re-packs ld's loaded sections into the retail container (see below);
   `tools/check_elf.py` compares the result with `config/checksums.sha256`.

Times (USA retail, a 2-core build backend): a build from nothing (extract, splat, split, assemble 12,000 objects,
link, pack) takes about 42 s; with the objects cached and one source unit changed about 13 s, of which the link and the
transfer of the cached objects to the build backend are most (about 11 s); with nothing changed `ninja` does nothing.

ld cannot write the retail container: section-header order, the non-loaded `.reginfo`, `.DVP.*` and `.debug_str`
sections, and `e_flags` 0x20924001. `pack_elf.py` therefore takes the linked section contents and addresses from ld and
writes the headers from `config/<boot>.layout.json`, regenerating `.shstrtab` and `.reginfo` (with the linked `_gp`)
and rebasing the `.DVP.ovlytab` addresses that point into `.vutext`. The overlays and `.vutext`/`.vudata` are extracted
payloads, not rebuilt. Code and data come only from the reassembled sources and the source units.

### Constants (rodata migration)

`split_objects.py` does for `.rodata`, `.lit4` and `.gcc_except_table` what splat's rodata migration does, with checks
splat does not make for this assembler. A splat data object (`dlabel` .. `enddlabel`) belongs to a function when exactly
one function refers to it and no data does; it is then written into that function's file (`.lit4` into a sibling
`func_XXXXXXXX.lit4.s`, because the assembler mishandles a small-data symbol defined next to the code that addresses it
off `$gp`). Constraints it enforces, found by building: an input section is placed whole, so a function keeps one
contiguous run per section; the assembler aligns `.short`/`.word`/`.float`/`.double` by itself, so a run is cut where such
a directive would need an earlier start than the original address allows. Result for USA retail: `.rodata` 79,417 of
107,816 bytes (74 %, 1,022 functions), `.lit4` 228 of 260 bytes (28 functions). What stays shared: 13,968 bytes referenced
from data (string tables, vtable-like arrays), 9,763 referenced by several functions, 2,148 unreferenced, 2,520 whose
function had a second, non-adjacent run. `.gcc_except_table` migrates only 456 of 3,972 bytes: the other tables
belong to a whole object file (their handler labels span several functions), which is translation-unit evidence for
Phase 3 rather than something one function can carry.

### Function boundaries

Splat finds the function starts; `tools/boundaries.py` adds the ones it cannot see (`config/boundaries.<variant>.txt`, splat's
`symbol_addrs` format, regenerated by `python3 tools/boundaries.py VARIANT` and read by the `split` stage). Evidence from the
instructions of the image (all five retail images behave alike):

- **Orphan pieces.** 8-byte pieces `<one non-branch instruction>; nop` (mostly `addiu $sp, $sp, N; nop`) sit between functions,
  1,169 of them in USA retail. Nothing calls or jumps to them or builds their address, their `N` does not follow the
  neighbouring frames, functions that match from C do not emit them, and a reference to the function behind a run points
  behind it (`%lo(func_00103928 + 0x8)`). Splat fused 123 runs with the function that follows, which kept those functions from
  matching; the tool starts a function behind every run (not across a branch, not where Ghidra starts a function inside the
  run). On USA retail Ghidra independently starts a function exactly behind the run in 531 of the 535 runs it has an opinion on.
  The runs stay assembly (`orphan` in `build/auto.json`).
- **Extent disagreements with Ghidra** (312): Ghidra leaves out the last instruction (the `jr` delay slot) in 158, and ends at
  an indirect `jr` that is a computed jump inside the function in 180 more; splat's extent holds (internal branches or jump
  tables reach the rest, no frame is allocated behind Ghidra's end). Nothing to repair.
- **Fall-through over-splits** (47 reported by the Ghidra comparison): the "extra" words are the function's own jump table
  (migrated `.rodata` counted as code) or follow an orphan piece. No real over-split remains.

## Replacing a function with source

A *unit* is a source file that replaces a run of adjacent functions of the image. List it in `config/units.yaml`
(the file is maintained by `tools/settle_units.py`; the format is described in `tools/units.py`):

```yaml
variant: usa-retail
units:
- name: kynapse_leaf_2d15a0
  source: src/kynapse/leaf_functions_2d15a0.cpp
  origin: kynapse                    # kynapse | game | vector, for the progress report
  flags: [-O2, -G0, -snas, -fbyte-bool]
  externs: {gIdA: 0x44ecd0}          # name the code refers to but does not define -> original address
  functions:
  - {addr: 0x2d15a0, symbol: Kaim_AllIdsValid__Fv, size: 108, status: source}   # asm + reason: to keep the assembly
```

`symbol` is the exact mangled name the compiler emits; `make_ld.py` makes the image's `func_XXXXXXXX` name an alias of it,
so assembly callers link against the source. The unit's `.text` and its constants take the place of the functions'
objects; its other sections (unwind data in `.data`, vtables and inline copies in `.gnu.linkonce.*`) are not linked, and
global symbols they defined are bound to the originals through `externs`. Then:

```sh
python3 tools/settle_units.py      # compile every unit, demote what cannot be placed identically, relink until OK
ninja && ninja progress
```

`settle_units.py` uses `tools/units_verify.py`: `prepare` checks each object (symbol, size, extra code, constants it brings
that the original did not migrate, unbound externs), `link` demotes units the linker names, `compare` demotes the units
that own any differing word of the linked image. Reasons recorded in `config/units.yaml`: `extra` (the unit emits other
functions too), `name`, `size`, `section`, `shared`, `layout`, `extern`, `labels`, `link`, `bytes`, `compile`. Provenance
of the first sources: `tools/import_kynapse.py` and `tools/import_game.py` port the PS2-exact bodies of the companion project
(headers in `include/kynapse/`, `include/game/`, sources in `src/kynapse/`, `src/game/`). Diagnostic helpers:
`tools/objdump.py` (sections, symbols, relocations of an object), `BLACK_UNITS_ALL=1` (pretend every unit function is
source, to compile demoted units).

## Automatic pipeline (tools/autodecomp.py)

Drafts C for assembly functions with no per-function judgment and keeps what rebuilds byte-identically. Setup, once:

```sh
.venv/bin/pip install -r requirements.txt            # m2c (pinned git commit), pycparser, toml
.venv/bin/python tools/autodecomp.py setup           # decomp-permuter at its pinned commit, into .venv/ (git clone)
```

m2c and the scoring run on the host (they only read and write text); every compile runs in the build backend, hundreds
of candidates per call (about 0.8 s latency per call, about 90 compiles per second). m2c's little-endian MIPS GCC target
is `-t mipsee-gcc-c` (with `--valid-syntax`, which turns unknown field accesses into `M2C_FIELD` macros, see
`include/auto/prelude.h`).

```sh
python3 tools/autodecomp.py run --max-size 100            # all assembly functions under 100 bytes -> build/auto.json
python3 tools/autodecomp.py run --min-size 100 --max-size 300 --region game
python3 tools/autodecomp.py run --max-size 100 --status near --status mismatch --ctx ctx2.c --tag arity-int
python3 tools/autodecomp.py permute --max-score 8         # decomp-permuter on near misses (one member per family)
python3 tools/autodecomp.py family                        # clone exact sources onto identical-body functions
python3 tools/autodecomp.py register                      # exact drafts -> src/auto/<region>/*.c + config/units.yaml
python3 tools/autodecomp.py settle                        # compile, link, demote what cannot be placed, retry alone; ninja must say OK
python3 tools/autodecomp.py report [--max-size N]         # outcome classes, failure reasons
python3 tools/next.py [near|types|families|data|ee]       # best next work
```

Per function: (1) m2c on its `.s` (plus the sibling `.lit4.s`), with a C context made of the typedefs and the Ghidra
prototypes of `config/symbols.txt` (`ctx.c`), or the same plus an int (`ctx2.c`) or pointer (`ctx3.c`) prototype with the
argument count inferred for every other function (registers read before written in the callee, and the argument
registers set before each call, majority over call sites); (2) mechanical cleaning: missing leading parameters, K&R
declarations for callees, function-pointer globals, strings the function owns turned back into literals; (3) compile as
C named `func_XXXXXXXX` with `-O2 -G0 -snas`, plus `-G8` when the original addresses small data through `$gp`; on a miss
the flag set is varied (`-O1`, `-O3`, `-fbyte-bool`, `-G8`, `-fno-peephole`, `-fno-schedule-insns2`); (4) score: the
compiled `.text` is compared with the original words, relocated fields masked, and each relocation target (symbol address
plus addend; constants by their bytes) must equal the symbolic operand of the original assembly; (5) up to 8 differing
instructions: decomp-permuter's randomizer, a hill climb on the compile score, 50 candidates per function and round
compiled together in one worker call; (6) identical bodies (`family`): an exact source is cloned onto the members of its
family by renaming symbols; (7) functions m2c cannot read but that are a few special instructions (`li $v1, N; syscall`,
`ei`, `di`, `sync`) come from one inline-asm template.

Type and instruction support, all of it mechanical and checked by exact matches:

- **Types.** `python3 tools/ghidra_types.py` writes `include/types_ghidra.h` from the raw Ghidra pages in `.local/ghidra/`
  (`structures_N.json`, one `get-structure-info` response per structure listed by `list-structures`, and the signatures in
  `config/symbols.txt`): 25 structures (the PS2 collision, game-object, Kynapse and AI/route types the Ghidra program holds)
  and 267 signatures under the image's `func_XXXXXXXX` names, with compile-time offset and size asserts. They are recovered
  guesses; each structure is marked `UNVERIFIED` until a unit that includes the header and names it is in `config/units.yaml`.
  `ctx.c` for m2c is made of the typedefs, this header and `long long` prototypes (below); every draft includes the header.
  `tools/m2c_wrap.py` is m2c with one change: a dereference of an untyped expression becomes `M2C_FIELD(expr, T *, 0)` (valid
  C) instead of `*expr`.
- **Stack objects.** m2c's frame objects (`sp`, `&spN`, `spN`) become one `u8 sp[N] __attribute__((aligned(16)))` buffer whose
  size is searched against the frame size; reads of an argument register the function never sets become `argN`.
- **EE instructions** (`tools/ee_prep.py`). SN GCC 2.95 for the EE has `long` = 64 bits and `long long` = 128 bits. `lq`/`sq`/
  `por rd, rs, $0` are `long long` loads, stores and moves; `ldl`+`ldr` / `sdl`+`sdr` pairs are 8-byte accesses at byte
  alignment (`struct { char c[8]; }` copies, packed members). The assembly shown to m2c has `ld`/`sd`/`daddu` instead, and
  its 64-bit types are turned into the 128-bit type (or `M2C_UNALIGNED64`) afterwards, but only when the function has no real
  64-bit access. Callee results and arguments of 128-bit type are found from the callee's code (`wide_info`) and enter the
  context as `s64`. `max.s`/`min.s` and MMI/VU0 instructions m2c cannot read are reported by instruction (`next.py ee`).
  The vector layer (`include/game/ai_vector.hpp`, compile with `-mvu0-use-vf0-vf31`) is the form SN accepts for them.
- **Owned rodata** (`autodecomp.py rodata`). An exact draft that owns `.rodata` gets the run defined in its unit, as
  `const u32 rodata_XXXXXXXX[] __asm__("D_XXXXXXXX")` words or a `const char` string array laid out as the original run, and
  string literals point at the array. Then `register`/`settle` place it.
- **Families** (`family`). Exact sources are cloned onto the members of a family of identical bodies by renaming symbols (also
  for functions that own rodata); a template for a family is adopted with `autodecomp.py adopt ADDR file.c` and tried with
  `tools/trysrc.py ADDR file.c`.

An exact draft is only a candidate: `register` writes it as a unit (adjacent exact drafts are grouped, at most 24) and
`settle` uses `tools/settle_units.py` to demote whatever does not link identically; a demoted group is retried one function
per unit. Results and reasons (`verify-failed`: `size` = the function owns rodata that the source does not define, `extra`,
`layout`, `bytes`) are kept in `build/auto.json` (ignored). The drafts keep m2c's variable names (`temp_5`, `var_3`) and
`M2C_FIELD` accesses; they compile as C under the image's `func_XXXXXXXX` names, so assembly callers link unchanged, and
carry `origin: auto` in `config/units.yaml`. Later phases turn them into C++ methods once classes are known.

## Symbols and progress

`python3 tools/ghidra_export.py` writes `config/symbols.txt` from raw Ghidra pages in `.local/ghidra/` (the three Ghidra MCP
calls it lists) and reconciles Ghidra's function list with splat's (`build/<variant>/ghidra_reconcile.json`). Names are
readable aliases, not original symbols; unknown functions stay `func_XXXXXXXX`.
`ninja progress` (or `python3 tools/progress.py`) prints the share of `.text` bytes and functions provided by source,
overall and by region, and writes `build/<variant>/progress.json`.

Other tools: `tools/diffelf.py REF BUILT` (section-by-section diff), `tools/shift_test.py` (shiftability test),
`tests/link/check.py` (SN object + GNU object linked by the build backend's ld).
In a sandbox script, `mipsel-linux-gnu-{ld,objcopy,readelf,objdump,nm}` are on PATH.

### Shiftability

`python3 tools/shift_test.py usa-retail --nops 200` copies the split assembly to a scratch name, inserts NOPs into one
function, rebuilds and checks every symbolic reference against a symbol-derived address map. Result for 200 NOPs
(everything from `.text` onward moves): all 19,781 `jal`/`j`, 19,121 `%hi`, 25,118 `%lo`, 2,997 gp-relative accesses,
8,499 + 4,321 + 5 data pointers and 903 exception-table entries moved correctly, 0 inconsistencies. Known non-shiftable
spots: 984 raw `.word` values in `.data`, `.rodata` and `.sdata` that fall inside the image address range but are not
symbols in the split (almost all are numbers such as colours, hashes and flags; at least 33 words around `.data` 0x3C3DC0
point into the `.vutext` blob and would need symbols), and any address built by arithmetic that is not a `%hi/%lo` pair.
One NOP only moves the code behind it by 8 bytes (function alignment) and the alignment slack before `.vutext` hides it
from the data sections.

## Layout

```
PLAN.md       phases and rules          config/variants.json   hashes and ELF metadata of all variants
AGENTS.md     agent rules               config/<boot>.yaml     splat configuration, one per boot executable
configure.py  writes build.ninja        config/<boot>.layout.json   ELF container description for tools/pack_elf.py
include/      macro.inc, kynapse/, game/ headers of the source units    docs/inputs.md   Phase 0 findings
src/          source units (kynapse/, game/)    config/units.yaml, symbols.txt, regions.txt
tools/        build, unit and Phase 0 tools     tests/           toolchain and linker probes
orig/ asm/ data/ build/ .local/         ignored: inputs, generated assembly and data, build output, scratch
```

## Phase 0 tools

Put the disc zips in a directory (default `../ps2images`), then:

```sh
.venv/bin/python tools/discs.py            # one image at a time: keep executables, SYSTEM.CNF, listings in orig/<slug>/
.venv/bin/python tools/inputs.py           # triage and retail comparison -> config/variants.json, .local/inputs/
.venv/bin/python tools/symbols.py          # symbol/debug dump and transfer estimate -> .local/inputs/symbols/
.venv/bin/python tools/compile.py ee-gcc2.95.3-136 -O2 -G0 -snas -c tests/toolchain/trivial.c -o build/probe/t.o
.venv/bin/python tools/asmcheck.py gen && .venv/bin/python tools/asmcheck.py run   # EE assembler round trip in the sandbox
.venv/bin/python tools/sandbox.py SCRIPT.py   # run a Python script inside the build backend
```

`discs.py` refuses to extract when fewer than 12 GB of disk would remain and deletes each image after use.
