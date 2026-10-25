# Tools

Every tool answers `--help`. One-line purposes are taken from each tool's docstring; this file is written by
`python3 tools/tools_index.py`.

A contributor needs the first two sections, which are the files directly in `tools/` (and `tools/permuter/`). `ninja` runs the
build internals itself, the automatic pipeline is reached through `tools/autodecomp.py`, and the maintainer tools regenerate
committed data. Tools import each other by bare module name; every tool puts `tools/` and its subdirectories on `sys.path`.

## Everyday tools: working on a function

| Tool | Purpose |
| --- | --- |
| `tools/decompile.py` | Friendly front door for one function: an m2c draft, ready to replace its INCLUDE_ASM line, and where to put it. |
| `tools/objdiff.py` | Per-unit objects and the project file for objdiff, and the progress report that decomp.dev reads. |
| `tools/trysrc.py` | Compile a hand-written or templated C source for one function and score it against the original. |
| `tools/next.py` | Best next work, from the automatic pipeline's results (build/auto.json) and the source units (tools/build/units.py). |
| `tools/autodecomp.py` | Automatic decompilation pilot: m2c -> clean -> compile variants -> score -> permuter -> register as source units. |
| `tools/where.py` | Name the source file that owns a function, and the line where it is: assembly, draft or source. |
| `tools/relocate_sources.py` | Move source files and keep every reference to them consistent: the build inputs, documentation and generated comments. |
| `tools/permuter/prepare.py` | Write the assembly of one function in the plain form decomp-permuter's import.py reads. |
| `tools/permuter/cc.py` | Compile script for decomp-permuter: run the pinned SN compiler on one self-contained source file. |
| `tools/permuter/as.py` | Assemble the target of decomp-permuter with the EE assembler of the pinned toolchain. |

## Everyday tools: build, check and progress

| Tool | Purpose |
| --- | --- |
| `tools/toolchain.py` | Local build toolchain: download, verify and unpack the pinned compilers, assemblers and wibo. |
| `tools/compile.py` | Run one of the pinned EE compilers on a standalone source file. |
| `tools/check_versions.py` | Rebuild every supported version and print OK or MISMATCH for each; run before a release or after changes to shared build tools. |
| `tools/check_elf.py` | Compare a rebuilt executable with the target hash in config/<GAME_ID>/checksums.sha256. Build check, run by `ninja`. |
| `tools/diffelf.py` | Compare two ELF files section by section (a debugging aid for the identical rebuild). Convenience script; binutils `readelf` and `objdump` work too. |
| `tools/objdump.py` | Print the sections, symbols and relocations of a relocatable ELF object (reads the file only). Convenience script; binutils `mipsel-linux-gnu-objdump` and `readelf` work too. |
| `tools/progress.py` | Report how much of .text is provided by source (tools/build/units.py: functions the TU files do not mark INCLUDE_ASM), overall and by library. |
| `tools/badges.py` | Write the self-hosted progress badges (progress/) and the per-library table of the README from the exact progress data. |
| `tools/tools_index.py` | Regenerate docs/tools.md, the index of the tools, from the docstring of every tool. |

## Build internals (`tools/build/`)

| Tool | Purpose |
| --- | --- |
| `tools/build/backend.py` | Where the toolchain jobs run: the built-in local backend (default) or an optional plugin module. |
| `tools/build/sandbox.py` | Run a build job script with the compilers, assembler and binutils of the selected backend. |
| `tools/build/build_objects.py` | Assemble and compile what changed, then link, in one call to the build toolchain . |
| `tools/build/build_job.py` | Job runner: assemble, compile, link and pack with the toolchain of the selected backend (sent by build_objects.py). |
| `tools/build/split_objects.py` | Cut splat's output into one assembly file (and later one object) per function, migrating constants with them. |
| `tools/build/splat_config.py` | Generate the splat64 configuration for a retail boot executable from its ELF section table. |
| `tools/build/make_ld.py` | Write the GNU ld script and the object list for the rebuild. |
| `tools/build/link_support.py` | Make splat's output linkable: define the symbols splat could not, so that every reference goes through a symbol. |
| `tools/build/pack_elf.py` | Write the final boot executable: GNU ld's linked sections inside the container the retail tools produced. |
| `tools/build/elf_layout.py` | Describe the container of a retail boot ELF (headers and non-loaded sections) for tools/build/pack_elf.py. |
| `tools/build/elfinfo.py` | Small ELF32 reader (little-endian, any machine) used by the Phase 0 tools. |
| `tools/build/elfobj.py` | Fix-ups for relocatable objects written by the SN assembler (-snas) so that mainline GNU ld accepts them. |
| `tools/build/include_asm.py` | Read and edit the INCLUDE_ASM markers of a translation unit source file. |
| `tools/build/splits.py` | Readers and writers for the committed, human-edited build inputs of one version (config/<GAME_ID>/). |
| `tools/build/units.py` | The source units of the build (python3 tools/build/units.py [GAME_ID] derives and caches them), derived from the split list, the source files and the symbol table. |
| `tools/build/units_verify.py` | Check the compiled source units against the original image; report what cannot be placed identically. |
| `tools/build/layout.py` | Source layout rules: which library directory and which file name a source unit gets (src/<library>/<name>.c\|cpp). |
| `tools/build/nm_build.py` | Build the NON_MATCHING drafts into a separate executable (`python3 configure.py --non-matching`, then `ninja`). |
| `tools/build/text_placement.py` | Recognize natural linker alignment after source sections, without inventing bytes. |
| `tools/build/constant_relocs.py` | Resolve words in compiler-owned constants for matching, including switch targets. |
| `tools/build/source_data.py` | Validate opt-in source-owned data ranges at labels or complete unwind groups. |
| `tools/build/ownership.py` | Which source file owns a function, and where in the file it is: the answer of `python3 tools/where.py`. |
| `tools/build/assembler.py` | Explicit compiler -S / catalog assembler configurations. |
| `tools/build/patch_ps2eeas.py` | Reproduce retail's six-word short loops with SN Ps2EeAs 1.9.25.758. |
| `tools/build/fixasm.py` | Line-level rules that let the EE GNU assembler 2.10 reproduce the original words (used by split_objects.py). |
| `tools/build/objdiff_job.py` | Job for tools/objdiff.py (runs through tools/build/sandbox.py): build the target and base objects objdiff compares. |
| `tools/build/build_telemetry.py` | Append small worker-call records under ignored build directories. |
| `tools/build/tus.py` | Translation-unit (TU) boundary evidence and the TU map of the boot executable. |
| `tools/build/linkonce_owners.py` | Decide which library owns each link-once copy (compiler-emitted inline and template code) and write the owner list. |
| `tools/build/boundaries.py` | Function boundaries splat cannot see: write build/<GAME_ID>/boundaries.txt (splat's symbol_addrs format), derived from the image. |

## Automatic pipeline (`tools/pipeline/`)

| Tool | Purpose |
| --- | --- |
| `tools/pipeline/tu_files.py` | Edit the translation unit files and the split list: the "register a match" step of the automatic pipeline. |
| `tools/pipeline/m2c_input.py` | Present split sections and assembler-escaped instructions to m2c. |
| `tools/pipeline/m2c_wrap.py` | m2c with one formatting change for the pipeline: a dereference at offset 0 of an expression that m2c has not typed as a pointer (an integer holding an address, say `lw $v0, 0($a0)` with $a0 an untyped argument) is written as `M2C_FIELD(expr, T *, 0)` instead of `*expr`, which is not valid C. |
| `tools/pipeline/ee_prep.py` | EE instructions that m2c cannot read, rewritten before m2c sees them, and the matching clean-up of its C afterwards. |
| `tools/pipeline/vu0_m2c.py` | Opt-in, conservative semantic VU0 adapter for the local m2c wrapper. |
| `tools/pipeline/vu0_micro.py` | Static, conservative VU0 microcall contracts for the retail upload images. |
| `tools/pipeline/stack_context.py` | Conservative stack-frame facts for automatic drafts; no target tools run here. |
| `tools/pipeline/context_recovery.py` | Recover PS2 call and layout constraints; never execute target tools on the host. |
| `tools/pipeline/permuter_service.py` | Run durable, restartable decomp-permuter searches inside the build backend. |
| `tools/pipeline/permuter_worker.py` | Worker-only durable decomp-permuter search with relocation-aware PS2 scores. |
| `tools/pipeline/permuter_lanes.py` | Worker-only supervisor for disjoint durable permuter search lanes. |
| `tools/pipeline/compiler_dumps.py` | Retrieve GCC pass dumps through the build backend for source-shape diagnosis. |

## Maintainer and analysis tools (`tools/maint/`)

| Tool | Purpose |
| --- | --- |
| `tools/maint/class_skeletons.py` | Generate conservative GCC 2.95 PS2 class skeletons from RTTI and vtables into build/classes/include/ (ignored). |
| `tools/maint/rtti_evidence.py` | Recover legacy GCC RTTI initialization evidence without executing target code. |
| `tools/maint/shift_test.py` | Shiftability test: insert NOPs into one function of a scratch copy, rebuild and check that references moved. |
| `tools/maint/handbook_controls.py` | Verify handbook recipes with isolated SN 1.36 retail controls and perturbations. |
| `tools/maint/symbols.py` | Dump symbols and debug data from every ELF kept under orig/ and estimate transfer to USA retail. |
| `tools/maint/discs.py` | Phase 0: unpack each disc image one at a time and keep only executables and debug candidates. |
| `tools/maint/iso.py` | Minimal ISO 9660 reader for plain ISO (2048) and raw CD images (MODE1/MODE2, 2352). |
| `tools/maint/inputs.py` | Phase 0 triage of every procured disc variant (run tools/maint/discs.py first). |

