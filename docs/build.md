# Build stages

How the identical rebuild works. Everything generated stays under the ignored `asm/`, `data/` and `build/`.

## Stages

Needs the target executable in `orig/<variant>/files/` (see `tools/discs.py`), the build backend, and `ninja`.

```sh
python3 configure.py --variant SLUS_213.76     # writes build.ninja (variants: SLUS_213.76, SLES_540.30, SLES_538.86, SLKA_253.72, SLPM_663.54)
ninja                                          # ends with `OK  SLUS_213.76 ...` or a mismatch report
ninja progress                                 # share of .text provided by source (see below)
```

Stages (one `ninja` rule each; everything generated is under the ignored `asm/`, `data/`, `build/`):

1. extract: `tools/splat_config.py` writes `config/<GAME_ID>/splat.yaml` (splat segments from the ELF section table) and the
   headerless image splat reads; `tools/elf_layout.py` writes `config/<GAME_ID>/layout.json` (ELF header, program
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
writes the headers from `config/<GAME_ID>/layout.json`, regenerating `.shstrtab` and `.reginfo` (with the linked `_gp`)
and rebasing the `.DVP.ovlytab` addresses that point into `.vutext`. The overlays and `.vutext`/`.vudata` are extracted
payloads, not rebuilt. Code and data come only from the reassembled sources and the source units.

## Constants (rodata migration)

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

## Function boundaries

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
- **Constructor list.** `__CTOR_LIST__` in `.data` (count word, that many pointers, zero) names every `_GLOBAL__I_*` stub. One of the
  116 entries in USA retail, 0x339c28, sat behind five orphan pieces that splat fused with it: `boundaries.py` adds the entries of the
  list as function starts (the stub then matches like the others).
- **Extent disagreements with Ghidra** (312): Ghidra leaves out the last instruction (the `jr` delay slot) in 158, and ends at
  an indirect `jr` that is a computed jump inside the function in 180 more; splat's extent holds (internal branches or jump
  tables reach the rest, no frame is allocated behind Ghidra's end). Nothing to repair.
- **Fall-through over-splits** (47 reported by the Ghidra comparison): the "extra" words are the function's own jump table
  (migrated `.rodata` counted as code) or follow an orphan piece. No real over-split remains.

## Symbols and progress

`python3 tools/ghidra_export.py` writes `config/symbols.txt` from raw Ghidra pages in `.local/ghidra/` (the three Ghidra MCP
calls it lists) and reconciles Ghidra's function list with splat's (`build/<variant>/ghidra_reconcile.json`). Names are
readable aliases, not original symbols; unknown functions stay `func_XXXXXXXX`.
`ninja progress` (or `python3 tools/progress.py [--tus N]`) prints the share of `.text` bytes and functions provided by source,
overall and by region, then by translation unit (complete, partial and untouched TUs by confidence and by library), and writes
`build/<variant>/progress.json`. `python3 tools/next.py tus` lists candidate TUs for a Phase 5 agent.

Other tools: `tools/tus.py` (TU boundaries and map), `tools/regroup.py` (one source file per TU), `tools/diffelf.py REF BUILT` (section-by-section diff), `tools/studies/shift_test.py` (shiftability test),
`tests/link/check.py` (SN object + GNU object linked by the build backend's ld).
In a sandbox script, `mipsel-linux-gnu-{ld,objcopy,readelf,objdump,nm}` are on PATH.

## Shiftability

`python3 tools/studies/shift_test.py SLUS_213.76 --nops 200` copies the split assembly to a scratch name, inserts NOPs into one
function, rebuilds and checks every symbolic reference against a symbol-derived address map. Result for 200 NOPs
(everything from `.text` onward moves): all 19,781 `jal`/`j`, 19,121 `%hi`, 25,118 `%lo`, 2,997 gp-relative accesses,
8,499 + 4,321 + 5 data pointers and 903 exception-table entries moved correctly, 0 inconsistencies. Known non-shiftable
spots: 984 raw `.word` values in `.data`, `.rodata` and `.sdata` that fall inside the image address range but are not
symbols in the split (almost all are numbers such as colours, hashes and flags; at least 33 words around `.data` 0x3C3DC0
point into the `.vutext` blob and would need symbols), and any address built by arithmetic that is not a `%hi/%lo` pair.
One NOP only moves the code behind it by 8 bytes (function alignment) and the alignment slack before `.vutext` hides it
from the data sections.
