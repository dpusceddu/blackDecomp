# Build migration design

The build will use ordinary Ninja edges: extract/splat, generate assembler inputs and the object graph, one compile or
assemble per unit, one link, pack, compare. Generated includes live at
`asm/<version>/nonmatchings/<source-relative-stem>/<function>.s`. `INCLUDE_ASM` emits an assembler `.include`; unmatched
functions are assembled by the same assembler as the recovered code in their file. No source-unit function has a separate
assembly object. Assembly-only segments have one assembly input and object per segment.

Assembler input generation expands labels without splat macros or `.size` for SN. It preserves relocatable references,
uses named aliases for gp-relative addends, spells coprocessor instructions in the selected assembler's syntax, and emits
unsupported instructions and padding-sensitive backward branches as original words. The selected compiler and assembler
remain properties of each file in `splits.yaml`.

Objects retain ordinary function sections where needed by disjoint historical ranges and compiler context. The linker
script explicitly places these sections in original order; it does not rename them to numeric addresses or sort them.
Constants keep their established ownership and link positions. A unit's compile produces its final object without a
full-image size gate, so an unfinished edit is immediately usable in objdiff. Full-image verification reports size and
instruction differences after linking. Header and assembly include dependencies belong to the individual compile edge.

Objdiff compares one original object and one source object per unit. Assembly functions are excluded from source progress,
even though the linked object contains them. A generated comparison view can strip assembly-backed functions without
changing the actual linked object. Objdiff invokes the single-unit Ninja target, with an ignored local command override.

Migration checkpoints:

1. Establish a clean byte-identical baseline, progress and fresh report agreement; verify assembler inclusion on controls.
2. Switch to real inclusion and an explicit per-object Ninja graph; retain source behavior, constants and all exact matches.
3. Integrate per-object objdiff, diagnostics, permuter import and contributor documentation; remove obsolete build machinery.
4. Validate clean/container/regional/non-matching builds, tests and the edit/revert workflow, and record measured times.

Every committed checkpoint must pass the retail identity, unchanged progress and fresh objdiff agreement checks.
