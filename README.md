# Black (PS2) decompilation

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
| game | 3,310 / 6,437 | 51.4 % | 212,492 / 1,453,676 | 14.6 % |
| kynapse | 1,351 / 1,557 | 86.8 % | 146,764 / 303,420 | 48.4 % |
| rw_core | 85 / 381 | 22.3 % | 4,584 / 179,516 | 2.6 % |
| rw_audio | 310 / 674 | 46.0 % | 22,824 / 106,632 | 21.4 % |
| animation | 259 / 377 | 68.7 % | 33,900 / 76,944 | 44.1 % |
| physics | 95 / 184 | 51.6 % | 12,056 / 77,680 | 15.5 % |
| apt | 223 / 705 | 31.6 % | 11,892 / 277,148 | 4.3 % |
| sony | 309 / 703 | 44.0 % | 13,800 / 140,092 | 9.9 % |
| libc | 76 / 209 | 36.4 % | 4,084 / 69,952 | 5.8 % |
| **Total** | **6,018 / 11,227** | **53.6 %** | **462,396 / 2,685,060** | **17.2 %** |

Functions as objdiff counts them: 6,018 of 11,227 (53.6 %); code: 462,396 of 2,685,060 bytes (17.22 %). Image measure (`ninja progress`): 6,018 of 11,899 function starts and 472,280 of 2,715,464 bytes (17.39 %), which includes the 672 orphan pieces and the alignment padding.

<!-- progress:end -->

Details of both measures: [docs/progress-reports.md](docs/progress-reports.md). What is hard and what is next:
[docs/status.md](docs/status.md).

## Get started

You need your own copy of the game (USA, `SLUS_213.76`) and a Linux x86-64 shell. Native Linux with a Python virtual
environment is the default; a user or harness can also provide the shell through WSL or a container
([docs/setup.md](docs/setup.md)).

```sh
sudo apt install -y git ninja-build python3 python3-venv binutils-mipsel-linux-gnu libc6-i386 xz-utils
git clone https://github.com/dpusceddu/blackDecomp.git && cd blackDecomp
mkdir -p orig/SLUS_213.76 && cp /path/to/SLUS_213.76 orig/SLUS_213.76/
python3 tools/setup.py    # Python packages, pinned toolchain, assembly and objdiff metadata; no image build
```

Activate `.venv` if setup asks; subsequent commands use that environment. During matching, build individual units
through objdiff or their Ninja targets. Run the full-image `ninja` check once
before submitting the final changes for review; it must print `OK  SLUS_213.76`. `python3 tools/setup.py --build` is
available when an explicit full-image smoke check is wanted.

## Contribute

There are thousands of functions left, from small helpers to the game's core systems.

- **By hand:** [CONTRIBUTING.md](CONTRIBUTING.md) has the workflow (objdiff, claiming a file, naming, commit rules).
- **With an AI agent:** open your fork in a coding agent and say *"Follow AGENTS.md and do a work session."* The agent
  picks an unclaimed file with `tools/next.py`, claims it with a draft pull request, matches what it can and hands the
  pull request over for review. Much of the work so far was done with AI coding agents under human direction; agents
  follow the same rules and evidence standard as everyone else.

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
