# Black (PS2) decompilation

[![CI](https://github.com/dpusceddu/blackDecomp/actions/workflows/ci.yml/badge.svg)](https://github.com/dpusceddu/blackDecomp/actions/workflows/ci.yml)
[![License: CC0-1.0](https://img.shields.io/badge/license-CC0--1.0-lightgrey.svg)](LICENSE)
[![Code](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/dpusceddu/blackDecomp/main/progress/code.json)](progress/summary.md)
[![Functions](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/dpusceddu/blackDecomp/main/progress/functions.json)](progress/summary.md)

A work-in-progress matching decompilation of the PS2 version of *Black* (Criterion Games, 2006). The goal is readable C/C++
source that compiles, with the original compilers, to the exact bytes of the retail executable. `ninja` rebuilds the executable
byte for byte, with recovered source replacing its assembly one function at a time (`INCLUDE_ASM` lines in the translation
unit files). Because the rebuild is *shiftable*
(code and data can move and every reference is fixed up by the linker), it also works as a base for modding.

## Supported versions

Each version is identified by the game ID of its boot executable (`SYSTEM.CNF`, `BOOT2`).

| Game ID | Region | SHA-256 of the executable | Rebuild matches | Recovered source |
| --- | --- | --- | --- | --- |
| `SLUS_213.76` | USA | `141b05209570458af9c8e27ab1911f258da6353909d813cd572df026254ffe4c` | yes | 5,563 functions (15.1 % of `.text`) |
| `SLES_538.86` | Europe | `bbed3444a22d28b7fdc641e15a1759b6ece1c9cbc5a13331586025ff8fc2b948` | yes, from assembly | none yet |
| `SLES_540.30` | Europe, Australia | `7e6f25966389656a9bdc534c2514a3a56f205054ee66b43c27a18b111add309f` | yes, from assembly | none yet |
| `SLKA_253.72` | Korea | `fb59440b00444ff64be1436fd757452c3eead9e560532fad74e4d05e913a6b94` | yes, from assembly | none yet |
| `SLPM_663.54` | Japan | `bf70d92152237eae6908e973d44dde8ce49d9e7e32b34e9b7ad41f79ad569f43` | yes, from assembly | none yet |

"Rebuild matches" means `ninja` reproduces the executable byte for byte. `SLUS_213.76` is the only version with recovered
source and the only one that routine work builds, measures and checks. The other four are rebuilt from their own assembly
and are checked before releases (`python3 tools/check_versions.py` configures and builds all five and prints `OK` or
`MISMATCH` for each); their configurations stay committed. Source units are written for the USA version.

## Legal note

This repository contains no game assets and no game code: no disc contents, no executables, no disassembly and no compiler
output. The source is a new work written to compile to the same behavior. You need your own copy of the game, and you extract
the executable from it yourself. The build tools download the third-party compilers from their public archives on your
machine; they are not redistributed here.

## Quickstart

You need the boot executable of your own copy (see the table) as `orig/<GAME_ID>/<GAME_ID>`, for example
`orig/SLUS_213.76/SLUS_213.76`, and a Linux x86-64 environment: the compilers are a Windows program (run through
[wibo](https://github.com/decompals/wibo)) and 32-bit Linux programs.

**Linux (Debian 12 or Ubuntu 22.04 and later)**

```sh
sudo apt update && sudo apt install -y git ninja-build python3 python3-venv python3-pip binutils-mipsel-linux-gnu libc6-i386 xz-utils ca-certificates
git clone https://github.com/dpusceddu/blackDecomp.git
cd blackDecomp
mkdir -p orig/SLUS_213.76 && cp /path/to/SLUS_213.76 orig/SLUS_213.76/
python3 -m venv .venv && .venv/bin/pip install -r requirements.txt
python3 tools/toolchain.py install        # pinned compilers, assemblers and wibo into build/toolchain (SHA-256 checked)
python3 configure.py                      # default --version SLUS_213.76
ninja
```

A build from scratch takes a few minutes; a rebuild after changing one file takes seconds. It ends with

```
OK  SLUS_213.76  SLUS_213.76  sha256 141b05209570458af9c8e27ab1911f258da6353909d813cd572df026254ffe4c
```

or with a section-by-section mismatch report. Another version: `python3 configure.py --version SLES_538.86` (and so on); to
check all five, run `python3 tools/check_versions.py`.

**Windows**: use WSL 2 with Ubuntu and follow the Linux steps inside it (keep the checkout in the Linux file system).

**macOS and other platforms**: the tools only run on Linux x86-64, so use Docker.

```sh
docker build --platform linux/amd64 -t black-decomp .
docker run --rm -it --platform linux/amd64 -v "$PWD":/workspace black-decomp
# inside: python3 configure.py && ninja
```

On Apple silicon this relies on the emulation of x86-64 Linux containers and has not been tested.

**Binutils.** `ld` and `objcopy` for little-endian MIPS come from the distribution package `binutils-mipsel-linux-gnu`
(Debian, Ubuntu; version 2.40 is the tested one). On a distribution without it, use Docker, or build GNU binutils 2.40 with
`--target=mipsel-linux-gnu` and put the tools on `PATH` (or set `BLACK_BINUTILS_PREFIX`). The decompals
`binutils-mips-ps2-decompals` prebuilt cannot link this executable: its `ld` has no little-endian MIPS emulation.

## Progress

```sh
ninja progress                              # share of .text and of functions provided by source, per region and TU
python3 tools/progress.py --libraries       # ... per library directory of src/
ninja badges                                # refresh progress/ (badge files, summary.md) and the table below
```

Functions and bytes of `.text` rebuilt from recovered source (USA, `SLUS_213.76`):

<!-- progress:begin (tools/badges.py) -->

| Library | Functions from source | Share | Bytes from source | Share |
| --- | ---: | ---: | ---: | ---: |
| game | 2,908 / 6,650 | 43.7 % | 176,864 / 1,460,176 | 12.1 % |
| kynapse | 687 / 905 | 75.9 % | 107,512 / 257,240 | 41.8 % |
| rw_core | 85 / 449 | 18.9 % | 4,744 / 181,416 | 2.6 % |
| rw_audio | 309 / 754 | 41.0 % | 23,368 / 109,560 | 21.3 % |
| animation | 195 / 350 | 55.7 % | 26,128 / 69,680 | 37.5 % |
| physics | 93 / 206 | 45.1 % | 11,864 / 78,240 | 15.2 % |
| apt | 129 / 633 | 20.4 % | 7,520 / 267,744 | 2.8 % |
| sony | 274 / 756 | 36.2 % | 9,000 / 142,096 | 6.3 % |
| libc | 75 / 213 | 35.2 % | 4,088 / 70,472 | 5.8 % |
| linkonce | 808 / 983 | 82.2 % | 39,296 / 78,840 | 49.8 % |
| **Total** | **5,563 / 11,899** | **46.8 %** | **410,384 / 2,715,464** | **15.1 %** |

<!-- progress:end -->

The numbers are produced locally with `ninja badges` from `ninja progress`, which measures the finished, byte-identical
image; anyone with the game can reproduce them with `ninja` and `ninja progress`. The objdiff report counts slightly
differently ([docs/progress-reports.md](docs/progress-reports.md)).

## Diffing with objdiff

`ninja objdiff` writes `objdiff.json` and, for every source unit, an object with the original code and an object compiled
from source. Open the repository root in [objdiff](https://github.com/encounter/objdiff) to compare function by function.
`ninja report` writes the progress report to `build/SLUS_213.76/report.json` (needs `python3 tools/toolchain.py install
--objdiff` once). Details: [docs/progress-reports.md](docs/progress-reports.md).

## Modding notes

The rebuild links every function and data object from separate pieces and lays them out with a generated linker script, so
adding, removing or growing code moves everything behind it and the linker fixes the references (`jal`, `%hi/%lo`, gp-relative
accesses, pointers in data, exception tables). A test inserting 200 NOPs into one function relinks with no inconsistency
([docs/build.md](docs/build.md#shiftability)); the known exceptions are raw numbers in data that look like addresses. To change
behavior, edit a translation unit file (`src/<library>/`, listed in `config/SLUS_213.76/splits.yaml`) and rebuild; the result is a modified
executable, not a match, so `ninja` will report a mismatch against the original hash. Never distribute the game's executable
or assets; distribute patches in a form that needs the user's own copy.

## Project structure

```
configure.py          writes build.ninja (and picks the version)
config/<GAME_ID>/     per-version splat configuration, ELF layout, function boundaries, expected SHA-256; SLUS_213.76 also has
                      splits.yaml (source files, address ranges, flags), symbols.txt (names), equivalent.yaml
config/               tus.yaml (translation unit map), toolchain pins, shared data
orig/<GAME_ID>/       your executable goes here (ignored by Git)
src/<library>/        one file per translation unit: recovered functions as C/C++, the rest as INCLUDE_ASM lines, drafts in
                      #ifdef NON_MATCHING blocks (game, kynapse, animation, physics, rw_core, rw_audio, apt, sony, libc, linkonce)
include/<library>/    headers per library, include/ps2/ for helpers shared by all
tools/                build, analysis and pipeline tools; tools/studies/ keeps finished experiments
progress/             badge files and the per-library table written by `ninja badges` (committed)
docs/                 build, translation unit files and split list, pipeline, TU map, matching handbook, status, history
tests/                tests that need no game files
asm/ build/ data/     generated (asm/<GAME_ID>/nonmatchings/ holds the assembly of every function), ignored
```

## FAQ

**How does the matching work?** The executable is split into one assembly object per function plus data objects, which link
back into the identical image. A translation unit file lists all functions of its range; the ones written in C or C++ replace the assembly of the ones still marked `INCLUDE_ASM`; if the
compiler reproduces the original instructions and the full image stays identical, the function is *exact*. Details:
[docs/build.md](docs/build.md), [docs/units.md](docs/units.md), [docs/matching-handbook.md](docs/matching-handbook.md), [docs/tools.md](docs/tools.md) (index of the tools).

**How do I work on a function?** Open its TU file (`python3 tools/next.py tus` lists candidates), replace the function's
`INCLUDE_ASM(...)` line with C or C++, run `ninja`: it prints `OK`, or the file and function that differ. A draft that does not
match yet goes in `#ifdef NON_MATCHING` ... `#else` INCLUDE_ASM `#endif`; `python3 configure.py --non-matching` builds the drafts into
a separate executable. Steps and an example: [CONTRIBUTING.md](CONTRIBUTING.md).

**What do exact, equivalent and draft mean?** Every function has an evidence tier. `exact`: compiled from source, the whole
image is byte-identical. `equivalent`: agrees with the original on recorded machine states with measured coverage; it is not
a proof and never replaces assembly in the build. `draft`: readable or machine-written, no evidence. A function is never
described as more than its tier. See [docs/status.md](docs/status.md).

**How was this made?** Much of the work was done with AI coding agents under human direction.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for picking a translation unit, the matching workflow, commit rules and code style.
Agents and other automation: [AGENTS.md](AGENTS.md).

## License

[CC0 1.0 Universal](LICENSE): the source in this repository is dedicated to the public domain. The game, its code and its
assets belong to their owners and are not included.

## Acknowledgments

[splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm) and
[rabbitizer](https://github.com/Decompollaborate/rabbitizer) for splitting and disassembling; [m2c](https://github.com/matt-kempster/m2c)
for first drafts; [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) for the search; the
[decomp.me compilers](https://github.com/decompme/compilers) archives; [wibo](https://github.com/decompals/wibo) for running
the Windows tools; [objdiff](https://github.com/encounter/objdiff) for comparison and reports; and the decompilation
projects whose methods this one follows (see the links in [docs/matching-handbook.md](docs/matching-handbook.md)).
