# Setup in detail

The short version is in the [README](../README.md#get-started). This page has the details: versions, platforms, Docker
and binutils.

## Versions

Each version is identified by the game ID of its boot executable (`SYSTEM.CNF`, `BOOT2`).

| Game ID | Region | SHA-256 of the executable | Rebuild matches | Recovered source |
| --- | --- | --- | --- | --- |
| `SLUS_213.76` | USA | `141b05209570458af9c8e27ab1911f258da6353909d813cd572df026254ffe4c` | yes | see the [README](../README.md#progress) |
| `SLES_538.86` | Europe | `bbed3444a22d28b7fdc641e15a1759b6ece1c9cbc5a13331586025ff8fc2b948` | yes, from assembly | none yet |
| `SLES_540.30` | Europe, Australia | `7e6f25966389656a9bdc534c2514a3a56f205054ee66b43c27a18b111add309f` | yes, from assembly | none yet |
| `SLKA_253.72` | Korea | `fb59440b00444ff64be1436fd757452c3eead9e560532fad74e4d05e913a6b94` | yes, from assembly | none yet |
| `SLPM_663.54` | Japan | `bf70d92152237eae6908e973d44dde8ce49d9e7e32b34e9b7ad41f79ad569f43` | yes, from assembly | none yet |

"Rebuild matches" means `ninja` reproduces the executable byte for byte. `SLUS_213.76` is the only version with recovered
source and the only one that routine work builds, measures and checks. The other four are rebuilt from their own assembly
and are checked before releases (`python3 tools/check_versions.py` configures and builds all five and prints `OK` or
`MISMATCH` for each); their configurations stay committed. Source units are written for the USA version.

## Linux, Windows, macOS and Docker

You need the boot executable of your own copy (see [Versions](#versions)) as `orig/<GAME_ID>/<GAME_ID>`, for example
`orig/SLUS_213.76/SLUS_213.76`, and a Linux x86-64 environment: the compilers are a Windows program (run through
[wibo](https://github.com/decompals/wibo)) and 32-bit Linux programs.

**Linux (Debian 12 or Ubuntu 22.04 and later)**

```sh
sudo apt update && sudo apt install -y git ninja-build python3 python3-venv python3-pip binutils-mipsel-linux-gnu libc6-i386 xz-utils ca-certificates
git clone https://github.com/dpusceddu/blackDecomp.git
cd blackDecomp
mkdir -p orig/SLUS_213.76 && cp /path/to/SLUS_213.76 orig/SLUS_213.76/
python3 -m venv .venv && .venv/bin/pip install -r requirements.txt
. .venv/bin/activate                      # from here on `python3` is the virtual environment's; every command in the documentation assumes it
python3 tools/toolchain.py install --objdiff # pinned compilers, assemblers and wibo into build/toolchain (SHA-256 checked)
python3 configure.py                      # default --version SLUS_213.76
ninja
```

In a container or as root there is no `sudo`: drop it from the first line. Build timings and the object architecture are in [build.md](build.md). It ends with

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
# inside (the virtual environment is already on PATH): python3 configure.py && ninja
```

`docker build` downloads the pinned compilers, assemblers and wibo from their public archives (SHA-256 checked), so it needs
network access; the image contains no game files.

With Podman, or on a host with SELinux (Fedora, RHEL), mount with `-v "$PWD":/workspace:Z`, or the container cannot read the checkout.
On Apple silicon this relies on the emulation of x86-64 Linux containers and has not been tested.

**Binutils.** `ld` and `objcopy` for little-endian MIPS come from the distribution package `binutils-mipsel-linux-gnu`
(Debian, Ubuntu; version 2.40 is the tested one). On a distribution without it, use Docker, or build GNU binutils 2.40 with
`--target=mipsel-linux-gnu` and put the tools on `PATH` (or set `BLACK_BINUTILS_PREFIX`). The decompals
`binutils-mips-ps2-decompals` prebuilt cannot link this executable: its `ld` has no little-endian MIPS emulation.

## Repository layout

```
configure.py          writes build.ninja (and picks the version)
config/<GAME_ID>/     per-version expected SHA-256; SLUS_213.76 also has splits.yaml (source files, address ranges, flags), symbols.txt
                      (names), libraries.txt (which library each stretch of .text is), explicit boundaries; the splat
                      configuration, ELF layout, TU map and the like are generated into build/ (config/README.md)
config/               versions.json, tus_overrides.yaml, toolchain pins, shared data
orig/<GAME_ID>/       your executable goes here (ignored by Git)
src/<library>/        (src/game/ has subsystem directories) one file per translation unit: recovered functions as C/C++, the rest as INCLUDE_ASM lines, drafts in
                      #ifdef NON_MATCHING blocks (game, kynapse, animation, physics, rw_core, rw_audio, apt, sony, libc);
                      compiler-emitted inline and template copies are in src/<library>/inline/ (docs/build.md#link-once-copies)
include/<library>/    headers per library, include/ps2/ for helpers shared by all
tools/                the everyday tools (decompile, where, split_function, objdiff, progress, toolchain, ...); tools/build/ (internals `ninja` runs),
                      tools/pipeline/ (automatic pipeline), tools/maint/ (maintainer and analysis)
progress/             the two badge files the README reads, written by `ninja badges` (the maintainer commits them)
docs/                 build, translation unit files and split list, pipeline, TU map, matching handbook, status, history
tests/                tests that need no game files
asm/ build/ data/     generated (asm/<GAME_ID>/nonmatchings/ holds the assembly of every function), ignored
```
