# Build stages

How the identical rebuild works. Everything generated stays under the ignored `asm/`, `data/` and `build/`.

## Stages

Needs the target executable in `orig/<GAME_ID>/<GAME_ID>` (see [orig/README.md](../orig/README.md)), the toolchain
(`python3 tools/toolchain.py install`; see "Toolchain" below) and `ninja`.

```sh
python3 configure.py --version SLUS_213.76     # writes build.ninja (SLUS_213.76 is the default; also SLES_538.86, SLES_540.30, SLKA_253.72, SLPM_663.54)
ninja                                          # ends with `OK  SLUS_213.76 ...` or a mismatch report
ninja progress                                 # share of .text provided by source (see below)
python3 configure.py --non-matching && ninja   # NON_MATCHING drafts into build/SLUS_213.76-nm (not a match; see below)
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
  `tools/build/patch_ps2eeas.py` and checked against the pinned hashes in `config/toolchain-assemblers.json`;
- [wibo](https://github.com/decompals/wibo) 1.2.0 (`config/toolchain-local.json`), which runs the Windows programs on Linux.

The linker and `objcopy` come from `binutils-mipsel-linux-gnu` (Debian/Ubuntu package, 2.40 tested); the build looks for
`mipsel-linux-gnu-ld` on `PATH` (or the prefix in `$BLACK_BINUTILS_PREFIX`). The decompals `binutils-mips-ps2-decompals` release
was tried and does not work: its `ld` only supports the big-endian MIPS emulation, while the executable links little-endian
(`-m elf32ltsmip`).
`python3 tools/toolchain.py check` reports what is missing. The Sony tools are 32-bit Linux programs, hence `libc6-i386`
on Debian. The `Dockerfile` builds an image with all of this.

Two quirks the tools handle: SN's `Ps2EeAs.exe` crashes when it has to print a warning and its own path is longer than about
80 characters (Windows form), so the Windows tools run from a short copy under `/tmp` (`tools/build/assembler.py`, `short_path`);
and compiler warnings are printed only for failed jobs (set `BLACK_VERBOSE=1` for all).

Every tool that needs a compiler, assembler or linker sends its work through `tools/build/backend.py` (batches of jobs via
`tools/build/sandbox.py`), so there is one place that decides where the toolchain runs; the default is the local one above.

### Running the toolchain elsewhere (optional)

The toolchain only runs on Linux x86-64. A contributor who prefers to run it elsewhere can name a Python file in the ignored
`.local/config.json`:

```json
{"backend_plugin": "path/to/plugin.py"}
```

(relative to the repository root, or absolute). The file must define `run_script(request, config)`: it receives one batch of
jobs (`files`, a `script` to run, the `out` names to return and a `timeout`) and returns `{rc, out, err, artifacts}`, the
same contract as the local backend; `backend.WRAPPER` is the program that runs such a batch and can be reused. It may also
define `compile_standalone(request, config)` (single compiles for `tools/compile.py`) and `service(...)` (long-running
detached jobs for `tools/pipeline/permuter_service.py`). The full interface is in the docstring of `tools/build/backend.py`. One call
carries a whole batch (a full build is a few calls), so a plugin may be slow per call. `BLACK_BACKEND=local` ignores the
plugin for one command. A plugin reports its own failures by raising `SystemExit('Build backend failed; ...')`; the tools
stop on that message instead of treating it as a compile error.

Stages (one `ninja` rule each; everything generated is under the ignored `asm/`, `data/`, `build/`):

1. extract: `tools/build/splat_config.py` writes `build/<GAME_ID>/splat.yaml` (splat segments from the ELF section table) and the
   headerless image splat reads; `tools/build/elf_layout.py` writes `build/<GAME_ID>/layout.json` (ELF header, program
   header and one record per section) and extracts the opaque non-loaded payloads (DVP overlays) to `data/`.
2. split: `splat split` (spimdisasm, rabbitizer) writes `asm/<GAME_ID>/text.s` (all functions, one file) and one data
   file per section; `.vutext` and `.vudata` stay binary blobs.
3. `tools/build/link_support.py` defines the symbols splat cannot (labels inside code, offsets into data objects, section
   ends and plain constants).
4. `tools/build/split_objects.py --functions` writes `functions.json` (the function starts); `tools/build/units.py` derives the units
   from `splits.yaml`, the INCLUDE_ASM markers of the source files and `symbols.txt` ([units.md](units.md)).
5. `tools/build/split_objects.py` cuts `.text` into **one assembly file per function** (`asm/<GAME_ID>/nonmatchings/func_XXXXXXXX.s`,
   with the function's own `.extern` block) and migrates the constants that only one function uses into that
   function's file (see "Constants" below). `.rodata`, `.lit4` and `.gcc_except_table` keep their remaining shared objects
   as runs; the other data sections stay one object each. It also writes `placement.json` (every object and the original
   order of every section) and `labels.json`.
6. compile: `tools/build/build_objects.py --compile-only` compiles the source files (SN compiler, one backend job; compile errors
   are printed with the file name); then `tools/build/units_verify.py prepare` checks that each compiled function can take the
   original's place and records the extern bindings (`unit_facts.json`).
7. `tools/build/make_ld.py` writes the linker script. Every function and constant run is an input section named
   `<section>.<its original address>`, and the script places them with `*(SORT_BY_NAME(<section>.*))`, which restores the
   original order (one ld statement per object would take hours for 12,000 objects). A function that a TU file compiles
   replaces its assembly object by taking over the slot (its `.text.<symbol>` section is renamed to the slot's key).
8. `tools/build/build_objects.py` assembles what changed, takes the cached compiled objects and links everything with mainline
   GNU `ld`. Objects are cached by the hash of their inputs in `build/<GAME_ID>/cache/`, so an incremental build
   re-assembles or recompiles only what changed.
9. `tools/build/pack_elf.py` re-packs ld's loaded sections into the retail container (see below);
   `tools/check_elf.py` compares the result with `config/<GAME_ID>/checksums.sha256` and, on a mismatch, names the
   functions and source files that differ (`tools/build/units_verify.py compare`).

## Link-once copies

GCC emits inline functions, template instantiations, vtables and type information that several object files need as
*link-once* sections (`.gnu.linkonce.*`): every object that uses one carries its own copy, and the linker keeps the first
and drops the others. In the retail image the kept copies of the code form a block behind the regular code (USA:
0x383b50 to 0x396f48), in link order, so a copy sits next to the others of the object file that came first
and uses it. That is why a destructor of a Kynapse class or an Apt `Value::Dispose` is not next to the rest of its class.

The sources keep the same split. A copy is a function of the library that uses it, not a library of its own:
`src/<library>/inline/linkonce_<address>.c|cpp` (and descriptive names for recovered ones) hold the copies of that library, and
progress counts them there. `ninja` computes the owner of every range into the ignored `build/SLUS_213.76/inline_owners.txt` with the strength of the
evidence (`tools/build/linkonce_owners.py`, from the callers, vtable slots and neighbours in the split assembly); a source file in
`src/<library>/inline/` is that library's by its directory. The libraries of the regular code are the hand-edited ranges of
`config/SLUS_213.76/libraries.txt`. Where the right C++ is an inline member function in the class header, a copy that
matches belongs there eventually; for now each copy stays a separate unit because its address, flags and the surrounding
link-once order are part of what the build reproduces.

## INCLUDE_ASM

Every source file lists all functions of its range; `INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_XXXXXXXX);` marks one
that is still assembly. Two ways to implement it were considered:

1. *Include the assembly into the compiled object* (as oot or sly1 do with `.include`). Not adopted: the SN assembler
   (`-snas`) does not accept the splat output as is (`.size`, macros, gp-relative expressions, loop padding; splat issue #525),
   the exact short-loop padding of each unit depends on the assembler variant, and the build already assembles every
   function with the EE GNU assembler 2.10 as a separate object. Making all of that byte-identical through the compiler
   would put the existing matches at risk for no gain in workflow.
2. *A declarative marker* (chosen). `INCLUDE_ASM` expands to a harmless declaration (`include/include_asm.h`). The build reads
   the markers from the source (`tools/build/include_asm.py`), links each marked function from its per-function assembly object
   at its original position, as before, and takes every other function of the file's range from the compiled object.
   Assembly is therefore always assembled by the EE GNU assembler that rebuilds the unmodified image, and a compiled function
   cannot disturb its neighbours (`-ffunction-sections` gives it a section of its own, placed in its original slot).

The workflow is the same as with a real include: open the file, replace an INCLUDE_ASM line with C, run `ninja`, read `OK` or
the name of the function that differs. Conditionals around markers (`#ifdef NON_MATCHING`) are evaluated with the file's `-D`
flags.

## NON_MATCHING

A draft that does not match yet lives in its TU file as `#ifdef NON_MATCHING` <draft> `#else` INCLUDE_ASM `#endif`.
`python3 configure.py --non-matching` followed by `ninja` builds the drafts into `build/<GAME_ID>-nm/<boot>.nonmatching.elf`
(`tools/build/nm_build.py`): the markers inside `#else` branches stop applying, the drafts replace the assembly, and the shiftable
link moves everything else. It is not compared with the original and is not expected to boot. A file whose drafts do not
compile or link (their declarations are incomplete), or that the checks of `tools/build/units_verify.py prepare` reject (a symbol with no address), keeps its matching version; the list is in
`build/<GAME_ID>-nm/nm_fallback.json`. `python3 configure.py` returns to the matching build.

The build repeats until that set is stable (up to 8 attempts). Each attempt starts without the facts file of the one before
(`unit_facts.json`, written by `tools/build/units_verify.py prepare` from the objects of the attempt and read back by the units):
a stale copy would drop units from the compile, `prepare` would find no object for them and forget the demotion, and the link would
lack a function the units still call. `tests/tools/test_nm_build.py` checks this ordering without a backend.

Times (USA retail, two cores): a build from nothing (extract, splat, split, assemble 12,000 objects, link, pack) takes
about 1.5 to 2 minutes with the local toolchain; with the objects cached and one source unit changed about 15 s; with
nothing changed `ninja` does nothing.

ld cannot write the retail container: section-header order, the non-loaded `.reginfo`, `.DVP.*` and `.debug_str`
sections, and `e_flags` 0x20924001. `pack_elf.py` therefore takes the linked section contents and addresses from ld and
writes the headers from `build/<GAME_ID>/layout.json`, regenerating `.shstrtab` and `.reginfo` (with the linked `_gp`)
and rebasing the `.DVP.ovlytab` addresses that point into `.vutext`. The overlays and `.vutext`/`.vudata` are extracted
payloads, not rebuilt. Code and data come only from the reassembled sources and the compiled source files.

## Constants (rodata migration)

`split_objects.py` does for `.rodata`, `.lit4` and `.gcc_except_table` what splat's rodata migration does, with checks
splat does not make for this assembler. A splat data object (`dlabel` .. `enddlabel`) belongs to a function when exactly
one function refers to it and no data does; it is then written into that function's file (`.lit4` into a sibling
`func_XXXXXXXX.lit4.s`, because the assembler mishandles a small-data symbol defined next to the code that addresses it
off `$gp`). Constraints it enforces, found by building: an input section is placed whole, so a function keeps one
contiguous run per section; the assembler aligns `.short`/`.word`/`.float`/`.double` by itself, so a run is cut where such
a directive would need an earlier start than the original address allows. `ninja` prints, per section, how many bytes migrated and why the rest stays shared:
referenced from data (string tables, vtable-like arrays), referenced by several functions, unreferenced, or whose
function had a second, non-adjacent run. Most `.rodata` and `.lit4` migrates; `.gcc_except_table` migrates little: most tables
belong to a whole object file (their handler labels span several functions), which is translation-unit evidence for
the translation-unit map rather than something one function can carry.

## Function boundaries

Splat finds the function starts; `tools/build/boundaries.py` adds the ones it cannot see (`build/<GAME_ID>/boundaries.txt`, splat's
`symbol_addrs` format, written by `ninja` before the `split` stage from the image and the hand-listed `// explicit:` entries). Evidence from the
instructions of the image (all five retail versions behave alike):

- **Orphan pieces.** 8-byte pieces `<one non-branch instruction>; nop` (mostly `addiu $sp, $sp, N; nop`) sit between functions,
  1,169 of them in USA retail. Nothing calls or jumps to them or builds their address, their `N` does not follow the
  neighbouring frames, functions that match from C do not emit them, and a reference to the function behind a run points
  behind it (`%lo(func_00103928 + 0x8)`). Splat fused 123 runs with the function that follows, which kept those functions from
  matching; the tool starts a function behind every run (not across a branch, and not past an explicit start, see below).
  The runs stay assembly (`orphan` in `build/auto.json`).
- **Explicit starts.** A real function can open with the same shape (`mtc1 $zero, $f1; nop`, an FPU hazard nop, or an `addiu`
  or `daddu` that the code behind it consumes), so the last piece of a run is code. Such starts are listed by hand in
  `config/<GAME_ID>/explicit_boundaries.txt`, each behind a `// explicit: <reason>` line; `boundaries.py` ends the run there and
  adds the entry to the file it generates. USA retail has four: 0x1B0BD0, 0x280500, 0x316840 and 0x384E28. Without them the scan
  would start those functions one piece late.
- **Constructor list.** `__CTOR_LIST__` in `.data` (count word, that many pointers, zero) names every `_GLOBAL__I_*` stub. One of the
  116 entries in USA retail, 0x339c28, sat behind five orphan pieces that splat fused with it: `boundaries.py` adds the entries of the
  list as function starts (the stub then matches like the others).
- **Fall-through over-splits.** Where a function seems to fall through into the next one, the "extra" words are the function's
  own jump table (migrated `.rodata` counted as code) or follow an orphan piece. A function that ends in a computed `jr` is
  one function: internal branches or jump tables reach the rest, and no frame is allocated behind it. No real over-split remains.

The function list the tools use is splat's: `build/<GAME_ID>/placement.json` (starts and ends) and the split assembly, whose last
`endlabel` gives a function's size without the alignment padding (`tools/objdiff.py`). Nothing reads a second function list.

## Symbols and progress

`config/SLUS_213.76/symbols.txt` is the one place for names. It is edited by hand (and by `autodecomp.py register`, which adds the
mangled name of a function it compiles), in splat's `symbol_addrs` form. There are two kinds of line:

- **Bound names** (`Tick__4Game = 0x1b78d8; // type:func`): the name a compiled function is defined under (a mangled C++ name), or a
  name the source uses without defining. Linking depends on them, so `func_XXXXXXXX` stays the name of everything else and
  assembly references keep working.
- **Aliases** (`GameObjectManager_FindByName = 0x129160; // type:func alias`, `REG_GS_CSR = 0x12001000; // type:data alias`):
  readable working names, 269 for functions and 174 for data (hardware registers and the gp value). An alias never defines or binds a symbol and is not
  an original symbol; `tools/build/splits.py` keeps aliases apart from the bound names, so adding or changing one cannot change the
  build. Tools use them to label functions (`tus.py`, `next.py`). To give a
  function a real name, rename its definition in the source and add a bound-name line as above, not an alias.

Prototypes are not in `symbols.txt`. Recovered signatures live in `include/ps2/prototypes.h` (under the `func_XXXXXXXX` names,
the alias in a comment) and the structures they use in `include/ps2/recovered_types.h`; see "Types and signatures" in
[pipeline.md](pipeline.md).

`ninja progress` (or `python3 tools/progress.py [--tus N]`) prints the share of `.text` bytes and functions provided by source,
overall and by region, then by translation unit (complete, partial and untouched TUs by confidence and by library), and writes
`build/<GAME_ID>/progress.json`. `python3 tools/next.py tus` lists candidate TUs.

Other tools: `tools/build/tus.py` (TU boundaries and map, `ninja tus`), `tools/build/layout.py` (naming of TU files), `tools/build/include_asm.py` (markers), `tools/diffelf.py REF BUILT` (section-by-section diff), `tools/maint/shift_test.py` (shiftability test),
`tests/link/check.py` (SN object + GNU object linked by the toolchain's `ld`). In a sandbox script, the binutils tools
(`mipsel-linux-gnu-{ld,objcopy,readelf,objdump,nm}`, or the prefix in `$BLACK_BINUTILS_PREFIX`) are on PATH.

## Shiftability

`python3 tools/maint/shift_test.py SLUS_213.76 --nops 200` copies the split assembly to a scratch name, inserts NOPs into one
function, rebuilds and checks every symbolic reference against a symbol-derived address map. Result for 200 NOPs
(everything from `.text` onward moves): all 19,781 `jal`/`j`, 19,121 `%hi`, 25,118 `%lo`, 2,997 gp-relative accesses,
8,499 + 4,321 + 5 data pointers and 903 exception-table entries moved correctly, 0 inconsistencies. Known non-shiftable
spots: 984 raw `.word` values in `.data`, `.rodata` and `.sdata` that fall inside the image address range but are not
symbols in the split (almost all are numbers such as colours, hashes and flags; at least 33 words around `.data` 0x3C3DC0
point into the `.vutext` blob and would need symbols), and any address built by arithmetic that is not a `%hi/%lo` pair.
One NOP only moves the code behind it by 8 bytes (function alignment) and the alignment slack before `.vutext` hides it
from the data sections.
