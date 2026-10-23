# Black (PS2) decompilation

Readable C/C++ source for the retail PS2 executable of Black, with explicit per-function evidence: byte-exact (`exact`),
behaviorally equivalent on tested states (`equivalent`) or untested (`draft`). `ninja` rebuilds the executable byte for
byte with the recovered source in place of its assembly. Current numbers, method and open problems are in
[PLAN.md](PLAN.md); the results history is in [docs/history.md](docs/history.md).

Game bytes, disc contents, compilers and build output are never committed; they live in ignored directories
(`orig/`, `asm/`, `data/`, `build/`, `.local/`, `.venv/`).

## Setup

```sh
python3 -m venv .venv && .venv/bin/pip install -r requirements.txt     # rabbitizer, splat64, spimdisasm, m2c, PyYAML ...
```

Private inputs (not in the repository):

- `orig/<variant>/files/<boot executable>`: the retail executables (variants `usa-retail`, `eu-retail`, `eu-au-retail`,
  `kr-retail`, `jp-retail`; hashes in `config/variants.json`). `tools/discs.py --images DIR` extracts them from disc image
  zips one image at a time (see `docs/inputs.md`).
- `.local/config.json`: machine-specific settings (ignored by Git).
  SDK compilers, assemblers and binutils run only through the build backend, never on the host
  (`tools/compile.py`, `tools/sandbox.py`). If the build backend reports a failure, restore it instead of
  working around the isolation.

Optional inputs, needed only by the tools that refresh committed metadata (the build never needs them):

| Input | Used by | Refreshes |
| --- | --- | --- |
| `.local/ghidra/*.json` raw pages of three Ghidra MCP calls (listed in the docstring of `tools/ghidra_export.py`) | `ghidra_export.py`, `ghidra_types.py`, `autodecomp.py context --refresh` | `config/symbols.txt`, `include/types_ghidra.h` |
| An Xbox-to-PS2 counterpart map (json) | `progress.py --refresh MAP.json` | `config/regions.txt` |
| `orig/savestates/*.p2s`, PCSX2 states | `tools/eeharness/phase2.py` | recorded entry states (ignored `build/`) |
| The companion project checkout (`--parent DIR`) | `tools/studies/import_*.py` | one-time source imports, already committed |

## Build

```sh
python3 configure.py --variant usa-retail     # writes build.ninja (usa-retail, eu-retail, eu-au-retail, kr-retail, jp-retail)
ninja                                          # ends with `OK  SLUS_213.76 ...` or a mismatch report
ninja progress                                 # share of .text provided by source (python3 tools/progress.py --libraries: per library)
```

A build from nothing takes about 90 s on a two-core machine (split, 9,600 objects, link, pack); with a warm cache and one
changed unit about 15 s. Source units apply to USA retail; the other four images rebuild from assembly and must stay
identical too. Stages, constants migration, function boundaries and shiftability: [docs/build.md](docs/build.md).

## Source layout

```
src/<library>/<name>.c|cpp     game apt kynapse animation physics rw_core rw_audio sony libc linkonce
src/<library>/nonmatching/     drafts that no unit uses
include/                       headers (library directories, ps2/ shared helpers, classes/ and recovered/ generated)
config/units.yaml              every source unit: library, provenance, tier, flags, functions and their status
config/tus.yaml                the TU map (boundaries, libraries, compiler and flags per TU)
tools/                         build, pipeline and harness tools; tools/studies/ one-off studies and importers
docs/                          build.md units.md pipeline.md tus.md history.md inputs.md
tests/                         tool tests (python -m unittest discover -s tests; -s tests/tools) and linker probes
```

Files are named after the TU (`tu_<address>`, plus `_<unit address>` when a unit does not start its TU) or the class or
module they implement. `tools/relayout.py` applies the rules of `tools/layout.py` and can be re-run after other tools add files.

## Working on a TU

1. Pick work with `python3 tools/next.py [tus|near|types|families|data|ee]`; `python3 tools/progress.py --tus 15` lists the
   partly done TUs closest to completion.
2. Claim the TU: add or edit its units in `config/units.yaml` (`owner`, `claim`) before touching its sources, and edit only
   those sources unless you are the coordinator. Shared headers belong to their owners.
3. Draft with `python3 tools/autodecomp.py run ...` (m2c, flag variants, scoring, permuter; [docs/pipeline.md](docs/pipeline.md)),
   or write the source by hand and try it for one function with `python3 tools/trysrc.py ADDR file.c`.
4. Register what is exact: `python3 tools/autodecomp.py register` then `settle`, or `python3 tools/settle_units.py` for
   hand-written units. Units, symbols, statuses and reasons: [docs/units.md](docs/units.md). Anything that does not link
   identically is demoted; the build must print `OK` before every commit.
5. Leave a one-line `// Unmatched:` note on every function that stays inexact. Keep `src/` free of per-function journals.
6. Run `ninja`, `ninja progress` and the tests; commit without attribution lines; do not push.

Planned: `docs/matching-handbook.md`, the working handbook for matching (method, typical mismatch causes, helper headers).

## Tools

Core build (`configure.py` drives them through Ninja): `splat_config.py`, `elf_layout.py`, `boundaries.py`,
`link_support.py`, `split_objects.py`, `make_ld.py`, `build_objects.py`, `pack_elf.py`, `check_elf.py`, `units.py`,
`units_verify.py`, `settle_units.py`. Backend access: `compile.py`, `sandbox.py`, `build_job.py`, `assembler.py`.
Pipeline: `autodecomp.py`, `context_recovery.py`, `class_skeletons.py`, `rtti_evidence.py`, `shared_context.py`, `m2c_*.py`,
`ee_prep.py`, `tus.py`, `regroup.py`, `merge_units.py`, `next.py`, `progress.py`, `relayout.py`. Inputs and symbols:
`discs.py`, `inputs.py`, `symbols.py`, `ghidra_export.py`, `ghidra_types.py`. Every tool has a purpose docstring and `--help`.
`tools/studies/` keeps finished experiments (short-loop padding, VU0 shape census, large-function calibration, shiftability,
importers) that are not part of the build.

## Equivalence harness

`tools/eeharness/` is an independent host-side EE emulator (integer/MMI, COP0, COP1, VU0 macro/micro) with recorded
hardware stubs, savestate loading, entry-state capture and typed fuzzing. `tools/equiv.py` runs compiled candidate source
against recorded inputs from the original code, measures original instruction and branch coverage and writes the result as
function `evidence:` in `units.yaml` (`tier: equivalent` means agreement on tested states, not a proof). Equivalent source
never replaces assembly in the matching build. Details, checks and limits: [tools/eeharness/README.md](tools/eeharness/README.md).
Private captures stay under ignored `build/eeharness/`.

## Rules

`AGENTS.md` has the short agent rules. In particular: never run SDK binaries on the host; never commit game bytes,
generated assembly or data, savestates, build output or machine-specific details (host names, user names, absolute paths,
addresses); every commit leaves `ninja` printing `OK` for USA retail and keeps `ninja progress` from regressing.
