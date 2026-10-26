# Black (PS2) decompilation

[![CI](https://github.com/dpusceddu/blackDecomp/actions/workflows/ci.yml/badge.svg)](https://github.com/dpusceddu/blackDecomp/actions/workflows/ci.yml)
[![License: CC0-1.0](https://img.shields.io/badge/license-CC0--1.0-lightgrey.svg)](LICENSE)
[![Code](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/dpusceddu/blackDecomp/main/progress/code.json)](#progress)
[![Functions](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/dpusceddu/blackDecomp/main/progress/functions.json)](#progress)

A matching decompilation of *Black* (Criterion Games, 2006) for the PlayStation 2: readable C and C++ that the original
compilers turn back into the exact bytes of the retail game.

*Black* never had a PC release or a remaster. Its source code would make native ports, mods, new weapons and effects,
better graphics and preservation possible. This project rebuilds that source, function by function, and proves every step.

## What exists today

- **A byte-identical rebuild.** `ninja` rebuilds the USA executable byte for byte from recovered source plus the assembly
  of the functions not yet recovered. The other four retail versions rebuild too.
- **Half of the functions in C and C++.** They have recovered names, structures and classes rather than raw addresses.
  The [table](#progress) has the numbers per library.
- **A base for mods now.** The rebuild is *shiftable*: code can grow, shrink or move, and the linker fixes every reference
  ([docs/modding.md](docs/modding.md)).

**What "exact" means here.** A function counts only when it is compiled from source with the original compilers (SN
Systems GCC 2.95 and Sony's EE GCC) and the whole linked executable is still byte-identical. Functions kept as assembly,
including assembly written by hand, never count. The figures follow [objdiff](https://github.com/encounter/objdiff), the
measure [decomp.dev](https://decomp.dev) uses, and anyone with the game can reproduce them with `ninja progress`.

## Progress

<!-- progress:begin (tools/badges.py) -->

| Library | Functions matched | Share | Code matched (bytes) | Share |
| --- | ---: | ---: | ---: | ---: |
| game | 3,192 / 6,437 | 49.6 % | 197,180 / 1,453,676 | 13.6 % |
| kynapse | 1,321 / 1,557 | 84.8 % | 142,468 / 303,420 | 47.0 % |
| rw_core | 85 / 381 | 22.3 % | 4,584 / 179,516 | 2.6 % |
| rw_audio | 310 / 674 | 46.0 % | 22,824 / 106,632 | 21.4 % |
| animation | 236 / 377 | 62.6 % | 29,952 / 76,944 | 38.9 % |
| physics | 94 / 184 | 51.1 % | 11,944 / 77,680 | 15.4 % |
| apt | 223 / 705 | 31.6 % | 11,892 / 277,148 | 4.3 % |
| sony | 309 / 703 | 44.0 % | 13,800 / 140,092 | 9.9 % |
| libc | 75 / 209 | 35.9 % | 3,944 / 69,952 | 5.6 % |
| **Total** | **5,845 / 11,227** | **52.1 %** | **438,588 / 2,685,060** | **16.3 %** |

Functions as objdiff counts them: 5,845 of 11,227 (52.1 %); code: 438,588 of 2,685,060 bytes (16.33 %). Image measure (`ninja progress`): 5,845 of 11,899 function starts and 448,096 of 2,715,464 bytes (16.50 %), which includes the 672 orphan pieces and the alignment padding.

<!-- progress:end -->

Details of both measures: [docs/progress-reports.md](docs/progress-reports.md). What is hard and what is next:
[docs/status.md](docs/status.md).

## Get started

You need your own copy of the game (USA, `SLUS_213.76`) and Linux x86-64; on Windows use WSL 2, elsewhere Docker
([docs/setup.md](docs/setup.md)).

```sh
sudo apt install -y git ninja-build python3 python3-venv binutils-mipsel-linux-gnu libc6-i386 xz-utils
git clone https://github.com/dpusceddu/blackDecomp.git && cd blackDecomp
mkdir -p orig/SLUS_213.76 && cp /path/to/SLUS_213.76 orig/SLUS_213.76/
python3 -m venv .venv && . .venv/bin/activate && pip install -r requirements.txt
python3 tools/toolchain.py install --objdiff   # pinned compilers and tools, SHA-256 checked
python3 configure.py && ninja
```

A clean build takes about two minutes and ends with
`OK  SLUS_213.76  SLUS_213.76  sha256 141b0520...`.

## Contribute

There are thousands of functions left, from small helpers to the game's core systems.

- **By hand:** [CONTRIBUTING.md](CONTRIBUTING.md) has the workflow (objdiff, claiming a file, naming, commit rules).
- **With an AI agent:** point the agent at this repository and tell it to follow [AGENTS.md](AGENTS.md). Much of the work so
  far was done with AI coding agents under human direction; agents follow the same rules and evidence standard as
  everyone else.

Recovered types and names are as valuable as matches: a correct structure makes every function that uses it easier.

## Legal

This repository contains no game assets and no game code: no disc contents, executables, disassembly or compiler output.
You need your own copy of the game and extract the executable yourself. The build downloads the third-party compilers from
their public archives on your machine; they are not redistributed here. The game, its code and its assets belong to their
owners. The first recovered sources came from the author's earlier, unpublished project
([docs/history.md](docs/history.md#where-the-first-sources-came-from)).

## License

[CC0 1.0](LICENSE): the contributors' own work here (source, tools, documentation) is dedicated to the public domain.

## Acknowledgments

[splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm),
[rabbitizer](https://github.com/Decompollaborate/rabbitizer), [m2c](https://github.com/matt-kempster/m2c),
[decomp-permuter](https://github.com/simonlindholm/decomp-permuter), [objdiff](https://github.com/encounter/objdiff),
[wibo](https://github.com/decompals/wibo), the [decomp.me compilers](https://github.com/decompme/compilers) archives, and
the decompilation projects whose methods this one follows ([docs/matching-handbook.md](docs/matching-handbook.md)).
