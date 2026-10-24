# Tools

Every tool answers `--help`. One-line purposes are taken from each tool's docstring; this file is written by
`python3 tools/tools_index.py`.

## Build

| Tool | Purpose |
| --- | --- |
| `tools/backend.py` | Where the toolchain jobs run: the built-in local backend (default) or an optional plugin module. |
| `tools/toolchain.py` | Local build toolchain: download, verify and unpack the pinned compilers, assemblers and wibo. |
| `tools/sandbox.py` | Run a build job script with the compilers, assembler and binutils of the selected backend. |
| `tools/compile.py` | Run one of the pinned EE compilers on a standalone source file. |
| `tools/build_objects.py` | Assemble and compile what changed, then link, in one call to the build toolchain . |
| `tools/build_job.py` | Job runner: assemble, compile, link and pack with the toolchain of the selected backend (sent by build_objects.py). |
| `tools/split_objects.py` | Cut splat's output into one assembly file (and later one object) per function, migrating constants with them. |
| `tools/splat_config.py` | Generate the splat64 configuration for a retail boot executable from its ELF section table. |
| `tools/make_ld.py` | Write the GNU ld script and the object list for the rebuild. |
| `tools/link_support.py` | Make splat's output linkable: define the symbols splat could not, so that every reference goes through a symbol. |
| `tools/pack_elf.py` | Write the final boot executable: GNU ld's linked sections inside the container the retail tools produced. |
| `tools/elf_layout.py` | Describe the container of a retail boot ELF (headers and non-loaded sections) for tools/pack_elf.py. |
| `tools/elfobj.py` | Fix-ups for relocatable objects written by the SN assembler (-snas) so that mainline GNU ld accepts them. |
| `tools/check_elf.py` | Compare a rebuilt executable with the target hash in config/<GAME_ID>/checksums.sha256. Build check, run by `ninja`. |
| `tools/diffelf.py` | Compare two ELF files section by section (a debugging aid for the identical rebuild). Convenience script; binutils `readelf` and `objdump` work too. |
| `tools/check_versions.py` | Rebuild every supported version and print OK or MISMATCH for each; run before a release or after changes to shared build tools. |
| `tools/include_asm.py` | Read and edit the INCLUDE_ASM markers of a translation unit source file. |
| `tools/splits.py` | Readers and writers for the committed, human-edited build inputs of one version (config/<GAME_ID>/). |
| `tools/tu_files.py` | Edit the translation unit files and the split list: the "register a match" step of the automatic pipeline. |
| `tools/units.py` | The source units of the build (python3 tools/units.py [GAME_ID] derives and caches them), derived from the split list, the source files and the symbol table. |
| `tools/units_verify.py` | Check the compiled source units against the original image; report what cannot be placed identically. |
| `tools/nm_build.py` | Build the NON_MATCHING drafts into a separate executable (`python3 configure.py --non-matching`, then `ninja`). |
| `tools/text_placement.py` | Recognize natural linker alignment after source sections, without inventing bytes. |
| `tools/constant_relocs.py` | Resolve words in compiler-owned constants for matching, including switch targets. |
| `tools/source_data.py` | Validate opt-in source-owned data ranges at labels or complete unwind groups. |
| `tools/assembler.py` | Explicit compiler -S / catalog assembler configurations. |
| `tools/patch_ps2eeas.py` | Reproduce retail's six-word short loops with SN Ps2EeAs 1.9.25.758. |
| `tools/boundaries.py` | Function boundaries splat cannot see: write config/<GAME_ID>/boundaries.txt (splat's symbol_addrs format). |
| `tools/fixasm.py` | Line-level rules that let the EE GNU assembler 2.10 reproduce the original words (used by split_objects.py). |

## Working on a function

| Tool | Purpose |
| --- | --- |
| `tools/decompile.py` | Friendly front door for one function: an m2c draft, ready to replace its INCLUDE_ASM line, and where to put it. |
| `tools/objdiff.py` | Per-unit objects and the project file for objdiff, and the progress report that decomp.dev reads. |
| `tools/objdiff_job.py` | Job for tools/objdiff.py (runs through tools/sandbox.py): build the target and base objects objdiff compares. |
| `tools/trysrc.py` | Compile a hand-written or templated C source for one function and score it against the original. |
| `tools/permuter/prepare.py` | Write the assembly of one function in the plain form decomp-permuter's import.py reads. |
| `tools/permuter/cc.py` | Compile script for decomp-permuter: run the pinned SN compiler on one self-contained source file. |
| `tools/permuter/as.py` | Assemble the target of decomp-permuter with the EE assembler of the pinned toolchain. |
| `tools/next.py` | Best next work, from the automatic pipeline's results (build/auto.json) and the source units (tools/units.py). |

## Progress and reports

| Tool | Purpose |
| --- | --- |
| `tools/progress.py` | Report how much of .text is provided by source (tools/units.py: functions the TU files do not mark INCLUDE_ASM), overall and by region. |
| `tools/badges.py` | Write the self-hosted progress badges and the per-library table (progress/) from the exact progress data. |
| `tools/build_telemetry.py` | Append small worker-call records under ignored build directories. |
| `tools/tools_index.py` | Regenerate docs/tools.md, the index of the tools, from the docstring of every tool. |

## Matching pipeline

| Tool | Purpose |
| --- | --- |
| `tools/autodecomp.py` | Automatic decompilation pilot: m2c -> clean -> compile variants -> score -> permuter -> register as source units. |
| `tools/m2c_input.py` | Present split sections and assembler-escaped instructions to m2c. |
| `tools/m2c_wrap.py` | m2c with one formatting change for the pipeline: a dereference at offset 0 of an expression that m2c has not typed as a pointer (an integer holding an address, say `lw $v0, 0($a0)` with $a0 an untyped argument) is written as `M2C_FIELD(expr, T *, 0)` instead of `*expr`, which is not valid C. |
| `tools/ee_prep.py` | EE instructions that m2c cannot read, rewritten before m2c sees them, and the matching clean-up of its C afterwards. |
| `tools/vu0_m2c.py` | Opt-in, conservative semantic VU0 adapter for the local m2c wrapper. |
| `tools/vu0_micro.py` | Static, conservative VU0 microcall contracts for the retail upload images. |
| `tools/stack_context.py` | Conservative stack-frame facts for automatic drafts; no target tools run here. |
| `tools/shared_context.py` | Verify the shared PS2 inline context against its real source consumers. |
| `tools/mod_context.py` | Verify the shared mod context using real PS2 source consumers and the full image. |
| `tools/context_recovery.py` | Recover PS2 call and layout constraints; never execute target tools on the host. |
| `tools/permuter_service.py` | Run durable, restartable decomp-permuter searches inside the build backend. |
| `tools/permuter_worker.py` | Worker-only durable decomp-permuter search with relocation-aware PS2 scores. |
| `tools/permuter_lanes.py` | Worker-only supervisor for disjoint durable permuter search lanes. |
| `tools/compiler_dumps.py` | Retrieve GCC pass dumps through the build backend for source-shape diagnosis. |
| `tools/equiv.py` | Differentially execute compiled candidates on every available recorded input. |

## Analysis and metadata

| Tool | Purpose |
| --- | --- |
| `tools/tus.py` | Translation-unit (TU) boundary evidence and the TU map of the boot executable. |
| `tools/layout.py` | Source layout rules: which library directory and which file name a source unit gets (src/<library>/<name>.c\|cpp). |
| `tools/class_skeletons.py` | Generate conservative GCC 2.95 PS2 class interfaces from RTTI and vtables. |
| `tools/rtti_evidence.py` | Recover legacy GCC RTTI initialization evidence without executing target code. |
| `tools/symbols.py` | Dump symbols and debug data from every ELF kept under orig/ and estimate transfer to USA retail. |
| `tools/discs.py` | Phase 0: unpack each disc image one at a time and keep only executables and debug candidates. |
| `tools/iso.py` | Minimal ISO 9660 reader for plain ISO (2048) and raw CD images (MODE1/MODE2, 2352). |
| `tools/inputs.py` | Phase 0 triage of every procured disc variant (run tools/discs.py first). |
| `tools/elfinfo.py` | Small ELF32 reader (little-endian, any machine) used by the Phase 0 tools. |
| `tools/objdump.py` | Print the sections, symbols and relocations of a relocatable ELF object (reads the file only). Convenience script; binutils `mipsel-linux-gnu-objdump` and `readelf` work too. |

## Equivalence harness (`tools/eeharness/`)

An EE interpreter and differential-test driver for the `equivalent` evidence tier; see its README.

## Finished studies (`tools/studies/`)

Experiments and one-time migrations whose results are recorded in [history.md](history.md). They are kept for reproducibility and are not part of the normal workflow.

| Tool | Purpose |
| --- | --- |
| `tools/studies/asmcheck.py` | Phase 0 assembler check: does a given EE-aware GNU assembler reassemble retail instruction words identically? |
| `tools/studies/divide_compiler_control.py` | Compare a retail scalar divide under catalog SN and Sony compiler defaults. |
| `tools/studies/full_tu_context_control.py` | Verify that real unfinished TU context cannot leak through sorted text inputs. |
| `tools/studies/handbook_controls.py` | Verify handbook recipes with isolated SN 1.36 retail controls and perturbations. |
| `tools/studies/large_study.py` | Reproduce a fixed private calibration set against the isolated compiler catalog. |
| `tools/studies/loop_padding.py` | Read-only short-loop diagnostics. |
| `tools/studies/loop_positions.py` | Read-only address-position study of retail SN-assigned short loops. |
| `tools/studies/loop_provenance.py` | Audit retail short-loop forms against the recovered TU and library map. |
| `tools/studies/migrate_include_asm.py` | One-time migration to one source file per translation unit with INCLUDE_ASM markers (stage 1 of docs/build.md history). |
| `tools/studies/migrate_split_list.py` | One-time migration, stage 2: config/units.yaml -> split list, symbol table and equivalent-tier file. |
| `tools/studies/reorganize_includes.py` | One-time move of include/ from origin-based directories to one directory per library, updating every #include. |
| `tools/studies/shift_test.py` | Shiftability test: insert NOPs into one function of a scratch copy, rebuild and check that references moved. |
| `tools/studies/verify_vu0_math.py` | Worker-compile isolated VU shapes and compare register-renamed retail windows. |
| `tools/studies/vu0_patterns.py` | Read-only VU0 shape census; generated instruction/site reports stay in build/. |
