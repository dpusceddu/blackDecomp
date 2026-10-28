# Black (PS2) decompilation

[![License: CC0-1.0](https://img.shields.io/badge/license-CC0--1.0-lightgrey.svg)](LICENSE)
![Code](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/dpusceddu/blackDecomp/main/progress/code.json)
![Functions](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/dpusceddu/blackDecomp/main/progress/functions.json)

A byte-matching decompilation of *Black* (Criterion Games, 2006): readable C and C++ that compiles back into the exact
bytes of the original PlayStation 2 executable.

Beyond preservation, we hope to make extensive changes to the game easier to develop and maintain, including projects
such as a virtual reality mod. Readable source verified against the original executable should provide a rigorous
foundation for that work, though the practical benefits remain to be demonstrated.

We target PS2 because its build compiles source files separately, without whole-game optimization. This makes byte
matching more tractable: optimizations across source files can make a function's machine code depend on code elsewhere
in the game.

## Contribute with an AI agent

An AI coding agent is the only supported contribution workflow. You provide:

- Your own USA PS2 copy of the game (`SLUS_213.76`), as an ISO or an extracted boot executable.
- A Linux **x86-64** shell with Git and Python 3, accessible to the agent. Windows users can use WSL 2; on other hosts,
  run the agent on a Linux x86-64 machine.
- GitHub CLI (`gh`) authenticated to GitHub, and Git access to push a branch to this repository or your fork and open
  pull requests here. Set your Git author name and email too.
- Permission for one-time dependency installation, and network access for tool downloads and GitHub.

Clone this repository, put your ISO in `orig/`, and open the checkout in your coding agent. Tell it:

> Read AGENTS.md and do a work session.

The agent handles setup, claims a file through a draft pull request, recovers and verifies code, and submits its work for
review. You do not need to choose functions, operate a compiler or learn the build system first. Review the changes and
the agent's verification report before handing the pull request over.

An extracted executable goes at `orig/SLUS_213.76/SLUS_213.76`. If the ISO lives elsewhere, tell the agent its path; setup
accepts `--iso PATH`.

## How it works

The project already rebuilds the complete executable byte for byte. Functions not yet recovered are assembled from your
copy of the game; recovered C and C++ gradually replace them in the same build.

For each claimed file, the agent reads the assembly and its callers, reconstructs types and behavior, and compiles a
candidate with the original toolchain. [objdiff](https://github.com/encounter/objdiff) compares its instructions and
relocations with the original. Small object builds make iteration quick; a complete byte-identical rebuild verifies the
final source changes, including linking and data placement. Unfinished attempts remain drafts, and existing matches
must be preserved.

This is the established matching-decompilation workflow used by projects such as
[Super Mario 64](https://github.com/n64decomp/sm64), developed long before AI coding agents. Our agents carry out the
investigation and iteration; the compiler and binary comparisons supply the checks. Matching bytes do not uniquely
recover the original source text or names, so readable code and evidence for names and types remain part of review.

We build on [splat](https://github.com/ethteck/splat),
[spimdisasm](https://github.com/Decompollaborate/spimdisasm),
[rabbitizer](https://github.com/Decompollaborate/rabbitizer), [m2c](https://github.com/matt-kempster/m2c),
[decomp-permuter](https://github.com/simonlindholm/decomp-permuter), objdiff,
[wibo](https://github.com/decompals/wibo), and the [decomp.me compiler archives](https://github.com/decompme/compilers).

## Legal and license

No leaked source code has been used in this project. The reconstructed game source comes from decompilation and reverse
engineering of game binaries, including the author's earlier Xbox reconstruction work.

You must supply your own copy of the game. Original executables, disc contents, assets, generated disassembly and compiler
output are excluded from this repository. The build downloads third-party compilers to your machine; they are not
redistributed here. *Black* and its original assets belong to their respective owners.

The contributors' work here (reconstructed source, tools and documentation) is dedicated to the public domain under
[CC0 1.0](LICENSE). This dedication does not grant rights to the original game or third-party tools.
