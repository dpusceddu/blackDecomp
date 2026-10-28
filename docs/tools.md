# Tools

Every tool answers `--help`. One-line purposes are taken from each tool's docstring; this file is written by
`python3 tools/tools_index.py`.

A contributor needs the first two sections, which are the files directly in `tools/` (and `tools/permuter/`). `ninja` runs the
build internals itself, the automatic pipeline is reached through `tools/autodecomp.py`, and the maintainer tools regenerate
committed data. Tools import each other by bare module name; every tool puts `tools/` and its subdirectories on `sys.path`.

## Everyday tools: working on a function

| Tool | Purpose |
| --- | --- |
| `tools/setup.py` | Prepare the environment, assembly and objdiff metadata for a matching session; optionally verify the full image. |
| `tools/github.py` | Check Git identity and GitHub access for contribution sessions against the main repository. |
| `tools/next.py` | Best next work: the source files to claim next, and analyses from the automatic pipeline's results (build/auto.json). |
| `tools/brief.py` | Everything a work session needs about one source file, in one printout, so that it can start writing C at once. |
| `tools/decompile.py` | Friendly front door for one function: an m2c draft, ready to replace its INCLUDE_ASM line, and where to put it. |
| `tools/objdiff.py` | Generate a per-object objdiff project, build one comparison view, or write a fresh report. |
| `tools/trysrc.py` | Compile a hand-written C/C++ source with its owning file's recipe and score it against the original. |
| `tools/autodecomp.py` | Automatic decompilation: m2c -> clean -> compile variants -> score -> permuter -> register as source units. |
| `tools/where.py` | Name the source file that owns a function, and the line where it is: assembly, draft or source. |
| `tools/split_function.py` | Give one assembly function a source file of its own: the way to put a function in a file with other flags or another language. |
| `tools/relocate_sources.py` | Move source files and keep every reference to them consistent: the build inputs, documentation and generated comments. |
| `tools/permuter/prepare.py` | Write the assembly of one function in the plain form decomp-permuter's import.py reads. |
| `tools/permuter/cc.py` | Per-file compile command for decomp-permuter's import.py, using splits.yaml. |
| `tools/permuter/as.py` | Assemble a decomp-permuter target with its owning file's assembler from splits.yaml. |
| `tools/permuter/import.py` | Import a permuter seed while preserving PS2 scalar typedef attributes and checking 128-bit widths. |
| `tools/permuter/abi.py` | Preserve PS2 scalar typedef attributes across decomp-permuter parser round trips. |

## Everyday tools: build, check and progress

| Tool | Purpose |
| --- | --- |
| `tools/toolchain.py` | Local build toolchain: download, verify and unpack the pinned compilers, assemblers and wibo. |
| `tools/compile.py` | Compile one source with a pinned local compiler (Linux x86-64). |
| `tools/check_elf.py` | Compare a rebuilt executable with the target hash in config/<GAME_ID>/checksums.sha256. Build check, run by `ninja`. |
| `tools/diffelf.py` | Compare two ELF files section by section (a debugging aid for the identical rebuild). Convenience script; binutils `readelf` and `objdump` work too. |
| `tools/objdump.py` | Print the sections, symbols and relocations of a relocatable ELF object (reads the file only). Convenience script; binutils `mipsel-linux-gnu-objdump` and `readelf` work too. |
| `tools/progress.py` | Report how much of .text is provided by compiled source, overall and by library. |
| `tools/badges.py` | Write the self-hosted progress badges (progress/) and the progress table and source facts in docs/status.md. |
| `tools/tools_index.py` | Regenerate docs/tools.md, the index of the tools, from the docstring of every tool. |

## Optional environment provisioning (user or harness)

| Tool | Purpose |
| --- | --- |
| `tools/container.py` | Optional host launcher for a prepared Linux environment, provisioned by the user or harness before a session. |

## Build internals (`tools/build/`)

| Tool | Purpose |
| --- | --- |
| `tools/preparation_lock.py` | Serialize expensive preparation across worktrees of the same Git repository. |
| `tools/build/check_graph.py` | Check unique producers, direct generated-input dependencies and recovery of every generated file. |
| `tools/build/graph_io.py` | Record generator files or enforce a Ninja edge's declared generated-file reads and writes. |
| `tools/build/ninja_graph.py` | Construct Ninja edges and their generated-file I/O contracts from the same dependency lists. |
| `tools/build/prepare.py` | Run one source-generation stage; each invocation records its complete output inventory. |
| `tools/build/inventory.py` | Generate the USA function inventory used by the TU map and source analysis tools. |
| `tools/build/object_graph.py` | Generate real assembler includes and ordinary per-object Ninja edges from the split image. |
| `tools/build/object_compile.py` | Compile or assemble one Ninja input with its pinned local toolchain and write its depfile. |
| `tools/build/unit_link.py` | Place unit input sections in original order and invoke the ordinary GNU link once. |
| `tools/build/unit_compare.py` | Explain a full-image mismatch with function sizes and decoded instruction diffs. |
| `tools/build/asm_syntax.py` | Translate EE function includes for the selected assembler, preserving symbolic relocations. |
| `tools/build/split_objects.py` | Generate original function includes and constant ownership from splat output. |
| `tools/build/splat_config.py` | Generate the splat64 configuration for a retail boot executable from its ELF section table. |
| `tools/build/make_ld.py` | Linker alias helpers for compiler-owned data and labels referenced by assembly. |
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
| `tools/build/text_placement.py` | Recognize natural linker alignment after source sections, without inventing bytes. |
| `tools/build/constant_relocs.py` | Resolve words in compiler-owned constants for matching, including switch targets. |
| `tools/build/source_data.py` | Validate opt-in source-owned data ranges at labels or complete unwind groups. |
| `tools/build/ownership.py` | Which source file owns a function, and where in the file it is: the answer of `python3 tools/where.py`. |
| `tools/build/preflight.py` | One-line answers instead of tracebacks when the game's executable or the first build is missing. |
| `tools/build/assembler.py` | Explicit compiler -S / catalog assembler configurations. |
| `tools/build/patch_ps2eeas.py` | Reproduce retail's six-word short loops with SN Ps2EeAs 1.9.25.758. |
| `tools/build/fixasm.py` | Line-level rules that let the EE GNU assembler 2.10 reproduce the original words (used by split_objects.py). |
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
| `tools/pipeline/compiler_dumps.py` | Retrieve GCC pass dumps with the pinned local compiler for source-shape diagnosis. |

## Maintainer and analysis tools (`tools/maint/`)

| Tool | Purpose |
| --- | --- |
| `tools/maint/class_skeletons.py` | Generate conservative GCC 2.95 PS2 class skeletons from RTTI and vtables into build/classes/include/ (ignored). |
| `tools/maint/rtti_evidence.py` | Recover legacy GCC RTTI initialization evidence without executing target code. |
| `tools/maint/shift_test.py` | Audit relocation movement in an edited build using the linked symbol address map. |
| `tools/maint/handbook_controls.py` | Verify handbook recipes with isolated SN 1.36 retail controls and perturbations. |
| `tools/maint/iso.py` | Minimal ISO 9660 reader for plain ISO (2048) and raw CD images (MODE1/MODE2, 2352). |

