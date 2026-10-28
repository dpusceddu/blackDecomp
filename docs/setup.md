# Setup in detail

The short version is in the [README](../README.md#get-started). This page covers versions, one-time native provisioning,
session preparation and binutils.

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

## Native Linux, prepared once

Run decompilation sessions on Linux x86-64 with a Python virtual environment and the pinned toolchain. The compilers are
Windows programs run through [wibo](https://github.com/decompals/wibo) and 32-bit Linux programs; a Python venv on macOS
cannot supply that Linux runtime.

### One-time provisioning (user or harness)

With Python 3 and Git available, clone the repository on the Linux machine and run:

```sh
python3 tools/setup.py --provision
```

This explicit provisioning mode installs system packages using apt-get on Debian/Ubuntu or dnf on Fedora (sudo when
needed), prepares `.venv` or the active Python environment, installs the pinned compiler/assembler tools and objdiff-cli,
and verifies that the native MIPS linker supports `elf32ltsmip`. It does not need game files, prepare session metadata or
build an image. Provide Git/GitHub access for later sessions.
Re-run provisioning when the system prerequisites or pinned Python requirements change.

System prerequisites are Ninja, Git, xz, cpp, Python with venv/pip support, the 32-bit Linux loader, and GNU MIPS binutils
with little-endian linking support. Other Linux distributions can install those prerequisites manually. Debian/Ubuntu's
package is `binutils-mipsel-linux-gnu`; Fedora's is `binutils-mips64-linux-gnu`. Setup and the toolchain recognize both
prefixes automatically. `BLACK_BINUTILS_PREFIX` can select an explicitly provisioned compatible toolchain.

GNU binutils 2.40 is the tested linker version. A distribution package with another version still has to pass the final
byte-identical image check. To install that version separately, build GNU binutils 2.40 with `--target=mipsel-linux-gnu`
and put its tools on PATH (or set `BLACK_BINUTILS_PREFIX`). The decompals `binutils-mips-ps2-decompals` prebuilt cannot link
this executable: its linker has no little-endian MIPS emulation.

### Normal agent sessions

Start the agent on the prepared Linux host, with its command and file tools using the same workspace. Add the boot
executable of your own copy as `orig/SLUS_213.76/SLUS_213.76`, then run:

```sh
python3 tools/setup.py
. .venv/bin/activate
python3 tools/next.py --pick
```

Activate the venv before further project commands, repeating activation in each fresh shell. Setup creates or links
the worktree's `.venv`; creating a worktree does not activate it automatically.

Normal setup never invokes a system package manager or a container runtime. It creates `.local/` for session notes,
reuses installed dependencies and prepares assembly, the TU map and `objdiff.json` without compiling all objects or linking
an image. Existing local worktrees can share `.venv`, the pinned toolchain and game inputs with the main checkout;
generated build outputs stay local to each checkout. Missing system prerequisites produce the one-time provisioning
instruction for the user or harness.

Setup serializes metadata preparation across linked worktrees of the same Git repository; a cold or refreshed
recovery context uses the same lock, while a valid cached context does not wait. Other repositories and ordinary
matching builds remain independent. The lock coordinates these tools only, and does not limit manually launched
preparation commands. If a setup process is forcibly killed, its child processes may continue after its lock is released.

Follow the [validation impact rule](../CONTRIBUTING.md#rules) during matching. `--build` is available for an explicit setup
smoke check; `--no-build` remains a compatibility alias for normal preparation. A successful image check prints:

```
OK  SLUS_213.76  SLUS_213.76  sha256 141b05209570458af9c8e27ab1911f258da6353909d813cd572df026254ffe4c
```

A mismatch report identifies what needs fixing. Select other retail versions with `python3 configure.py --version GAME_ID`;
`python3 tools/check_versions.py` checks all five.

### Other host environments

Windows users can prepare a Linux x86-64 environment in WSL 2. On other hosts, provision a native Linux machine and run
the agent there. Do not select or create a container merely because a prepared image is available.

The Dockerfile and `tools/container.py` remain optional deployment references for a harness that explicitly supplies its
execution environment that way. They are outside the selected native workflow; ordinary agents do not manage container
lifetimes, mounts, user mappings or exec prefixes.

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
