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

## Build (Phase 1: the identical rebuild)

Needs the target executable in `orig/<variant>/files/` (see `tools/discs.py`), the build backend, and `ninja`.

```sh
python3 configure.py --variant usa-retail     # writes build.ninja (variants: usa-retail, eu-au-retail, eu-retail, kr-retail, jp-retail)
ninja                                          # about 20 s; ends with `OK  SLUS_213.76 ...` or a mismatch report
```

Stages (one `ninja` rule each; everything generated is under the ignored `asm/`, `data/`, `build/`):

1. extract: `tools/splat_config.py` writes `config/<boot>.yaml` (splat segments from the ELF section table) and the
   headerless image splat reads; `tools/elf_layout.py` writes `config/<boot>.layout.json` (ELF header, program
   header and one record per section) and extracts the opaque non-loaded payloads (DVP overlays) to `data/`.
2. split: `splat split` (spimdisasm, rabbitizer) writes `asm/<variant>/text.s` (all functions, one file) and one data
   file per section; `.vutext` and `.vudata` stay binary blobs.
3. `tools/link_support.py` defines the symbols splat cannot: code addresses inside functions (labels), offsets into
   data objects, section ends and plain constants.
4. `tools/fixasm.py` applies the Phase 0 reassembly rules to the code (short backward branches as `.word`, bare VU0
   registers), inserts the extra labels, and cuts the code into chunks (the assembler is quadratic in file size).
5. `tools/make_ld.py` writes the linker script: every loaded section placed by alignment only, so sizes can change.
6. `tools/build_objects.py` runs, in the build backend, the EE assembler 2.10 on each chunk and data file and
   mainline GNU `ld` (`binutils-mipsel-linux-gnu`) on the objects.
7. `tools/pack_elf.py` re-packs ld's loaded sections into the retail container (see below);
   `tools/check_elf.py` compares the result with `config/checksums.sha256`.

ld cannot write the retail container: section-header order, the non-loaded `.reginfo`, `.DVP.*` and `.debug_str`
sections, and `e_flags` 0x20924001. `pack_elf.py` therefore takes the linked section contents and addresses from ld and
writes the headers from `config/<boot>.layout.json`, regenerating `.shstrtab` and `.reginfo` (with the linked `_gp`)
and rebasing the `.DVP.ovlytab` addresses that point into `.vutext`. The overlays and `.vutext`/`.vudata` are extracted
payloads, not rebuilt. Code and data come only from the reassembled sources.

Other tools: `tools/diffelf.py REF BUILT` (section-by-section diff), `tools/shift_test.py` (shiftability test),
`tests/link/check.py` (SN object + GNU object linked by the build backend's ld).
In a sandbox script, `mipsel-linux-gnu-{ld,objcopy,readelf,objdump,nm}` are on PATH.

### Shiftability

`python3 tools/shift_test.py usa-retail --nops 200` copies the split assembly to a scratch name, inserts NOPs into one
function, rebuilds and checks every symbolic reference against a symbol-derived address map. Result for 200 NOPs
(everything from `.text` onward moves): all 19,781 `jal`/`j`, 19,121 `%hi`, 25,118 `%lo`, 2,997 gp-relative accesses,
8,499 + 4,321 + 5 data pointers and 903 exception-table entries moved correctly, 0 inconsistencies. Known non-shiftable
spots: 984 raw `.word` values in `.data`, `.rodata` and `.sdata` that fall inside the image address range but are not
symbols in the split (almost all are numbers such as colours, hashes and flags; at least 33 words around `.data` 0x3C3DC0
point into the `.vutext` blob and would need symbols), and any address built by arithmetic that is not a `%hi/%lo` pair.
One NOP only moves the code behind it by 8 bytes (function alignment) and the alignment slack before `.vutext` hides it
from the data sections.

## Layout

```
PLAN.md       phases and rules          config/variants.json   hashes and ELF metadata of all variants
AGENTS.md     agent rules               config/<boot>.yaml     splat configuration, one per boot executable
configure.py  writes build.ninja        config/<boot>.layout.json   ELF container description for tools/pack_elf.py
include/      macro.inc (asm labels)    docs/inputs.md         Phase 0 findings and target proposal
tools/        Phase 0 and build tools   tests/                 toolchain and linker probes
orig/ asm/ data/ build/ .local/         ignored: inputs, generated assembly and data, build output, scratch
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
