# EE differential-execution harness

**Gate 1 (functional audit) passed; Gate 2 (enough recorded real-game states) is not passed.** This independently authored
host C++ interpreter executes no compiler or SDK tool; game code is still compiled with `tools/compile.py` and the build
backend. Generated reports, ELF overlays and reference material belong in ignored directories.

Build the harness with CMake and any C++17 compiler (`cmake -S tools/eeharness -B build/eeharness/host && cmake --build
build/eeharness/host`); the commands below use the built binary.

```sh
ctest --test-dir build/eeharness/host --output-on-failure
.venv/bin/python tools/eeharness/audit.py
.venv/bin/python tools/eeharness/selfcheck.py
.venv/bin/python tools/eeharness/gate1.py --logs .local/eeharness-references
```

The decoder audit checks every `.text` word against rabbitizer, normalizing only
mnemonic aliases. Invalid rabbitizer words remain separately reported. Decoder
agreement and the presence of an execution handler are not semantic validation.

Implemented: scalar integer operations and delay slots, MMI operation handlers,
COP1 integer-bit arithmetic/flags/transfers/conversions, VU0 macro operations,
EE-connected VU0 micro execution, COP0/COP2 conditional branches and ERET,
ELF segment loading, 32 MB RAM
with aliases, scratchpad and VU0 memories. `Machine::call` captures returns,
final written bytes and ordered external events. `Machine::run` accepts an
instruction budget and invokes `on_entry` at selected PCs, after call delay
slots. Copying the supplied state and memory retains a replayable input through
copy-on-write pages. Hardware and syscall defaults are zero, explicitly marked
in the trace; configured register responses are separate from gameplay memory.
Unknown addresses and unsupported instructions stop the run.

The function pilot stages 50 candidates from existing private autodecomp results,
claims the tracked candidates, then compiles and replays them through the build backend:

```sh
.venv/bin/python tools/eeharness/pilot_plan.py
.venv/bin/python tools/equiv.py build/eeharness/pilot/plan.json --claim-only
.venv/bin/python tools/equiv.py build/eeharness/pilot/plan.json --record-evidence
.venv/bin/python tools/eeharness/equiv_tests.py
.venv/bin/python tools/eeharness/pilot_controls.py
```

The first batch tested 6,132 recorded inputs and 249 existing typed mutations.
Fourteen readable C++ functions (984 original bytes) passed with 100% measured
basic-block coverage; their evidence is in `config/units.yaml`. Those fourteen
had no applicable pre-existing typed mutations; their claims concern recorded
states only. All ten candidates above 1 KB remain drafts. The 50-function target
is not passed. Full results, inputs and hashes stay under `build/eeharness/pilot/`.

Each candidate contains one function plus immutable constants at interpreter-only
addresses `0x08000000..0x09000000`; original RAM and callees remain in place.
This adapter is separate from a deployable nonmatching ELF. Return values,
preserved registers, written bytes and ordered events are compared. Only local
stack storage actually allocated below entry SP is excluded; escaping stack
pointers require an explicit contract. All call argument banks and auxiliary
FPU/VU outputs are compared conservatively, so allocation differences can reject
correct candidates. Pending VU outputs, faults and budget stops cannot pass.
Coverage uses the original direct CFG, excluding unreachable alignment; unresolved
indirect jumps block promotion. At least 90% of basic blocks and twenty recorded
inputs are required. Raw generated drafts and unreviewed ABIs cannot be promoted.
The matching source placement stays unchanged. Cached executions bind candidate,
harness, snapshot, corpus and fuzz hashes. Agreement is evidence on tested states,
not a proof or whole-program validation.

The MMU profile uses the supplied 48-entry TLB: all seven page sizes, ASIDs,
global/valid/dirty bits, scratchpad mappings, privilege segments and ERL bypass.
TLB instructions, Random/Wired, Count/Compare, Cause/Status write rules and
coprocessor usability are implemented. Translation and execution faults stop the
bounded run; they cannot qualify as successful differential executions. Synthetic
instruction fixtures default to flat RAM; real-state replay enables the MMU.
Count observations identify the deterministic clock profile in their trace.

The VU engine retains pending vector/integer/flag/Q writes in each input state.
It models micro lane hazards, macro whole-register RAW/WAW and VF/VI-number hazards,
simultaneous issue/write priority, integer branch backup,
E/M bits, enabled debug stops, clip history and divider delays. VCALLMS/VCALLMSR
launch microprograms; transfer `.i` variants apply their distinct completion/M
interlocks. Deadline-limited stepping retains future writes until their issue or
writeback time. FBRST resets/force breaks are modeled; VU1 commands are recorded
external stubs. The published micro fixtures pass both standalone and through
the EE call interface. Arithmetic tests distinguish final-result cause/MAC flags
from product-stage sticky flags, including an overflowed accumulator and
overlapping FMAC/divider writeback.
OPMULA and OPMSUB use the same cyclic lane products; a cross product reverses
the second instruction's register operands. Independent tests check supplied
accumulators, cancellation, aliased destinations and 3-4-5 normalization in
addition to the instruction-pair fixtures.

The functional gate combines 1,506 sanitizer assertions, all retail decoder words,
published instruction fixtures, and the exact/mutated-source controls. Its report
binds the executable and authored sources in `build/eeharness/gate-1.json`.
The three compiled fixtures that reach reviewed undefined/reserved operations
must stop at those exact words with the preceding output matching; they are
listed as diagnostic stops, never counted as output agreements.

Gate 1 does not certify full console timing. The deterministic profile advances one
issue clock per EE instruction, with VU dependency/interlock stalls. It does not
model EE dual issue, caches or every instruction's latency. Programs that depend
on non-interlocked races therefore remain outside validated execution. Unvalidated
COP0 register selectors and reserved VU control-register accesses still fault;
the retail COP0 transfers use the implemented selector-zero forms. Broader hardware
flag/timing validation remains useful. Decoder coverage alone is not a gate pass.
The EE number helpers implement finite exponent 255, denormal flushing,
one-bit adder alignment, the multiplier's discarded carry, and digit-recurrence
division/square root. Ordinary IEEE arithmetic with clamping is insufficient.

The self-check rebuilds/verifies the matching ELF, runs integer and floating
exact-source leaf controls on 32 synthetic states each, then compiles a positive control and
a changed source constant in the build backend. The positive must byte-match; the
mutation must produce a detected trace difference. These synthetic controls
cannot establish gameplay coverage or promote a function to `equivalent`.
Trace comparison is a foundation, not the Phase 3 ABI/stack-aware driver.

## Phase 2 inputs

Place private USA Black PCSX2 `.p2s` files in `orig/savestates/`. The in-memory
reader supports format `0x9a590000`, exercised on real v2.8.2 gameplay states.
The C++ bridge imports EE RAM, scratchpad, VU0 memories, hardware reads and
EE/FPU/TLB/VU0 registers. Active saved EE branches or VU0 pipelines and backend
FPU overflow state are rejected; they are never silently discarded. COP0 Random
is explicitly seeded when PCSX2's saved slot is outside Wired..47.

`phase2.py` calls the recovered frame dispatcher, separate world update and live
state virtual update and frame services using receivers from saved globals/vtables.
Roots are explicitly bootstrapped; descendant
entries are observed during original execution. The hardware profile performs
normal/interleaved scratchpad DMA using existing guest bytes, records/discards
output payloads, and delivers stub completions/vblank to original registered EE
handlers. It does not implement GS/VU1, a general kernel scheduler, or exact timing.
The recovered main-thread TCB/context supplies stack space when a state was saved
on the kernel stack. [ps2tek's EE threading layout](https://israpps.github.io/ps2tek/#bioseethreading)
documents these structures. Full dispatcher and isolated update counts remain
separate; unresolved device waits stop at the instruction budget.

The versioned `.eec` journal stores all register and pending pipeline/event state,
ordered memory deltas and changed hardware responses. Calls and cross-function
entries count; branches back to the same function's first word do not. Capture
mode streams complete ordered events, payloads and argument banks to
`.eec.events.gz`, retaining only bounded diagnostics in memory. Function replay
keeps its full comparison trace. `replay-entry` restores an
input and compares two deterministic original runs, reporting return/budget/fault
separately. Vtable scans retain candidate locations; a recorded receiver strengthens
that association. Fuzzing changes only recovered scalar fields, preserves pointers,
checks every memory preimage and records layout evidence. Fuzz cases do not count
toward naturally observed Gate 2 entries. No function is marked equivalent here.

Reports and all game material stay under ignored `build/`. Artifacts use input
hashes so new filenames cannot overwrite another state's corpus. Completed runs
are reused automatically; increasing a stopped run's budget recaptures it. Two
independent input workers are the default. Each finished input updates `gate-2.json`.

Current checkpoint: eight inputs, 238,062 saved entries, 1,841 game functions
reached and 1,429/6,512 at 20 states (3,257 required). Two inputs complete 40 full
dispatcher iterations each; other device waits remain. Of 1,745 typed mutations,
1,725 returned, 20 exhausted their budget and none faulted. Gate 2 remains open.

```sh
.venv/bin/python tools/eeharness/savestate_tests.py
.venv/bin/python tools/eeharness/corpus_tests.py
.venv/bin/python tools/eeharness/savestate.py --output build/eeharness/savestate-inputs.json
# Requires a built release harness (see above).
.venv/bin/python tools/eeharness/phase2.py --harness build/eeharness/release/eeharness --frames 40 --budget 16000000
# Reanalyze unchanged corpora without repeating their interpreter execution:
.venv/bin/python tools/eeharness/phase2.py --reuse-captures
# Replay a stored input (zero-based stream index):
build/eeharness/release/eeharness replay-entry SNAPSHOT.ees CORPUS.eec 1000 200000
```

Optional independent checks take private input snapshots rather than fetching
or linking any external implementation:

```sh
.venv/bin/python tools/eeharness/fpu_check.py --logs .local/eeharness-references
.venv/bin/python tools/eeharness/vu_check.py --logs .local/eeharness-references
.venv/bin/python tools/eeharness/micro_check.py --logs .local/eeharness-references
.venv/bin/python tools/eeharness/micro_check.py --logs .local/eeharness-references --via-ee
.venv/bin/python tools/eeharness/integer_check.py --logs .local/eeharness-references
.venv/bin/python tools/eeharness/compiled_check.py --logs .local/eeharness-references --budget 100000000
.venv/bin/python tools/eeharness/retail_micro_check.py
```

The FPU checker covers 901 published numerical cases and seven FCR31 situations.
With `--oracle EXECUTABLE`, it separately checks raw results against an external
PS2Float research executable, including random operands and exponent/sign edges.
The VU checker covers 106 published integer macro cases and flag preservation.
With all private inputs present, the micro checker covers 329 programs and 1,103
register observations: 671 published values and 432 flag-preservation checks with
authored initial flags. These include Q timing, clip history, immediate/integer
arithmetic, JALR aliasing, and 122 optional multiplier observations from
`vu-fobes-mul.expected`. The random-register observations were published for VU1;
the checker replays their common instruction semantics on VU0. Integer fixtures
retain the published setup's actual register construction, whose negative values
can differ from its printed operand labels. All cases also pass through EE
VCALLMS. The decoder audit
also checks all 842 instruction pairs in the three known retail VU0 uploads.
The integer checker covers 3,728 cases across 148 operations: scalar ALU and
multiply/divide, MMI arithmetic/comparison/logic/shuffle/multiply/divide, and funnel
operations. Scalar results check low 64 bits and independently check preservation
of the supplied upper half; packed results check all 128 bits and applicable HI/LO
banks. Published MTSA readbacks additionally constrain the observed four-bit value;
the manual only specifies restoring values previously saved with MFSA.
Reports bind input and executable hashes. Model agreement is not hardware proof,
and these checks do not constitute complete instruction or flag coverage.

The compiled checker executes the published MIPS test ELFs, including their
formatting code, with one explicitly bound stdout/stderr endpoint. Twenty complete
programs reproduce their published output over 64,189,222 instructions. Two
branch-in-delay-slot programs and one reserved VU-register test stop and remain
reported separately; the complete 23-program check therefore exits nonzero.
The configured fixture hardware ID is 0x2e30. This adapter is separate from game
replay. The retail micro check executes 42 synthetic cases over 21 entries in the
three uploaded images and checks full state/trace replay; it has no hardware
result oracle and contributes no gameplay coverage.

References for architectural facts, not implementation code:

- Sony [EE Core User's Manual v6.0](https://docs.alexrp.com/mips/ee.pdf), especially
  sections 8.1 and 8.7; [instruction set](https://docs.alexrp.com/mips/ee_insns.pdf)
  and [VU manual](https://docs.alexrp.com/mips/ee_vu.pdf).
- [PCSX2](https://github.com/PCSX2/pcsx2/tree/5b6e6e23eba403b589495c1abf8266eb1309a5b1/pcsx2),
  opcode tables and interpreter semantics. No reference code is copied into or linked with this interpreter.
- [PS2Float research](https://github.com/TellowKrinkle/PS2Float/tree/a5b2c0c80312e2582143fa801a25f4c4984fbe08)
  for independently modeled arithmetic circuits and the optional external oracle.
- [ps2autotests numerical result logs](https://github.com/unknownbrackets/ps2autotests/tree/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/ee_fpu)
  and [VU0 integer logs](https://github.com/unknownbrackets/ps2autotests/tree/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/vu0_macro)
  and [MMI logs](https://github.com/unknownbrackets/ps2autotests/tree/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/ee_simd)
  provide hardware expectations; the tests here are independently written.
- [Published VU multiplier observations](https://gist.github.com/F0bes/5f209d8a0890879ad0e25ceb6973977a)
  and their [hardware test description](https://fobes.dev/ps2/detecting-emu-vu-floats).
- [VU microprogram result logs](https://github.com/unknownbrackets/ps2autotests/tree/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/vu)
  for integer operations, common random-register instructions and the timing fixtures.
- PCSX2 [archive serialization](https://github.com/PCSX2/pcsx2/blob/5b6e6e23eba403b589495c1abf8266eb1309a5b1/pcsx2/SaveState.cpp),
  [EE/FPU register layouts](https://github.com/PCSX2/pcsx2/blob/5b6e6e23eba403b589495c1abf8266eb1309a5b1/pcsx2/R5900.h),
  and [VU member serialization](https://github.com/PCSX2/pcsx2/blob/5b6e6e23eba403b589495c1abf8266eb1309a5b1/pcsx2/VUmicroMem.cpp)
  document the prepared input reader's format profile.
