# Black (PS2) matching decompilation

Goal: a source tree that rebuilds the retail PS2 executable byte for byte, organised into the original
translation units. See `PLAN.md` for the phases and `docs/inputs.md` for the Phase 0 findings.

Game bytes, disc contents, compilers and build output are never committed; they live in ignored
directories (`orig/`, `asm/`, `data/`, `build/`, `.local/`).

## Setup

```sh
python3 -m venv .venv && .venv/bin/pip install -r requirements.txt   # rabbitizer, splat64, spimdisasm
```

Machine-specific configuration goes in `.local/config.json`, which is ignored. SDK compilers and assemblers run only
through the build backend, never directly on the host.

## Layout

```
PLAN.md       phases and rules          config/variants.json   hashes and ELF metadata of all variants
AGENTS.md     agent rules               docs/inputs.md         Phase 0 findings and target proposal
tools/        Phase 0 tools             tests/toolchain/       trivial probe sources for the compilers
orig/ .local/ build/                    ignored: inputs, raw dumps, scratch, outputs
```

## Phase 0 tools

Put the disc zips in a directory (default `../ps2images`), then:

```sh
.venv/bin/python tools/discs.py            # one image at a time: keep executables, SYSTEM.CNF, listings in orig/<slug>/
.venv/bin/python tools/inputs.py           # triage and retail comparison -> config/variants.json, .local/inputs/
.venv/bin/python tools/symbols.py          # symbol/debug dump and transfer estimate -> .local/inputs/symbols/
.venv/bin/python tools/compile.py ee-gcc2.95.3-136 -O2 -G0 -snas -c tests/toolchain/trivial.c -o build/probe/t.o
.venv/bin/python tools/asmcheck.py gen && .venv/bin/python tools/asmcheck.py run   # EE assembler round trip in the sandbox
.venv/bin/python tools/sandbox.py SCRIPT.py   # run a Python script inside the build backend
```

`discs.py` refuses to extract when fewer than 12 GB of disk would remain and deletes each image after use.
