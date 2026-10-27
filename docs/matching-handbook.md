# SN 1.36 matching handbook

Read this before each TU. The acceptance test is an identical full image, including owned data; an instruction score is
only a diagnostic. Use the unit's compiler, flags and assembler. All compiler execution goes through the per-object Ninja rule or
`compile.py` with the pinned toolchain in the Linux environment. Keep experiments and detailed results in ignored `build/`.

## Whole-TU ladder

1. Check `build/permuter/` for a better candidate. Note the TU's splits in `config/SLUS_213.76/splits.yaml` before editing. Inventory
   every real function and its rodata/data/sdata/bss/exception tables from the generated `build/SLUS_213.76/tus.yaml`; uncertain boundaries stay
   qualified. A code-complete TU is not data-complete until ownership is audited.
2. Recover behavior, callee arity/return widths, field offsets, hidden results and cleanup edges first. Xbox source gives
   algorithms and names, not PS2 layout proof. Matching work needs no recorded states.
3. Compare the first divergent instructions with `tools/trysrc.py`, using the actual bindings for named C++ symbols.
   Classify the obstruction below. Change one source feature, retain the best candidate, and compare the complete diff.
   Equal opcode lists can hide wrong offsets or widths; they do not prove a register-only problem.
4. Follow the relevant recipe through types, source evaluation order, scopes/temporaries, helper visibility, loop/case
   shape, allocation and scheduling. There is no per-function compile cap. Do not spend a flag sweep repairing a wrong ABI.
5. Submit every candidate with **1–29 differing instructions**, including status `mismatch`, to the permuter; larger
   functions go first. Continue another function within the same TU. Distinguish instruction count from weighted score.
   When the remaining instructions come from an inline helper, randomize that genuine helper while preserving its caller
   and scoring the caller's emitted body. Freeze the helper ABI and review float grouping before accepting a result.
6. Before leaving a hard function, exhaust the applicable ladder and leave one precise `// Unmatched:` obstruction in
   source; keep variants/diffs in `build/`. Revisit compiler and search evidence before moving to another TU.
7. Before submitting the session's final changes for review, confirm the registrations and run `ninja` and `ninja progress`.
   Use object comparisons during the ladder; full-image builds are not required after each function, TU or commit. Never demote previously exact work to
   claim a gain. Review shared headers and `splits.yaml` changes with extra care: they affect every file.

## Verified recipes

These are scoped controls, not promises that a rewrite will improve another function. Reproduce the retail checks with
`.venv/bin/python tools/maint/handbook_controls.py`; results and objects go to `build/handbook-controls/`. Each retail baseline
was recompiled with SN GCC 2.95.3 build 1.36 and scored **zero** against retail with relocation bindings, except the
explicitly identified native-CFI diagnostic whose metadata is exact while its body remains a draft. Synthetic
compiler controls are identified explicitly and make no retail-match claim. Flags are the
original unit flags, recorded by the tool. Restoring the original source restores the exact control.

| Obstruction | Practical recipe | Measured control |
| --- | --- | --- |
| Register allocation / argument setup | Establish real parameter and result types before changing locals. Preserve source parameter order even with independent integer/FP banks. Then shorten overlapping live values and test declaration order separately from evaluation order. | `0x1ED9C8`: floats-first declaration/calls preserve banks but add **31** differing instructions. `0x2D16B8`: swapping uninitialized declarations while preserving assignments stays **exact**; declaration order is a test, not a universal fix. |
| Address arithmetic / register coalescing | Preserve the operand order of PS2 byte-offset arithmetic separately from the element type and stride. Assert the native pointer width and element size; do not mistake typed pointer scaling for byte addition. | `0x2D77A0` (156 B): native byte-offset-plus-base is exact; reversing only those operands adds **4** register differences. The complete 13-function Wander TU also verifies the layout. |
| Hidden aggregate results | Declare a real aggregate return before shaping the caller. SN passes its hidden destination ahead of ordinary arguments; a guessed pointer result can introduce a false dependency on `$v0`. | `0x33AEE8`: the native storage-requirement result is exact; assuming a returned pointer to the hidden destination adds **3** differences (ABI-negative control). |
| Scheduling / delay slots | Preserve statement/operand order and alias information. Test the first scheduler independently only when the unit has evidence for that flag; inspect what actually moved. | `0x1052A0`: original `-fno-schedule-insns` is exact; enabling it adds **8** differences. This does not justify disabling scheduling globally. |
| Lifetimes / temporaries | Reconstruct scopes and construction points; do not hoist an iterator or address-taking temporary just to simplify source. Restore the original lifetime before trying register permutations. A visible inline scalar-return helper can preserve an FPR temporary where a direct literal becomes an integer store. | `0x2D6E48`: moving the iterator outside its `for` scope adds **13** differences. `0x30E9C8`: replacing the visible `Zero()` helper with direct literals adds **5** differences. |
| Scalar expression / CSE lifetimes | Test a genuine scaled expression at its uses before hoisting it to a shared float temporary. Preserve every floating operation's grouping; let the compiler share identical pure expressions. Focus the search on the helper that emits the differing instructions. | `0x3059F0` (1,508 B): the squared scaled-radius expression is full-image exact; introducing only `float reach=*radius*1.5f` and using `reach*reach` adds **8** FPR allocation/scheduling differences. No unused temporary, new operation or artificial dependency is retained. |
| Event predicate / return joins | Test positive and negative condition placement before adding a shared result. Preserve the actual discriminator width and call arguments. | `0x1998C0` (52 B): the positive event branch is exact; an equivalent negative early return adds **6** differences. All four action bodies and their native dispatch table pass the full image; original TU boundaries remain proposed. |
| Reused indices / reference views | Preserve the scope shared by related loops. A visible reference-return getter can retain a distinct global-address lifetime even when a value getter produces the same scalar. | `0x345510` (1,464 B): splitting the three skeleton-loop indices adds **29** differences. `0x345DC0`: replacing the reference getter with direct global access adds **20**. |
| Vector values / predicate width | Return constructed vector values directly before shaping their callers. Preserve comparison-result width and branch-local copies when they establish distinct address lifetimes; matching a narrow result does not identify the original typedef. | `0x2D3300` (448 B): materializing a product then copying its return adds **16** differences; changing only the narrow comparison to byte-bool adds **2**, or int adds **4**. All seven shared-header consumers remain exact. |
| Bitmap setup / shared captures | Form the slot mask before declaring its bitmap address; preserve a next-node capture shared by two insertion branches instead of reloading it independently. Inspect first-scheduler and allocation dumps to separate these changes. | `0x317C20` (328 B): moving the bitmap declaration before the mask adds **2** differences; splitting the shared next-node capture adds **2**. The other source consumers remain exact. |
| Commuting initialization / branch results | Preserve independent field-write order when it controls a shared constant's lifetime. Test shared results and direct failure returns independently: each changes the join lifetime. | `0x319ED0` (176 B): swapping only two zero stores or two shared-byte stores adds **2** differences each. `0x319950` (112 B): direct branch returns add **16**. `0x317E40` (384 B): replacing its direct null failure return with a nested result plus initialization join adds **4**; ordinary structured allocation and the failure return are exact. These bodies and their native storage pass the full image. |
| Alias information / null branches | Establish legitimate field types and alias relationships before allocator work. Test strict aliasing only where those accesses support it, then invert an equivalent null branch independently; do not assume either choice transfers to other TUs. | `0x32CDE0` (808 B): strict aliasing plus null-first pair release is exact; omitting only `-fstrict-aliasing` adds **123** differences, while changing only to nonnull-first adds **38**. Full-image integration preserves the scene's other exact bodies. |
| Nested storage alignment | Keep the genuine align-up stages in one size expression before adding array sizes. Preserve unsigned helper association separately from statement boundaries; splitting a valid expression can change value lifetimes and allocation. | `0x32BC70` (332 B): nested stages exact; splitting only the tree and solver stages adds **39** differences. Reassociating only `bytes + (alignment - 1u)` as `(bytes + alignment) - 1u` adds **4**. All 21 selected scene bodies and the unchanged native storage are checked independently; artificial 528 inputs agree, with no natural-state or equivalent-tier claim. |
| Shared induction expressions | Reuse an already computed next index when constructing paired free-list nodes; algebraically equivalent integer expressions can change induction optimization and allocation. Preserve the actual count and parity behavior. | `0x32D108` (304 B): `next - (i & 1) * 2`, with `next = i + 1`, is exact; replacing only the partner expression with `i - (i & 1) * 2 + 1` adds **23** differences and two instructions. |
| Loop shape / padding | Preserve entry test, induction direction, pointer stride, signedness and termination. Diagnose actual code changes separately from short-loop assembler NOPs. Select an alternate assembler only for the verified unit. | `0x18C178`: countdown rewrite adds **7** differences; stock assembler instead of `sn-min6` adds **5**. The original source with the per-unit assembler is exact. |
| Full TU inline context | Compile real neighboring bodies before judging inline lowering. Use the explicit `full_tu_context` option with function sections to retain unfinished source for compiler context while its original assembly stays linked; list reviewed discarded helpers. Never add dummy functions for allocator effects. | Twenty-one selected scene bodies, including `0x32DCE8` (532 B), reproduce the full image while five unfinished bodies remain assembly-backed. The current Sleep body stays exact with the unfinished bodies omitted too; context dependence must be remeasured after source changes. |
| Inline-helper placement / declarations | Put inline/template definitions before their callers. An identical body pasted into its caller need not lower the same way. Freeze helper order while working on a caller; retain visible identity-return views when they keep distinct address lifetimes. | `0x2D16B8`: moving the helper definition after its caller adds **20** differences and an external call. `0x3511D0` (1,944 B): removing only `NativeRowAddress` adds **14** differences; restoring it is exact. |
| Pure inline-assembly identity | Freeze helper definitions and source line placement while diagnosing repeated native operations. Identical pure-assembly text need not be commoned across different source lines; inspect the resulting transfers before changing lifetimes. | Synthetic SN control with genuine 128-bit input/output: one shared QMT helper emits **one** transfer (16 B); identical helpers on separate lines emit **two** (20 B body, 24 B input); putting those definitions on one line restores the shared result. Reproduce with `--only asm-source-identity`. This compiler control does not establish a retail constructor match. |
| EE 128-bit transport | Use `ps2/ee_types.h` and native vector transport. SN `long` is 64 bits, `long long`/TImode is 128; a 128-bit saved register alone does not establish a VU operation. Keep mixed 64/128-bit accesses distinct. | `0x17BDF0`: original native128 argument is exact; deliberately narrowing it to `unsigned long` adds **9** differences. This is an ABI-negative control, not a valid source alternative. |
| Native 128-bit temporary scheduling | Capture a native quadword immediately after each XYZ construction, then store the captures to their destinations. If ordinary scalar stores/native loads reorder, test volatile XYZ members and a volatile native read independently; preserve the unspecified fourth lane. | `0x32B598` and `0x33BA90`: both 324-byte initializers exact. On the latter, removing volatile from the native read adds **33** differences; removing scalar qualifiers adds **61** and shortens the function. No padding or physical-register constraints are used. |
| Branch-local native captures | Keep each branch's native rotation and position captures and stores within that branch before testing a shared temporary or joined store. Old GCC can coalesce the joined position with a rotation register even when the surrounding code is identical. | `0x346510` (344 B): branch-local captures exact; sharing only the position temporary and store across the join adds **3** register differences. Float/native alias views are retained at this lowering boundary; replacing them with union member expressions also changes scheduling. |
| Setup views / loop iterators | Keep setup addresses distinct from the iterators they initialize. Capture translation views inside the positive-count scope, then create the output rotation iterator before the input iterators. Test declaration order after restoring those lifetimes. | `0x347600` (308 B): distinct setup views and late iterators exact; reusing the setup variables as loop iterators adds **24** differences and removes two copies. Kept TU bodies and owned cache data pass the full image. |
| Root quaternion / translation views | Capture the actual root quaternion view before its branch; capture input then output translation views after the VU operation. Preserve the scalar identity construction order before changing registers or helpers. | `0x346CB0` (644 B): ordinary views and W/Z/Y/X identity stores are full-image exact. Moving the root view into the branch adds **12** differences; a literal identity initializer adds **2**; capturing output translation first adds **4**. No assembly or register constraints change. |
| Raw source / cache output cursor lifetimes | Construct a real input cursor from its track base, then advance it to the selected frame. Initialize the cache index before its positive-count test and declare the output iterator inside that guard; retain the original count reloads. | `0x346F58` (732 B) is full-image exact: combining raw base+offset initialization adds **10** allocation differences; hoisting the output iterator adds **3** scheduling differences. All variants retain the exact native 920-byte unwind group and the other 15 selected bodies. Reproduce with `handbook_controls.py --only builder-cursor-lifetimes`. The final match is manual after a valid service near-miss lead. |
| Native CFI / complete bone operations | Keep the W clear and consumed next-output cursor with the complete copy/blend operation when their split changes flags/output lifetimes. Compare natural CFI and function extents independently of code completion. | `0x3461D0` TU: all 920 native unwind bytes and 16 selected bodies match. The unfinished 732-byte Blend has **7** instruction differences; moving only W clear and cursor advance to the caller gives **21** and changes four CFI bytes. Returning the current cursor and adding one at the call site preserves the positive result. Reproduce with `handbook_controls.py --only consumed-next-cursor-native-cfi`; no metadata bytes are patched. |
| VU idioms | Reuse the verified `j`-allocated helpers or the separate fixed-VF animation helpers according to the original. Preserve masks, load order, written lanes, operand order and spill/readback shape. Hidden ACC/Q/flag state must satisfy the helper contract. | `0x3440B8`: fixed-VF quaternion+translation is exact; swapping independent operations adds **20** differences. The recipes have 26 exact consumers. |
| VU scalar readback / absolute value | Keep the float-return boundary, float/word view and storage lifetime distinct when the original transports a VU scalar through integer bits. Use the existing native VU helpers and let `j` operands allocate registers. | `0x33EB08` (128 B): typed dot/word/absolute helpers are exact; removing volatile from only the absolute-value union adds **9** differences. The dot helper transfers unchanged to three exact sphere callbacks. |
| Complete VU operations / native scratch | Keep an observed inverse, native scratch store/read and quaternion product inside one truthful operation when separate inline helpers extend the scratch-address lifetime. Retain real memory transfers, FPR roundtrips and hidden-state clobbers; let pointer/FPR operands allocate normally. | `0x346940` (876 B): complete quaternion difference exact; splitting only inverse and product into two visible helpers adds **10** differences. The helper, cache data and native 920-byte unwind group pass the full image; three unfinished bodies remain assembly-backed. |
| Native scalar builtin visibility | Use the supported single-precision builtin for a native scalar operation before shaping downstream registers. Opaque inline assembly can hide enough information to retain otherwise redundant argument copies; making that assembly volatile can add scheduling dependencies. | `0x34FB58` (296 B) and `0x34FC80` (400 B): `__builtin_fabsf` exact; replacing only the helper with opaque `abs.s` adds **5/6** differences, or volatile `abs.s` adds **10/11**. All 13 sampling TU bodies and native 880-byte unwind group match. Double-precision and conditional alternatives regress; preserve float semantics. |
| Switch / jump tables | Reconstruct the source `switch`, explicit default, shared cases and case-local scopes. Keep its table with the function; matching the body does not verify table placement. | `0x18DCE0`: switch exact, an if-chain with **30** differences. The object contains `.rodata` plus relocations into the generated jump table. |
| C++ cleanup / destructors | Define inline destructors before callers and preserve exit scopes, including early returns. Use ordinary destructor names; if a label alias is required, retain destructor-shaped ABI spelling and verify both normal and exceptional cleanup. | `0x2D6E48`: destructor definition after caller adds **38** differences. A synthetic SN control retains cleanup with the normal `_$_5Probe` alias; a plain `cleanup` alias removes both cleanup paths (104→68 B). Compiler-only evidence does not identify a retail class. |
| gp-relative data | Match `-G` and the declaration's known size. A small sized extern and an unsized array can lower differently under the same flags. Resolve the actual GPREL relocation target and addend; never forgive it just because the instruction matches. | `0x10BBF8`: sized extern under `-G8 -snas` exact; either `-G0` or unsized extern adds **2** differences. Assembly inputs require the existing `.extern symbol, 1` convention. A locally defined small-data section uses unnamed section relocations and object GP0; pass its verified base via `compiled_tokens(section_bindings=...)`, then verify the full link. |

Register-renamed arithmetic windows alone do not verify physical
allocation, surrounding scheduling or a new W/flag-state contract. Scale, cross and normalization recipes still marked
provisional in `include/ps2/README.md` remain provisional.

Do not discard a caller's upper GPR lanes as harmless scratch. The actual `0x33DAF8` bounds callback uses `MFC1`
followed by `QMTC2`: the first preserves the GPR's upper 64 bits ([PCSX2's implementation](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/FPU.cpp#L270))
and the second copies them into VU lanes, so an XYZ
operation can store an inherited W payload. An earlier 166-instruction `0x32C5A0` control with all opcodes matching
changed bound W bytes when its caller-side allocation changed. Correcting the genuine native frame-copy capture order
subsequently preserved the observed upper lanes of V0 entering the callback: the 18-difference draft passes all 178 recorded inputs, including
whole-quad writes and VU outputs, though that coverage is incomplete. A separate
20-case artificial diagnostic varies full 128-bit W payloads and substitutes static/no-body and callback outcomes; its
union reaches all 12 blocks, 166 instructions and eight branch outcomes. This does not increase natural coverage. Check whole
quad writes and the strict recorded contract; matching XYZ arithmetic does not establish equivalence or justify register pins.

For a hard allocation/scheduling problem, SN accepts `-da -fdump-unnumbered`. An isolated compiler control emitted
RTL, GCSE/loop/combine, first scheduling, local/global allocation, second scheduling and delay-slot dumps; adding these
flags preserved every text section of three exact controls. Compare the earliest divergent pass of two source variants:
fix lowering/combine before blaming allocation, then inspect scheduling. Use
`.venv/bin/python tools/pipeline/compiler_dumps.py SOURCE --flags '-O2 -G0 -snas'` to generate them with the pinned local compiler.
Dumps and generated assembly stay under `build/`.

A scalar divide with otherwise identical instructions can expose a compiler-default workaround. Reproduce
it by compiling the leaf under both compilers: the unchanged `0x3484D0` field expression is **2**
instructions short under SN 1.36 and **exact** under Sony `ee-gcc2.9-991111-01`. This leaf uses no wide ABI;
its two field offsets are asserted. Sony `ee-gcc2.96` also matches: disabling its accepted
`-mhandle-ee-div-pipeline-bug` option removes exactly those two instructions, establishing the workaround effect.
SN 114/136 and 273a reject that option; accepted CPU and division switches leave the two-slot deficit. The related 300-byte fade body regresses **4→12** differences under Sony,
and six larger methods in the leaf's TU also regress, so keep this compiler choice scoped. Do not add NOP tables or
infer the original compiler for the complete TU. [OpenRAC's divide investigation](https://github.com/OpenRAC/rac3-uya-decomp/blob/main/docs/full_match_roadmap.md)
motivated this control; the local unchanged-source comparison is the evidence used here.
The shared `ps2/ee_fpu.h` helper mirrors the measured guarded divide with two real generic FPR inputs and one result.
Under SN, the guarded leaf is exact and removing the guard adds **2** differences. Verified consumers include the
1,464-byte initializer; the complete 26-function `0x347A50` TU also reproduces its native 1,004-byte unwind group.
Select this recipe only where the retail sequence supplies that evidence; it does not establish the original compiler.
The ordered helper is volatile; the separately named value helper permits scheduling across the operation. The 300-byte
`0x348D00` fade consumer is exact with the value helper but has **7** differences with the ordered helper. Changing the
existing ordered initializer or leaf to the value helper adds **3** differences each. Keep the selection explicit and
verify all consumers; no per-address padding or unused FPR input is needed.

## Data and integration traps

- Preserve string bytes, alignment, table order, symbol aliases and exception-table ownership. Keep generated data out of
  Git; write source definitions only when their ownership and meaning are supported. Unresolved ownership is an open TU item.
- Check defined data symbols at their actual object offsets, not only bound instruction scores and total section size.
  In the pose-cache control, SN placed an earlier-declared counter before a later aligned arena, even when their definitions
  were reversed. A truthful arena declaration before the header restores the exact offsets; the kept bodies, five globals
  and the 46,160-byte native BSS input verify in the full image. Audio SBSS also follows first declarations, including externs;
  place supported definitions before callers in native order. `units_verify.py prepare` rejects misplaced original labels.
- Prefer separate meaningful string declarations to packed literals with hand-written NUL padding. The steering registration's
  three names naturally reproduce 96 bytes at offsets 0/32/48 under SN. The handbook control swaps the last two: all six
  bodies stay exact while the data offsets change. Verify both the native input and the full image.
- Native unwind ranges need their original function extents, including the compiler’s section-switch timing. In the
  `0x2E72F0` control, moving typed data definitions past the next functions leaves all ten bodies exact but changes
  one FDE extent from 12 to 16 bytes. Place declarations/definitions where the compiler naturally closes that range;
  do not repair it with opaque unwind bytes or padding.
- With `-ffunction-sections`, a C++ assembler label does not necessarily rename its section. Use the unit's established
  declaration/section macro and inspect the object; a zero body score can still produce an undefined symbol at full link.
- Constants, HI/LO carry, GPREL addends and jump-table targets need relocation-aware comparison and the final image check.
- SN's native `.lit4` pool can use `R_MIPS_LITERAL` (8), with the same local GP0 adjustment as GPREL. Keep the owned
  pool when promoting its function. The audio constructor's native `22050.0f` and `10000.0f` emit the exact eight-byte
  pool; extern-only declarations match its instructions but lose that owned input at full link.
- A permuter improvement remains a candidate until source review, confirmation and full-image equality. Random rewrites can
  change signedness, aliasing, evaluation order or exception behavior. Keep the readable seed and review the resulting diff.

## Community leads and limits

The recipes above were measured locally. External guides motivate experiments; compiler-specific advice is not promoted
without a Black/SN control. These are the sources consulted:

- [decomp.me FAQ](https://www.decomp.me/faq): compiler/assembler/flags/context and score interpretation.
- [OoT getting started](https://github.com/zeldaret/oot/wiki/Getting-Started) and
  [SM64 build](https://github.com/n64decomp/sm64/blob/master/Makefile): whole-build validation and source-file workflow;
  their original matching compiler is IDO, so its allocation tricks are not SN recipes.
- [Paper Mario GCC 2.8.1 tips](https://github.com/pmret/papermario/wiki/GCC-2.8.1-Tips-and-Tricks): induction forms,
  switch reconstruction and likely-branch experiments. Condition placement has the scoped event control above;
  compiler-specific likely-branch advice remains a lead.
- [Sly contributor guide](https://theonlyzac.github.io/sly1/html/md_docs_2CONTRIBUTING.html) and
  [PS2 cheat sheet](https://github.com/TheOnlyZac/sly1/blob/main/docs/mips_ps2_cheatsheet.md): context, declarations and
  delay-slot diagnosis. Local SN width/ABI controls take precedence over general tables.
- [Dog's Life](https://github.com/IWILLCRAFT-M0d/dogcomp) and
  [splat #525](https://github.com/ethteck/splat/issues/525): SN assembler syntax, short loops and gp expressions.
  Its reported `vadda` operand reversal is assembler-specific; do not apply a global operand swap.
- [OpenRAC matching patterns](https://github.com/OpenRAC/rac3-uya-decomp/blob/main/docs/wiki/Matching-Patterns.md):
  return types, data declarations, helper visibility, scopes and VU allocation. Its per-project flags are not Black defaults.
- [permuter usage](https://github.com/simonlindholm/decomp-permuter/blob/main/USAGE.md) and
  [GCC weights](https://github.com/simonlindholm/decomp-permuter/blob/main/default_weights.toml): use GCC weighting,
  focused manual alternatives and explicit randomized regions; measure tuning on retained best candidates.
- [GCC 2.95.3 debug options](https://gcc.gnu.org/onlinedocs/gcc-2.95.3/gcc_2.html#SEC13): pass dumps for diagnosis.
