# Build stages

How the identical rebuild works. Everything generated stays under the ignored `asm/`, `data/` and `build/`.

## Stages

Needs the target executable in `orig/<GAME_ID>/<GAME_ID>` (see [orig/README.md](../orig/README.md)), the toolchain
(`python3 tools/toolchain.py install`; see "Toolchain" below) and `ninja`.

```sh
python3 configure.py --version SLUS_213.76     # writes build.ninja (SLUS_213.76 is the default; also SLES_538.86, SLES_540.30, SLKA_253.72, SLPM_663.54)
ninja                                          # ends with `OK  SLUS_213.76 ...` or a mismatch report
ninja progress                                 # share of .text provided by source (see below)
ninja objdiff && ninja report                  # objdiff project and progress report (docs/progress-reports.md)
```

## Toolchain

`python3 tools/toolchain.py install` downloads, verifies by SHA-256 and unpacks into the ignored `build/toolchain/`
(or `$BLACK_TOOLCHAIN_DIR`):

- the decomp.me compiler archives the build uses (`config/toolchain-compilers.json`): `ee-gcc2.95.3-136` (SN 1.36, a Windows
  program) for most of the game, `ee-gcc2.9-991111-01` (32-bit Linux) for the Sony libraries, `ee-gcc2.96` (its GNU
  assembler assembles all split assembly; one scoped unit uses its compiler) and `ee-gcc2.95.2-273a` (an alternative
  assembler for three units);
- the patched short-loop assembler `ps2eeas-1.9.25.758-min6`, reproduced from the downloaded original `Ps2EeAs.exe` with
  `tools/patch_ps2eeas.py` and checked against the pinned hashes in `config/toolchain-assemblers.json`;
- [wibo](https://github.com/decompals/wibo) 1.2.0 (`config/toolchain-local.json`), which runs the Windows programs on Linux.

The linker and `objcopy` come from `binutils-mipsel-linux-gnu` (Debian package, 2.40 tested) or from the decompals prebuilt
release (`install --binutils prebuilt`); the build looks for `mipsel-linux-gnu-ld`, then `mips-ps2-decompals-ld`.
`python3 tools/toolchain.py check` reports what is missing. The Sony tools are 32-bit Linux programs, hence `libc6-i386`
on Debian. The `Dockerfile` builds an image with all of this.

Two quirks the tools handle: SN's `Ps2EeAs.exe` crashes when it has to print a warning and its own path is longer than about
80 characters (Windows form), so the Windows tools run from a short copy under `/tmp` (`tools/assembler.py`, `short_path`);
and compiler warnings are printed only for failed jobs (set `BLACK_VERBOSE=1` for all).

The jobs run through `tools/sandbox.py` on the local backend. An optional backend plugin (`tools/backend.py`, selected in the
ignored `.local/config.json`) runs the same jobs in a disposable offline container elsewhere.

Stages (one `ninja` rule each; everything generated is under the ignored `asm/`, `data/`, `build/`):

1. extract: `tools/splat_config.py` writes `config/<GAME_ID>/splat.yaml` (splat segments from the ELF section table) and the
   headerless image splat reads; `tools/elf_layout.py` writes `config/<GAME_ID>/layout.json` (ELF header, program
   header and one record per section) and extracts the opaque non-loaded payloads (DVP overlays) to `data/`.
2. split: `splat split` (spimdisasm, rabbitizer) writes `asm/<GAME_ID>/text.s` (all functions, one file) and one data
   file per section; `.vutext` and `.vudata` stay binary blobs.
3. `tools/link_support.py` defines the symbols splat cannot (labels inside code, offsets into data objects, section
   ends and plain constants).
4. `tools/split_objects.py` cuts `.text` into **one assembly file per function** (`build/<GAME_ID>/s/text/func_XXXXXXXX.s`,
   with the function's own `.extern` block) and migrates the constants that only one function uses into that
   function's file (see "Constants" below). `.rodata`, `.lit4` and `.gcc_except_table` keep their remaining shared objects
   as runs; the other data sections stay one object each. It also writes `placement.json` (every object and the original
   order of every section) and `labels.json`.
5. `tools/make_ld.py` writes the linker script. Every function and constant run is an input section named
   `<section>.<its original address>`, and the script places them with `*(SORT_BY_NAME(<section>.*))`, which restores the
   original order (one ld statement per object would take hours for 12,000 objects). Source units from
   `config/units.yaml` replace functions here (see "Replacing a function with source").
6. `tools/build_objects.py` runs, in one backend job, the EE assembler 2.10 on the objects that changed
   and the SN compiler on changed source units, then mainline GNU `ld` on everything. Objects are cached by the hash of
   their inputs in `build/<GAME_ID>/cache/`, so an incremental build re-assembles or recompiles only what changed.
7. `tools/pack_elf.py` re-packs ld's loaded sections into the retail container (see below);
   `tools/check_elf.py` compares the result with `config/checksums.sha256`.

Times (USA retail, two cores): a build from nothing (extract, splat, split, assemble 12,000 objects, link, pack) takes
about 1.5 to 2 minutes with the local toolchain; with the objects cached and one source unit changed about 15 s; with
nothing changed `ninja` does nothing.

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
the translation-unit map rather than something one function can carry.

## Function boundaries

Splat finds the function starts; `tools/boundaries.py` adds the ones it cannot see (`config/<GAME_ID>/boundaries.txt`, splat's
`symbol_addrs` format, regenerated by `python3 tools/boundaries.py GAME_ID` and read by the `split` stage). Evidence from the
instructions of the image (all five retail versions behave alike):

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

`python3 tools/ghidra_export.py` writes `config/symbols.txt` from raw Ghidra pages in `.local/ghidra/` (the three Ghidra exports
it lists; optional, the committed file is enough to build) and reconciles Ghidra's function list with splat's (`build/<GAME_ID>/ghidra_reconcile.json`). Names are
readable aliases, not original symbols; unknown functions stay `func_XXXXXXXX`.
`ninja progress` (or `python3 tools/progress.py [--tus N]`) prints the share of `.text` bytes and functions provided by source,
overall and by region, then by translation unit (complete, partial and untouched TUs by confidence and by library), and writes
`build/<GAME_ID>/progress.json`. `python3 tools/next.py tus` lists candidate TUs.

Other tools: `tools/tus.py` (TU boundaries and map), `tools/regroup.py` (one source file per TU), `tools/diffelf.py REF BUILT` (section-by-section diff), `tools/studies/shift_test.py` (shiftability test),
`tests/link/check.py` (SN object + GNU object linked by the toolchain's `ld`). In a sandbox script, the binutils tools
(`mipsel-linux-gnu-{ld,objcopy,readelf,objdump,nm}` or the decompals equivalents, see `$BLACK_BINUTILS_PREFIX`) are on PATH.

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
