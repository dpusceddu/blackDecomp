# Phase 0 findings: inputs and environment

Produced by `tools/discs.py`, `tools/inputs.py`, `tools/symbols.py`, `tools/compile.py` and
`tools/studies/asmcheck.py`. Hashes and ELF metadata are in `config/variants.json`; raw dumps stay in `.local/`.

## Variants

| Slug | Boot file | Image | Files | Boot ELF size | `.text` | Notes |
| --- | --- | --- | --- | --- | --- | --- |
| `usa-retail` | `SLUS_213.76` | DVD 3.92 GB | 585 | 3,371,868 | 2,715,464 | Reference. SHA-256 `141b0520…6254ffe4c` matches the extracted copy |
| `usa-beta-2005-08-16` | `SLUS_000.00` | CD 322 MB | 102 | 2,388,744 | 1,913,448 | Early development build, entry `0x13e718` |
| `usa-demo` | `SLUS_291.80` | CD 661 MB | 128 | 3,148,184 | 2,496,200 | Entry `0x157d30` |
| `eu-beta-2006-01-09` | `SLES_538.86` | DVD 3.91 GB | 697 | 3,371,996 | 2,715,656 | Boot ELF identical to `eu-retail` |
| `eu-retail` | `SLES_538.86` | DVD 3.91 GB | 697 | 3,371,996 | 2,715,656 | PAL, five languages |
| `eu-demo` | `SLED_539.37` | CD 667 MB | 136 | 3,148,568 | 2,496,840 | Same build family as `usa-demo` |
| `eu-au-retail` | `SLES_540.30` | DVD 3.92 GB | 602 | 3,371,868 | 2,715,528 | Same ELF size as USA, 64 bytes more `.text` |
| `jp-retail` | `SLPM_663.54` | DVD 3.93 GB | 584 | 3,372,252 | 2,715,912 | `VER = 1.01`, NTSC |
| `kr-retail` | `SLKA_253.72` | DVD 3.92 GB | 585 | 3,371,996 | 2,715,560 | NTSC |

The beta and demo images are raw CD images (MODE2/2352 bin plus cue); the rest are 2048-byte DVD ISOs.
`tools/iso.py` reads both. Zip and image hashes are in `config/variants.json`.

Every boot executable is a statically linked 32-bit little-endian MIPS ELF with `e_flags 0x20924001` and
a single PT_LOAD segment. All have the same section skeleton as USA retail (`.text`, `.vutext`, `.reginfo`,
`.DVP.*` overlays, `.debug_str` with one NUL byte, `.data`, `.vudata`, `.rodata`, `.gcc_except_table`,
`.lit4`, `.sdata`, `.sbss`, `.bss`, `.vubss`).

### Debug and symbol data in the EE executables

None. No variant has `.symtab`, `.strtab`, a non-empty `.mdebug`, `.debug_*` content, STABS, DWARF or
`.comment`. The only extra section anywhere is an empty `.mdebug.eabi64` in the two demos. There are no
GCC or SN banners and no tool version strings. The single date string, `Core built at Feb 28 2005`,
belongs to a middleware library (RenderWare Audio, linked into every variant), not to the game build.
Source paths are not retained either: the only path in any executable is the video decoder file
`GameShared/GameClasses/Graphical/VideoDecoder/Ps2/vibuf.c` (a vendor file; the beta spells the root as
`d:/Work/Black/`, the others as `d:/alienbrainwork/`). `GTASSERT` messages keep format strings but the
`__FILE__` arguments are not in the data.

### Comparison with USA retail

`.text` is compared as instruction words with address fields masked. The masks cover `j`/`jal` targets,
branch offsets, `lui` immediates and the `%lo` half of an address (immediates whose base register was set
by a preceding `lui`, or is `gp`). The windows are function-sized: the code is cut after each `jr ra` and
its delay slot. "Window exact" is the share of words in windows whose masked hash also occurs in retail.
"Loose" additionally masks every immediate (struct offsets, constants). "Shingle" is the share of words
covered by an 8-word masked run that also occurs in retail.

| Variant | `.text` delta | Window exact | Window loose | Shingle (masked) | Shingle (loose) | SN unwind groups | DVP overlays |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `eu-au-retail` | +64 | 98.3% | 99.9% | 99.98% | 100% | 281 | 88 |
| `eu-retail` / `eu-beta` | +192 | 80.8% | 99.9% | 99.2% | 99.99% | 281 | 88 |
| `kr-retail` | +96 | 80.7% | 99.8% | 99.2% | 99.99% | 281 | 88 |
| `jp-retail` | +448 | 80.5% | 99.4% | 99.2% | 99.95% | 281 | 88 |
| `usa-demo` | -219,264 | 36% | 45% | 64% | 69% | 279 | 90 |
| `eu-demo` | -218,624 | 36% | 45% | 64% | 69% | 279 | 90 |
| `usa-beta-2005-08-16` | -802,016 | 46% | 57% | 71% | 77% | 259 | 56 |
| `usa-retail` | 0 | | | | | 281 | 88 |

The PAL, Korean and Japanese builds are the USA code plus small changes. The 19% of windows that differ
only in exact masking, as sampled in the Korean build, differ by a constant `+0x80` shift of member
offsets from one base register (a structure that grew by 128 bytes), which the loose column absorbs; the `.rodata` differences are a few
dozen bytes. `eu-au-retail` has no such shift and is the closest relative of USA (it still differs
elsewhere: the `.rodata` and `.text` deltas above). The demos and the beta are earlier builds with 6%, 40%
and 31% less `.text` and visibly different code. All variants have the same CIE form of embedded unwind
groups that `the companion project` ties to SN 1.36 (259 to 281 groups), so one compiler family is used throughout.

Section size differences against USA, besides `.text`: PAL/KR/JP change `.rodata` by 16 to 48 bytes and
nothing else. The demos differ in `.vutext` (+4,176), `.data` (-2,056), `.rodata`, `.bss` (+4,032),
`.gcc_except_table` (+88) and have two more overlays plus the empty `.mdebug.eabi64`. The beta has 32 fewer
overlays, 57 KB less `.vutext`, 31 KB less `.data`, 33 KB less `.rodata` and 106 KB more `.bss`.

### Disc contents compared with USA retail

- **USA beta** (102 files): lacks nearly everything (levels 00 and 04 only, a handful of sounds and guns).
  Extra files are development tooling on the IOP side: `ATTYMON.IRX` (TTY monitor), `GTFSATMN.IRX`,
  `GTFSHOST.IRX` (host file system), `RWSCOMMS.IRX` (RenderWare Studio comms), a set of Sony network
  modules (`DEV9`, `INET`, `INETCTL`, `NETCNF`, `SMAP`) with 19 network `.CNF` files, and `DATA/VDB.XML`.
  Only 7 of its 17 IOP modules equal retail's.
- **Demos**: about 130 files, 32 `.DB`/`.WDD` gun pairs not in retail, one `VDB.XML`, 7 of 8 IOP modules
  equal retail's (`RWA.IRX` differs).
- **EU beta vs EU retail**: the file listings are identical. The boot executable is byte-identical. Only
  `GLOBDATA.BIN` differs (verified by hashing every file), so the "beta" label does not mean an earlier
  build of the code.
- **EU/AU retail**: 21 added files (UK language strings, trailers) and 4 missing ones. **Japanese**: Japanese
  strings, font and speech banks. **Korean**: one file differs in name only (the boot file).
- **IOP modules**: the 9 retail `.IRX` files are byte-identical across all five retail regions.

### IOP modules (out of scope, but informative)

IOP modules are MIPS R3000 code, so they do not map onto the EE executable. Most are stripped of
everything but a one-entry `.symtab`. Two beta modules differ: `RWSCOMMS.IRX` keeps a full symbol table (10
functions, 17 objects, 3 source files under `C:\RWStudio\console\Archive\game_framework\source\...`),
DWARF 1 `.debug` (8.3 KB) and a `.line` table (about 210 entries), and the `.comment` section names
`MW MIPS C Compiler (2.4.1.01)`, `PlayStation2_IOP`, i.e. CodeWarrior for the IOP. `GTFSATMN.IRX` carries
the same `.comment`. This shows that the studio's IOP code was built with CodeWarrior and that the game
framework is RenderWare Studio's. It does not describe the EE toolchain.

### Beta-specific highlights

- A debug overlay is present in the beta executable only: memory-pool names (`eMB_Level`, `eMB_Effects`,
  `eMB_Physics`, `eMB_Characters`, ...), profiler/HUD labels for effect managers (sparks, tracers, glass,
  bullet holes, muzzle flash) and actor-state readouts.
- About ten profiler zone names of the form `Class::Method` that retail drops:
  `CBkActor::{Update,RequestAction,EvaluateState,UpdateBoneMatrices}`,
  `CFleeAgent::{CheckDangerVisible,ComputeDestination}`, `CFollowerAgent::ComputeRealDistance`,
  `CHideAgent::{ComputeDestination,CheckPositionVisible}`, `CShooterAgent::BotShootAtEnemy` and
  `Kaim::CEntityManager::ComputeCommonInfo`. Retail keeps only `CPathFinder::FindNextMove::*` and
  `CBkActor::Update`. They name functions through the profiler call sites, but they do not give file
  boundaries.
- Early value-database paths (`../Export/ValueDB/Weapons/`, `Sound/*.cfg`) and level/chardata paths.
- `GTASSERT` is present in all builds, so the assertion macro is shared.

## Symbols (Task 2)

No EE executable has symbols or debug data, so nothing transfers to USA retail. `tools/symbols.py` dumps
anything it finds. It found one symbol-bearing file on all nine discs, `RWSCOMMS.IRX` in the beta (10
functions, 17 objects, 3 source files, DWARF 1 types and a line table). A search of its function heads in
the retail `.text` found none: it is IOP code. The share of retail functions that would receive a name or a
source-file assignment from symbols is therefore 0%. Translation-unit boundaries and compiler flags
cannot be read from any variant's symbols.

## Compiler check (Task 3)

The build backend was reachable. `tools/compile.py` compiled `tests/toolchain/trivial.c` and `trivial.cpp` (a class
with a virtual function and a derived class) with SN GCC 2.95.3 build 1.36 under `-O2 -G0 -snas` and under
`-O2 -G8` (default GNU assembler), and also `-O2 -G8 -snas`. All outputs are ELF32 relocatable MIPS objects
with `e_flags 0x20924001`, the same flags as the retail executable.

- `-G0 -snas`: `.text`, `.data`, `.reginfo`, `.symtab`; no `.mdebug` (the SN assembler does not emit one); global
  uninitialised data is an ordinary common symbol; addresses use `HI16/LO16` pairs only; no `GPREL16`.
- `-G8` with the GNU assembler: also `.bss` and `.mdebug` (536 bytes for the C file, 2.6 KB for C++); the global
  `counter` becomes a small common symbol (section index `0xff03`, MIPS small common) and three `R_MIPS_GPREL16`
  relocations appear. With `-snas` the same flag gives the small-common index and a `GPREL16` for it, but no
  `.mdebug` and no separate `.bss`.
- In C++ output `-G8` creates a 15 byte `.sdata`, GPREL16 relocations in a `.gnu.linkonce.t.*`
  section and, in both modes, the GCC 2.95 layout of one `.gnu.linkonce.d.*`/`.t.*` section per vtable, type
  info and inline function. The tool pitfall encountered: `-snas` must be a separate argument (it is an
  option of the driver, not of `cc1`).

## Assembler and linker check (Task 4)

Binutils for MIPS is not installed in the build image (Debian 12, x86-64 `as`/`ld`/`objdump` 2.40 with no MIPS
target), and nothing may be installed on the Mac. The catalog does contain EE-aware GNU assemblers that run
in the container, and `tools/sandbox.py` runs scripts there:

| Assembler | Where | Runs in container |
| --- | --- | --- |
| GNU as 2.10-ee-001003-1 | `ee-gcc2.96` package, Linux i386 | yes |
| GNU as 2.9-ee-991111 | `ee-gcc2.9-991111-01` package, Linux i386 | yes |
| GNU as 2.9-ee-991111b | the SN 1.36 package (`as.exe`, the driver default), via `wibo` | yes |

`tools/studies/asmcheck.py` samples the USA retail `.text`, disassembles it with rabbitizer's R5900 support and
reassembles it. The sample has two parts: every distinct mnemonic rabbitizer recognises (256, 2,684 words;
240 are branches compared with the offset field masked and a label target) and 40 random contiguous
windows of 1,500 words (60,000 words) with in-window branch targets as labels.

Result for all three assemblers: all 2,684 isolated words assemble to the identical encodings. That covers
ordinary MIPS, MMI (`pextlw`, `ppacb`, `pmulth`, ...), `lq`/`sq`, COP1 and COP2/VU0 macro instructions
(`lqc2`, `vaddx`, `vmadd*`, `vcallms`, `qmtc2.ni`, `ctc2.ni`), COP0 and `cache`/`sync.p`. Only syntax adaptation
is needed: rabbitizer prints named registers and VU0 specials with `$` (`$ACC`, `$Q`, `$I`), so
`regNames_namedRegisters` must be off (numeric `$n` registers; the assemblers reject `$zero`-style names for
many instructions) and `$ACC/$Q/$I/$R/$P` must be printed bare.

Findings that need handling in Phase 1:

1. **Short-loop padding.** Backward branches that jump back five words or fewer (941 of the 6,412 backward
   branches in retail, among 54,624 branches) make the assembler insert NOPs before the branch (2.9-ee) or
   fail with "problematic short loop for Emotion Engine in noreorder section" (2.10-ee). The game was not
   assembled with that padding. Emitting such branches as raw `.word` values fixes it: with that, the
   2.10-ee assembler reassembled 40 of 40 windows identically, 2.9-ee-991111b 39 of 40 and 2.9-ee-991111
   38 of 40. The remaining failures are a branch-likely loop (`bgezl` back 13 words, with a call in the body)
   that 2.9-ee also pads, which the same raw-word treatment would cover. Local loop offsets do not change
   when a function moves, so this does not hurt the shiftable build.
2. **Words rabbitizer does not decode.** 579 words print as `.word` (459 COP1 words with a zero format
   field and function `0x24`, and 120 `vsqrt` words `0x4a......`) and 4 `0x00ff00ff` words in `.text`.
   They survive byte-exactly as data but are unreadable.
3. **`e_flags`.** GNU-assembled objects get `0x20920001`; SN objects and the retail ELF have `0x20924001` (the
   extra `0x4000` bit). The final ELF's flags will need to be set explicitly.

**GNU ld could not be checked.** There is no MIPS-capable `ld` anywhere in the isolated environment (the
catalog has only assemblers, compiler drivers and the CodeWarrior linker, and Debian's `ld` knows only x86
emulations). Options, none of which touch the Mac's system:
  1. Add a static MIPS binutils (a distro `binutils-mipsel-linux-gnu` package or a ps2dev `mips64r5900el-ps2-elf`
     build, with `ld`) to the build backend's read-only tool directory, the way `tools/ps2/bootstrap.py` uploads the
     compiler catalog. This needs a download, which the user has to approve.
  2. Build binutils from source in a separate container that has a C compiler. The current image has none.
  3. Use the CodeWarrior linker (`mwldps2.exe`) in the catalog. This is unlikely to be compatible with GNU linker scripts.
Until one of these exists, linking of SN objects together with GNU-assembled objects (and the `e_flags`
question above) stays open.

## Decision proposal

**Primary target: USA retail (`SLUS_213.76`).** No variant has symbols or debug data, so nothing makes
another build a better target, and USA retail is already the Ghidra, PS2-exact-match and Xbox-counterpart
reference. Other variants give no names or types.

How to use the others:

- **PAL, Korean, Japanese and EU/AU retail (and the EU "beta", which is the PAL retail executable):** boundary
  evidence. Their code is the same compilation with small deltas, so a function's diffs show which functions
  are region-specific, which data each routine touches (a `+0x80` member shift marks a structure that
  differs, usually language or region data), and where `.text` and `.rodata` grew. `eu-au-retail` is the
  closest relative and a cheap second image for shiftability tests. They are not independent matching targets.
- **USA beta (2005-08-16) and the two demos:** name and type sources and order evidence, not byte targets.
  Their code is only 64% to 71% shingle-similar. The beta's profiler zone names and memory-pool names give a
  few `Class::Method` labels. Function sets that appear in demos and the beta but not in retail, or that
  changed, indicate which code moved between builds. The CIE counts (259 to 281) show one compiler family.
- **Compiler evidence:** unwind-record form is identical in every build, so SN 1.36 `-O2 -G0 -snas` remains the
  working hypothesis. Per-TU `-G` differences cannot be learned from any variant's symbols.
- **IOP modules and RWSCOMMS:** out of scope; they show that the studio's IOP code used CodeWarrior and the game
  framework is RenderWare Studio's, nothing more.

Open items for the coordinator: a MIPS `ld` inside the isolation (above), and the short-loop treatment in
the Phase 1 split.
