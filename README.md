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
link, pack) takes about 40 s; with the objects cached and one source unit changed about 15 s, of which the link and the
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
