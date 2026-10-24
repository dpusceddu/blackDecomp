# Inputs and versions

Produced by `tools/maint/discs.py`, `tools/maint/inputs.py`, `tools/maint/symbols.py` and `tools/studies/asmcheck.py`. The survey writes hashes and ELF metadata
to the ignored `build/survey/variants.json` and raw dumps to `.local/`; `config/versions.json` (by hand) keeps the five supported versions. The build itself only needs the boot executables in
`orig/<GAME_ID>/`; the disc survey tools are for maintainers who have the disc images.

## Versions

A version is identified by the game ID of its boot executable. The survey also covered an early USA beta, two demos and a
Europe disc labelled beta; those are not build targets.

| Game ID | Version | Image | Files | Boot ELF size | `.text` | Notes |
| --- | --- | --- | --- | --- | --- | --- |
| `SLUS_213.76` | USA retail | DVD 3.92 GB | 585 | 3,371,868 | 2,715,464 | Reference. SHA-256 `141b0520…6254ffe4c` matches the extracted copy |
| `SLUS_000.00` | USA beta, 2005-08-16 | CD 322 MB | 102 | 2,388,744 | 1,913,448 | Early development build, entry `0x13e718` |
| `SLUS_291.80` | USA demo | CD 661 MB | 128 | 3,148,184 | 2,496,200 | Entry `0x157d30` |
| `SLES_538.86` | Europe retail | DVD 3.91 GB | 697 | 3,371,996 | 2,715,656 | PAL, five languages. The disc labelled "Europe beta, 2006-01-09" has the identical boot executable |
| `SLED_539.37` | Europe demo | CD 667 MB | 136 | 3,148,568 | 2,496,840 | Same build family as the USA demo |
| `SLES_540.30` | Europe, Australia retail | DVD 3.92 GB | 602 | 3,371,868 | 2,715,528 | Same ELF size as USA, 64 bytes more `.text` |
| `SLPM_663.54` | Japan retail | DVD 3.93 GB | 584 | 3,372,252 | 2,715,912 | `VER = 1.01`, NTSC |
| `SLKA_253.72` | Korea retail | DVD 3.92 GB | 585 | 3,371,996 | 2,715,560 | NTSC |

The beta and demo images are raw CD images (MODE2/2352 bin plus cue); the rest are 2048-byte DVD ISOs.
`tools/maint/iso.py` reads both. The disc image hashes of the supported versions are in `config/versions.json`.

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

| Version | `.text` delta | Window exact | Window loose | Shingle (masked) | Shingle (loose) | SN unwind groups | DVP overlays |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `SLES_540.30` | +64 | 98.3% | 99.9% | 99.98% | 100% | 281 | 88 |
| `SLES_538.86` | +192 | 80.8% | 99.9% | 99.2% | 99.99% | 281 | 88 |
| `SLKA_253.72` | +96 | 80.7% | 99.8% | 99.2% | 99.99% | 281 | 88 |
| `SLPM_663.54` | +448 | 80.5% | 99.4% | 99.2% | 99.95% | 281 | 88 |
| `SLUS_291.80` | -219,264 | 36% | 45% | 64% | 69% | 279 | 90 |
| `SLED_539.37` | -218,624 | 36% | 45% | 64% | 69% | 279 | 90 |
| `SLUS_000.00` | -802,016 | 46% | 57% | 71% | 77% | 259 | 56 |
| `SLUS_213.76` | 0 | | | | | 281 | 88 |

The PAL, Korean and Japanese builds are the USA code plus small changes. The 19% of windows that differ
only in exact masking, as sampled in the Korean build, differ by a constant `+0x80` shift of member
offsets from one base register (a structure that grew by 128 bytes), which the loose column absorbs; the `.rodata` differences are a few
dozen bytes. `SLES_540.30` has no such shift and is the closest relative of USA (it still differs
elsewhere: the `.rodata` and `.text` deltas above). The demos and the beta are earlier builds with 6%, 40%
and 31% less `.text` and visibly different code. All variants have the same CIE form of embedded unwind
groups that are tied to SN 1.36 (259 to 281 groups), so one compiler family is used throughout.

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

## Symbols

No EE executable has symbols or debug data, so nothing transfers to USA retail. `tools/maint/symbols.py` dumps
anything it finds. It found one symbol-bearing file on all nine discs, `RWSCOMMS.IRX` in the beta (10
functions, 17 objects, 3 source files, DWARF 1 types and a line table). A search of its function heads in
the retail `.text` found none: it is IOP code. The share of retail functions that would receive a name or a
source-file assignment from symbols is therefore 0%. Translation-unit boundaries and compiler flags
cannot be read from any variant's symbols.

## What the first disassembly round found

Reassembling the USA retail `.text` with the EE-aware GNU assemblers (`tools/studies/asmcheck.py`; rabbitizer's R5900
support, numeric registers) reproduces every one of the 256 distinct mnemonics (2,684 words) and 40 random windows of 1,500
words, with three points that shaped the build:

1. **Short-loop padding.** Backward branches that jump back five words or fewer (941 of the 6,412 backward branches in
   retail, among 54,624 branches) make the assembler insert NOPs before the branch or refuse the file. The game was not
   assembled with that padding, so such branches are emitted as raw `.word` values. Local loop offsets do not change when a
   function moves, so this does not hurt the shiftable build.
2. **Words rabbitizer does not decode.** 579 words print as `.word` (459 COP1 words with a zero format field and function
   `0x24`, and 120 `vsqrt` words `0x4a......`) and 4 `0x00ff00ff` words in `.text`. They survive byte-exactly as data but are
   unreadable.
3. **`e_flags`.** GNU-assembled objects get `0x20920001`; SN objects and the retail ELF have `0x20924001`, so the packer
   (`tools/build/pack_elf.py`) writes the final flags explicitly.

SN GCC 2.95.3 build 1.36 under `-O2 -G0 -snas` produces ELF32 relocatable MIPS objects with `e_flags 0x20924001`, like the retail
executable: no `.mdebug` (the SN assembler does not emit one), uninitialised globals as common symbols, `HI16/LO16` pairs and no
`GPREL16`. With `-G8` it uses small-data symbols and `GPREL16` relocations; C++ output keeps the GCC 2.95 layout of one
`.gnu.linkonce.*` section per vtable, type info and inline function. `-snas` must be a separate argument (it is an option of the
driver, not of `cc1`).

## Target choice

**Primary target: USA retail (`SLUS_213.76`).** No version has symbols or debug data, so nothing makes
another build a better target, and USA retail is where the name aliases and the Xbox counterpart leads were made.
Other versions give no names or types.

How to use the others:

- **PAL, Korean, Japanese and EU/AU retail (and the EU "beta", which is the PAL retail executable):** boundary
  evidence. Their code is the same compilation with small deltas, so a function's diffs show which functions
  are region-specific, which data each routine touches (a `+0x80` member shift marks a structure that
  differs, usually language or region data), and where `.text` and `.rodata` grew. `SLES_540.30` is the
  closest relative and a cheap second image for shiftability tests. They are not independent matching targets.
- **USA beta (2005-08-16) and the two demos:** name and type sources and order evidence, not byte targets.
  Their code is only 64% to 71% shingle-similar. The beta's profiler zone names and memory-pool names give a
  few `Class::Method` labels. Function sets that appear in demos and the beta but not in retail, or that
  changed, indicate which code moved between builds. The CIE counts (259 to 281) show one compiler family.
- **Compiler evidence:** unwind-record form is identical in every build, so SN 1.36 `-O2 -G0 -snas` remains the
  working hypothesis. Per-TU `-G` differences cannot be learned from any variant's symbols.
- **IOP modules and RWSCOMMS:** out of scope; they show that the studio's IOP code used CodeWarrior and the game
  framework is RenderWare Studio's, nothing more.

