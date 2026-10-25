# Per-unit build design

The build uses ordinary Ninja edges: extract/splat, generate assembler inputs and the object graph, one compile or
assemble per unit, one link, pack, compare. Generated includes live at
`asm/<version>/nonmatchings/<source-relative-stem>/<function>.s`. `INCLUDE_ASM` emits an assembler `.include`; unmatched
functions are assembled by the same assembler as the recovered code in their file. No source-unit function has a separate
assembly object. Assembly-only segments have one assembly input and object per segment.

Assembler input generation expands labels without splat macros or `.size` for SN. It preserves relocatable references,
uses named aliases for gp-relative addends, emits fixed encodings for coprocessor and unsupported instructions, and preserves padding-sensitive backward branches
as original words. Symbolic jump and GP records retain linker relocations. The selected compiler and assembler
remain properties of each file in `splits.yaml`.

Objects retain ordinary function sections where needed by disjoint historical ranges and compiler context. The linker
script explicitly places these sections in original order; it does not rename them to numeric addresses or sort them.
Constants keep their established ownership and link positions. A unit's compile produces its final object without a
full-image size gate, so an unfinished edit is immediately usable in objdiff. Full-image verification reports size and
instruction differences after linking. Header and assembly include dependencies belong to the individual compile edge.

Objdiff compares one original object and one source object per unit. Assembly functions are excluded from source progress,
even though the linked object contains them. A generated comparison view can strip assembly-backed functions without
changing the actual linked object. Objdiff invokes the single-unit Ninja target, with an ignored local command override.

Migration checkpoints (completed in order):

1. Establish a clean byte-identical baseline, progress and fresh report agreement; verify assembler inclusion on controls.
2. Switch to real inclusion and an explicit per-object Ninja graph; retain source behavior, constants and all exact matches.
3. Integrate per-object objdiff, diagnostics, permuter import and contributor documentation; remove obsolete build machinery.
4. Validate clean/container/regional/non-matching builds, tests and the edit/revert workflow, and record measured times.

Every committed checkpoint must pass the retail identity, unchanged progress and fresh objdiff agreement checks.

The implemented architecture and measured times are in [build.md](build.md). All configured USA source files use real
includes. Data-only assembly objects remain separate; none is an unmatched source-function code fallback. The three
combined-text CFI recipes are normalized within their single TU objects. The old per-function code objects, address-sorted
link, `sections:` keys, compile batching, backend hook and custom permuter service have been removed. The source label
reader remains for editing and ownership analysis, rather than substituting assembly objects for compiler input.

## Validation

The final USA clean build in a fresh `debian:bookworm` container followed the README and printed
`OK  SLUS_213.76 ... sha256 141b05209570458af9c8e27ab1911f258da6353909d813cd572df026254ffe4c`.
A fresh report agreed with progress: 5,563 exact functions, 14.95% code and 15.11% image. Both suites passed
(91 build tests, 319 tool tests, no skips with the optional pinned permuter installed), along with CLI help,
byte-compilation, configuration parsing, split consistency and the tools-index check.

`tools/check_versions.py` passed all five retail versions. Its cold regional assembly rebuilds took 1,838.030 seconds;
ordinary USA clean and incremental measurements are in [build.md](build.md#measured-build-times).

The CONTRIBUTING edit-in-place example built its single objdiff object, passed the full image comparison and reverted
cleanly. An 8-byte function deliberately expanded to 20 bytes still built in objdiff without linking; the full check
reported its size and decoded instruction diff. `where.py` and `decompile.py --write` worked in that workflow.

A clean `configure.py --non-matching` and Ninja run linked successfully. Its 76 unfinished-draft fallbacks have individual
compiler or symbol diagnostics in the generated `nm_fallback.json`; they retain the real-include matching recipe.
Compiler timeout testing also verifies that an assembler child cannot survive the stopped process group.

The per-file permuter compile and assemble scripts passed SN 1.36, `sn-min6` and Sony 2.9 controls. Upstream `import.py`
with the documented `--no-prune` command imported the C example without warnings, and upstream debug scoring returned zero.

## Generated-file graph follow-up

The clean-recovery audit found preparation metadata and object sidecars that were produced outside declared Ninja edges.
Preparation now records its complete input/output inventory, while object/link/report edges share their dependency lists
with enforced I/O contracts. The graph checker covers 47,421 generated paths. The root manifest contains the generated
edges directly, so removing `objects.ninja` cannot prevent Ninja from loading its repair rule.

A fresh workspace rebuilt the retail image. Deletion sweeps recovered 46 individually deleted files spanning every
preparation producer, all preparation inventories and each leaf-output kind. Separate cold tests cover the default build, progress, objdiff, report and a single
object after `ninja -t clean`. The CI regression tests also check missing/duplicate producers, direct read dependencies,
actual undeclared reads, multi-output clean recovery and missing-manifest recovery without game files or an SDK.

Unchanged object and metadata bytes retain their timestamps; canonical JSON ordering prevents Python hash seeds from
causing spurious relinks. Context symbols are recorded with each object, and linker planning uses indexed function lookups.
Current wall-clock measurements and the remaining GNU ld cost are in [build.md](build.md#measured-build-times).

The follow-up validation passed 91 build tests and 326 tool tests (two optional permuter tests skipped), CLI help,
byte-compilation, configuration parsing, split consistency and the tools-index check. A new fresh report again agreed
with 5,563 exact functions, 14.95% code and 15.11% image. All five retail versions passed the version check.
