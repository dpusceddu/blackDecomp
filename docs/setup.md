# Setup reference

The supported contribution workflow is in the [README](../README.md#contribute-with-an-ai-agent).
[AGENTS.md](../AGENTS.md) owns the session procedure; this page covers environment preparation and troubleshooting.

## Native Linux, prepared once

Use Linux x86-64 with Git and Python 3. Windows users can use WSL 2; other hosts need a Linux x86-64 machine accessible
to the agent. The pinned compilers include Windows programs run through [wibo](https://github.com/decompals/wibo) and
32-bit Linux programs. A macOS venv does not provide that runtime.

With permission to install dependencies, the user or harness runs:

```sh
python3 tools/setup.py --provision
```

Provisioning installs system packages through apt-get on Debian/Ubuntu or dnf on Fedora (sudo when needed), prepares
`.venv` or the active Python environment, installs the pinned toolchain and objdiff-cli, and checks that the native
MIPS linker supports `elf32ltsmip`. It needs no game files or GitHub login and builds no image. Re-run it when system
prerequisites or pinned requirements change.

Other distributions must provide Ninja, Git, GitHub CLI (`gh`), xz, cpp, Python with venv/pip support, the 32-bit Linux
loader, and GNU MIPS binutils. Setup recognizes `mipsel-linux-gnu-` (Debian/Ubuntu) and `mips64-linux-gnu-` (Fedora);
`BLACK_BINUTILS_PREFIX` selects another compatible installation.

GNU binutils 2.40 is the tested linker. Other versions must still pass the final byte-identical image check. A separate
2.40 installation can use `--target=mipsel-linux-gnu` and PATH or `BLACK_BINUTILS_PREFIX`. The decompals
`binutils-mips-ps2-decompals` prebuilt lacks the required little-endian linker emulation.

The Dockerfile and `tools/container.py` are deployment references for harnesses explicitly supplied that way. Ordinary
sessions use their provided Linux shell and do not manage containers.

## Game input

Put one USA retail ISO in `orig/`, or pass its path:

```sh
python3 tools/setup.py --iso /path/to/your/game.iso
```

Setup reads `SYSTEM.CNF`, identifies the boot executable, checks that it is USA retail (`SLUS_213.76`), and verifies its
SHA-256 against `config/versions.json` before saving `orig/SLUS_213.76/SLUS_213.76`. It extracts no assets, preserves the
ISO, and refuses to overwrite an existing different executable. With multiple ISOs in `orig/`, pass `--iso` explicitly.
Only uncompressed ISO images are auto-detected; unpack compressed archives first.

An already extracted boot executable at that path works too and is verified on each setup. A valid existing executable
takes precedence over auto-detected ISOs. Game inputs and generated files remain ignored by Git. See [game input](inputs.md) for the expected executable metadata.

## GitHub access

Authenticate `gh` for github.com and configure a Git author name and email. `python3 tools/github.py` checks Git identity,
GitHub authentication and read access to `dpusceddu/blackDecomp`. Normal setup runs these checks before preparing metadata.
They do not establish push permission: the agent must successfully push its branch and open its draft claim before editing.

The picker always reads claims from `dpusceddu/blackDecomp`, including in forks. A deliberate `--repo OWNER/NAME` override
is available for separate projects. Pull requests for this project must explicitly target the main repository, as described
in [claiming a file](../CONTRIBUTING.md#claiming-a-file). If claims cannot be read, selection stops.

## Session preparation

Normal `python3 tools/setup.py` reuses the environment, checks contribution access and game input, and prepares assembly,
the TU map and `objdiff.json` without compiling all objects or linking. It never invokes a system package manager.
Activate the selected venv before further commands, including in each fresh shell; the checkout default is
`. .venv/bin/activate`. An already active environment takes priority.

Linked worktrees can share `.venv`, the pinned toolchain and extracted game inputs with the main checkout; generated
outputs remain local. Metadata preparation is serialized across linked worktrees. Ordinary matching builds and other
repositories remain independent. A forcibly killed setup process can leave children running after its lock is released.

`--build` additionally builds and verifies the full image.
The final image check prints `OK` and its SHA-256. Missing prerequisites report the provisioning command; missing GitHub
access or unsuitable game input gives an actionable error. Follow the [validation impact rule](../CONTRIBUTING.md#rules)
for subsequent work.
