# Build

Use the Linux x86-64 setup in [README](../README.md). `configure.py` prepares the split image and writes an ordinary Ninja
build. `ninja` compiles or assembles individual objects, links once, packs the retail ELF container and checks its SHA-256.

```sh
python3 configure.py
ninja
ninja progress
ninja report
python3 tools/progress.py --check
```

## Objects and includes

All 2,732 USA source files in `splits.yaml` use real INCLUDE_ASM, with no code fallback objects. Each produces one object, `build/<version>/obj/units/<unit>.o`. It contains its recovered C/C++
and its original assembly. `INCLUDE_ASM` is an assembler `.include`, for example:

```c
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_201518", func_00201960);
```

Generated assembly stays ignored. A version without recovered source assembles its text segment from its own assembly;
it does not create one object per function. Data and shared constant runs have their own assembly objects. The existing
ownership analysis keeps compiler-owned constants, exception tables and explicitly reconstructed data in their original
positions. The label reader remains useful to source-editing and ownership tools; it does not substitute assembly objects
for source-unit functions.

Ninja has one compile/assemble edge per object and depfiles for project headers and assembly includes. Changing one
function recompiles its file and relinks. An unchanged default build does no work. Source objects retain ordinary named
function sections: some historical files own disjoint stretches of the executable. The link script places these input
sections explicitly in original order. It has no address-named text sections, numeric sorting, contiguity requirement or
`sections:` setting.

`tools/build/object_compile.py` runs the per-file compiler, flags and assembler selected by `splits.yaml`, through the
pinned local installation from `tools/toolchain.py`. There is no backend plugin, build service, batched compile/link job or
content-addressed build cache. Ninja owns incremental rebuilding. The linker is GNU binutils 2.40, installed by the
`binutils-mipsel-linux-gnu` distribution package; `BLACK_BINUTILS_PREFIX` can select another compatible prefix.

The compiler installer checks archive hashes. SN 1.36 runs under the pinned wibo; Sony's compiler and GNU assembler are
32-bit Linux programs. `sn-min6` remains the explicitly selected, hash-checked assembler derivative on its established
files. `tools/build/pack_elf.py` preserves the original ELF container and opaque DVP overlays; it takes rebuilt loaded
sections from the ordinary linked ELF. No game bytes enter the source tree.

## Assembler compatibility

[splat issue #525](https://github.com/ethteck/splat/issues/525) describes the SN integration problems. The generated includes
expand label macros directly and omit `.size` and incompatible macros. The original function sizes are supplied separately
when generating objdiff targets. Fixed `.word` encodings cover undecodable words, VU instructions (including reversed
operand conventions), coprocessor spellings such as `c1`/`cop1`, and padding-sensitive short branches.

GP operands need extra care even with GNU: the older assemblers can expand a small-data operand under a file's `-G0`.
Includes emit a symbolic word and an explicit relocation marker. Object normalization converts that declared word to its
instruction encoding and `R_MIPS_GPREL16`. GP symbol-plus-offset operands use named linker aliases. SN direct jumps use the
same mechanism with `R_MIPS_26`; this avoids its delay-slot tracker treating a following raw word as an unconsumed slot.
These remain symbolic linker relocations; no linked addresses are patched into objects. The normalizer rejects unexpected
relocation forms and out-of-range addends. It also sorts SN's ELF symbols for GNU ld.

Floating constants in SN includes use original words, preserving negative zero. SN can impose excessive default alignment
and zero tails on included constant sections. Their original intervals establish
which zero tails may be removed and which alignment their original starts actually support. Recovered C functions never
pass through that include-layout adjustment. Exception labels SN drops from its symbol table retain function-relative
linker aliases. Three complete C++ files retain `-fno-function-sections` for native CFI; normalization splits their text
and rebases section references without changing instructions or unwind ranges. Two files keep unfinished bodies as
compiler context under separate context symbols and discard those inputs; their actual assembly still enters through real INCLUDE_ASM.

## Objdiff and drafts

`ninja objdiff` writes `objdiff.json` and a comparison pair per source object. The GUI invokes
`ninja build/SLUS_213.76/objdiff/base/<unit>.o`, which builds only that file and its comparison view. It requires neither a
link nor a fit check. The comparison base excludes included assembly, preserving honest source progress; the linked object
contains it. `ninja progress` builds its report dependency too. `ninja report` regenerates the report from these views, and `tools/progress.py --check` checks agreement with
the exact source functions.

An ignored `.local/objdiff.json` may override `custom_make` and `custom_args`, using the same fields as objdiff's project
schema. It is never committed. Public builds and the default generated command use `ninja`.

```sh
python3 configure.py --non-matching
ninja
python3 configure.py
```

Files whose unfinished drafts fail compilation, stall the assembler or introduce unbound symbols retain their matching
object recipe, still with real includes. A timeout stops the entire compiler/assembler process group before fallback. Each fallback and its reason is recorded in `build/<version>-nm/nm_fallback.json`. There is no iterative
whole-build demotion loop. The draft build has its own objects and linked ELF under `build/<version>-nm/`. It does not compare against retail. An
unfinished edit belongs under `#ifdef NON_MATCHING` with INCLUDE_ASM in the `#else` only when committing; use the unwrapped
edit while watching objdiff. Full-image mismatch diagnostics report function sizes and decoded instruction differences.

## Link-once copies

Compiler-emitted inline/template copies remain in `src/<library>/inline/`, with their established ownership, flags and
original positions. Their compiler symbols and per-file external bindings receive unique link names when necessary;
original address labels remain aliases.

## Symbols and progress

Hand-maintained `symbols.txt` binds recovered compiler names and external references. Lines marked `alias` are readable names only and never affect linking.

The nine progress categories are `game`, `kynapse`, `rw_core`, `rw_audio`, `animation`, `physics`, `apt`, `sony`, `libc`.
The image measure includes padding and orphan pieces; objdiff's code measure excludes them. See
[progress reports](progress-reports.md).

## Shiftability

The linker moves symbolic jumps, HI16/LO16 pairs, GP references, data pointers and exception references with their targets.
Fixed raw branch words describe local loops whose relative offsets stay constant when their function moves. Raw numbers
in data that resemble addresses remain an open limitation, including pointers into opaque DVP blobs that lack symbols.
Arithmetic-built addresses also need individual review. `tools/maint/shift_test.py` audits an explicitly edited build
against a symbol-derived address map; use its `--help` for the ordinary Ninja edit-and-link workflow.

## Measured build times

Measured on Linux x86-64 in the project's Debian Bookworm container, using default Ninja parallelism. Downloads and
environment installation are excluded. These are individual wall-clock observations, not benchmark averages. The clean
measurement starts after `ninja -t clean`; Ninja retains generator manifests and recreates all removed build inputs.

| Operation | Seconds |
| --- | ---: |
| `ninja` after `ninja -t clean`: regenerate, compile, link, pack and compare | 99.215 |
| One exact function edited in place; identical object bytes, no link | 3.590 |
| One function changed; object, link, pack and decoded mismatch diagnostic | 8.756 |
| No-op Ninja: no commands and unchanged linked ELF | 0.384 |

The exact edit changes `return arg0;` to `return (arg0);` in `tu_100258.c`; both versions match retail. The changed-code
control uses `return arg0 + 1;` and deliberately fails the image comparison, then is reverted. Objdiff's single-object
target skips the full link and image comparison even for a draft with a different size.

The previous 14.792-second exact-edit build unnecessarily relinked. Profiling found repeated ELF-symbol parsing and
function-list scans in link preparation; context-symbol sidecars and indexed lookups remove that work. Unchanged-byte
restat now skips the link entirely. A full link still spends about 3.2 seconds in GNU ld. Mismatch diagnostics also used
to copy the remainder of the linked ELF's string table for every symbol; bounded string slices remove that quadratic cost.

## Generated-file dependencies

`build/<version>/graph.json` lists the producers and direct inputs of the active Ninja graph. Source-generation stages
record their dynamic output inventories in `prepare/*.json`: this includes splat configuration, section layout and blobs,
undefined-symbol lists, function tables, unit recipes, placement, original assembly, the analysis inventory and generated
per-unit inputs. Each file belongs to one edge. The graph generator retains its manifests and recipe files during an
ordinary `ninja -t clean`; removed source-generation inputs are rebuilt before those manifests are used again. The root
Ninja file contains all edges, so deleting a generated manifest cannot prevent Ninja from parsing the rule that repairs it.

Object state (`.o.json`), link facts, linker scripts/maps, objdiff target assembly and comparison objects, reports and
progress JSON are declared outputs too. Build-rule readers do not create missing caches. Per-edge `io/*.json` contracts
are generated from the same input/output lists as the Ninja edges; `graph_io.py` rejects an actual undeclared generated-file
read or write. This includes file-existence checks. `python3 tools/build/check_graph.py --ninja` checks producer uniqueness,
direct dependencies, cycles and agreement with Ninja's output list. The tests exercise clean/deletion recovery and reject an
intentionally undeclared read without needing the game or SDK.

Ninja owns compiler depfiles and its internal log/dependency databases. The separately installed SDK is an external
prerequisite, including when it is installed under `build/toolchain/`; clean does not uninstall it. One-off decompiler,
permuter and class-recovery experiments remain explicit analysis commands rather than hidden build-rule side effects.

Compilation and packing preserve timestamps when their final output bytes are identical. Ninja's `restat` then skips
unnecessary downstream linking or comparison; changed objects still undergo the ordinary link and full image check.
Unit metadata uses canonical JSON ordering, so a different Python hash seed cannot trigger a relink by reordering keys.
The link preparation reads context-symbol metadata recorded during each compile, rather than reparsing every ELF symbol
table on every link.
