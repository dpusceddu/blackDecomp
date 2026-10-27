# config/

Committed build inputs and evidence. The rule for the whole repository: **only real work is committed, everything derivable is
generated.** Files here are reviewed source inputs, edited manually or with scripts. `tools/autodecomp.py register` adds
matched entries to `splits.yaml` and `symbols.txt`. The production build does not write this directory. Derived outputs go
through `ninja` into ignored `build/` and are never committed (list at the end).

## Shared by all versions

| File | What it is |
| --- | --- |
| `versions.json` | The five supported releases: region, boot executable name, executable and disc image hashes |
| `tus_overrides.yaml` | Reviewed corrections that `tools/build/tus.py map` applies on top of its evidence when `ninja` generates the translation-unit map |
| `toolchain-compilers.json` | Pinned compiler archives (URLs, SHA-256) that `tools/toolchain.py` downloads |
| `toolchain-assemblers.json` | Pinned assembler hashes, including the patched `ps2eeas` |
| `toolchain-binutils.json` | Pinned Debian binutils packages for MIPS |
| `toolchain-local.json` | Pinned `wibo` release used to run the Windows tools |

## Per version, `config/<GAME_ID>/`

Every version has `checksums.sha256`. Only `SLUS_213.76` has recovered source, so only it has the rest.

| File | What it is |
| --- | --- |
| `checksums.sha256` | SHA-256 the rebuilt executable must have; never changes for a release |
| `splits.yaml` | The split list: which source file covers which address range, with flags (docs/units.md) |
| `symbols.txt` | Names: bound (mangled) names, names the code uses, and `alias` lines that never change linking |
| `libraries.txt` | Which library (a directory of `src/`) each stretch of `.text` belongs to, and where the link-once block is; progress, file placement and the TU map use it |
| `explicit_boundaries.txt` | Function starts that look like orphan pieces but are code, each with its reason; `tools/build/boundaries.py` adds them to the boundaries it derives |
| `class_method_abi.json` | Class information recovered from the binary: for 32 methods, the return type, parameters and accessed fields read from their instructions. Input of `tools/maint/class_skeletons.py`; the inferred types require reviewed evidence from the code |
| `rtti_abi.json` | Class information recovered from the binary: where the GCC 2.95 run-time type information helpers (`__rtti_class`, `__rtti_si`, ...) and their virtual tables are, and the layout of their records. Seeds `tools/maint/rtti_evidence.py`, which then derives every class, base link and vtable of the executable into `build/classes/` (ignored); the seeds themselves had to be identified by hand |

## What is generated instead (ignored, under `build/`)

| Generated file | Written by | Used by |
| --- | --- | --- |
| `build/<GAME_ID>/splat.yaml`, `layout.json`, `rom.bin` | `tools/build/splat_config.py`, `tools/build/elf_layout.py` (the `extract` stage) | splat, the linker script, the ELF packer |
| `build/<GAME_ID>/boundaries.txt` | `tools/build/boundaries.py`, from the executable and `explicit_boundaries.txt` | splat |
| `build/<GAME_ID>/functions.json`, `placement.json`, `labels.json` | `tools/build/split_objects.py` (separate function-table and placement stages) | object recipes, linker, diagnostics and progress |
| `build/SLUS_213.76/units.json` | `tools/build/units.py` | placement, object recipes and progress |
| `build/<GAME_ID>/objects.ninja`, `spec/`, `unit_objects.json` | `tools/build/object_graph.py` | individual Ninja compile/assemble edges, linker and objdiff |
| `build/<GAME_ID>/obj/`, `objects.json`, `link.ld` | per-object compiler/assembler rules and `tools/build/unit_link.py` | GNU ld, diagnostics and analysis |
| `build/SLUS_213.76/unit_facts.json` | `tools/build/unit_link.py` | TU map and progress |
| `build/<GAME_ID>/objdiff/`, `report.json` | `tools/objdiff.py` (`ninja objdiff`, `ninja report`) | objdiff GUI and progress agreement |
| `build/SLUS_213.76/tus.yaml` | `tools/build/tus.py map` (`ninja tus`; written on first use otherwise) | `tools/next.py`, `tools/progress.py`, new file names (`tools/build/layout.py`), `autodecomp.py --tu` |
| `build/SLUS_213.76/inline_owners.txt` | `tools/build/linkonce_owners.py` (`ninja owners`) | progress, badges, objdiff |
| `build/auto/` (context, `ctx.c`, recovered layouts) | `tools/autodecomp.py context`, `tools/decompile.py` | m2c drafts, class skeletons |
| `build/auto/inventory.json` | `tools/build/inventory.py` | TU map and progress |
| `build/classes/include/` | `tools/maint/class_skeletons.py` (explicit class-recovery command; see docs/pipeline.md) | reference when writing a class view |
| `build/SLUS_213.76/badges/` | `tools/badges.py` | nothing (the two committed files in `progress/` are what the README reads) |

The survey of the disc images (`tools/maint/inputs.py`) writes its dump to `build/survey/` and `.local/`.

The active build's `graph.json`, source-stage inventories (`prepare/*.json`) and per-edge I/O contracts (`io/*.json`) make
these dependencies explicit. Run `python3 tools/build/check_graph.py --ninja` to check them. Depfiles and Ninja's own state
are managed by Ninja; optional source-analysis experiments are separate from the normal build graph.
