# Automatic pipeline

The m2c-based draft pipeline (`tools/autodecomp.py`), its context recovery and the shared PS2 helper headers.

## Pipeline

Shared PS2 inline helpers and target types live in [include/ps2/](include/ps2/README.md), owned by
the shared context maintainer. `config/shared_context.json` records the field/operation scope of
each exact consumer; `python3 tools/shared_context.py verify` checks actual header use, instruction
matches and the full image. Reuse these headers and preserve their helper order, widths and VU
spill recipes. Report shared changes to their owner; unverified layouts remain explicitly partial.

VU math study tools: `tools/studies/vu0_patterns.py` inventories recurring instruction/dataflow shapes;
`tools/vu0_micro.py` decodes conservative contracts keyed by uploaded image and entry address.
Their generated site lists belong under `build/`. Library labels inherited from the TU map are
qualified evidence, and overlapping shape counts are not additive. `tools/studies/verify_vu0_math.py`
checks isolated arithmetic windows; `config/vu0_math.json` promotes an operation only with two
complete exact source consumers. Full matrix/transpose and several normalization recipes remain
unverified. Animation's recurring fixed-VF macros have a separate header from allocatable `j` helpers.

For a targeted retry, select `users[].address` from the census with repeated `--addr` arguments and
run `AUTODECOMP_VU0=1 python3 tools/autodecomp.py run --redo --tu all ...` (game region first).
Use `AUTODECOMP_RESULTS=build/math-study/auto.json` to retain an independent experiment ledger.
This opt-in path models native 128-bit transfers, preserves live partial lanes and lowers a closed
subset to shared operations. Unknown upper lanes, flags, microcalls and open ACC/Q state still fail
explicitly; it does not invent a general VU library. Every accepted result still requires settlement
and an identical full link. Microcode stays binary; SN cannot express special-register clobbers, so
the documented micro/macro wrappers require hidden ACC/Q/I/flag state to be dead at their boundary.

Drafts C for assembly functions with no per-function judgment and keeps what rebuilds byte-identically. Setup, once:

```sh
.venv/bin/pip install -r requirements.txt            # m2c (pinned git commit), pycparser, toml
.venv/bin/python tools/autodecomp.py setup           # decomp-permuter at its pinned commit, into .venv/ (git clone)
```

m2c and the scoring run on the host (they only read and write text); every compile runs in the build backend, hundreds
of candidates per call (about 0.8 s latency per call, about 90 compiles per second). m2c's little-endian MIPS GCC target
is `-t mipsee-gcc-c` (with `--valid-syntax`, which turns unknown field accesses into `M2C_FIELD` macros, see
`include/auto/prelude.h`).

```sh
python3 tools/autodecomp.py run --max-size 100            # all assembly functions under 100 bytes -> build/auto.json
python3 tools/autodecomp.py rescore                     # revalidate saved drafts after shared headers change
python3 tools/autodecomp.py run --min-size 100 --max-size 300 --region game
python3 tools/autodecomp.py run --max-size 100 --status near --status mismatch --ctx ctx2.c --tag arity-int
python3 tools/autodecomp.py permute --max-score 8         # decomp-permuter on near misses (one member per family)
python3 tools/autodecomp.py family                        # clone exact sources onto identical-body functions
python3 tools/autodecomp.py register                      # exact drafts -> src/<library>/<tu>.c + config/units.yaml
python3 tools/autodecomp.py settle                        # compile, link, demote what cannot be placed, retry alone; ninja must say OK
python3 tools/autodecomp.py report [--max-size N]         # outcome classes, failure reasons
python3 tools/next.py [near|types|families|data|ee]       # best next work
```

Per function: (1) m2c on its `.s` (plus the sibling `.lit4.s`), with the recovered whole-callgraph context (`ctx.c`);
`ctx2.c` and `ctx3.c` retain scalar/pointer fallback variants; `ctx_void.c` tests unresolved scalar returns as void; (2) mechanical cleaning: missing leading parameters, K&R
declarations for callees, function-pointer globals, strings the function owns turned back into literals; (3) compile as
C named `func_XXXXXXXX` with `-O2 -G0 -snas`, plus `-G8` when the original addresses small data through `$gp`; on a miss
the flag set is varied (`-O1`, `-O3`, `-fbyte-bool`, `-G8`, `-fno-peephole`, `-fno-schedule-insns2`); (4) score: the
compiled `.text` is compared with the original words, relocated fields masked, and each relocation target (symbol address
plus addend; constants by their bytes) must equal the symbolic operand of the original assembly; (5) up to 8 differing
instructions: decomp-permuter's randomizer, a hill climb on the compile score, 50 candidates per function and round
compiled together in one worker call; (6) identical bodies (`family`): an exact source is cloned onto the members of its
family by renaming symbols; (7) functions m2c cannot read but that are a few special instructions (`li $v1, N; syscall`,
`ei`, `di`, `sync`) come from one inline-asm template.

Known HI16/LO16 address pairs also compare their complete encoded instructions, including signed-low
carry and REL addends. This handles a retail LUI shared by several addresses when only the compiled
object has a symbolic relocation. Unknown symbols and unpaired highs stay unresolved; no output bytes
are rewritten, and full-image equality remains the placement check.

`python3 tools/autodecomp.py context --refresh` exports both contexts and analyzes every function, matched C/C++ signatures, read-only Ghidra
snapshots and counterpart source leads. Normal `run` refreshes stale context automatically; `--refresh-context` forces
it. `build/auto/context.json` keeps evidence, unresolved arities and conflicts. Integer and floating argument banks are
independent on the EE. Caller counts and register-use constraints are lower bounds; the original order of mixed
parameters is unknown without a signature. Xbox types remain leads and never establish PS2 field offsets.

`include/recovered/` holds shared PS2 access views with field-offset assertions, plus a compile signature context.
Normal drafts include only the views they use, and worker jobs package their quoted-header dependencies. Overlapping,
unaligned or conflicting fields stay opaque. A view's extent is an accessed prefix, not an allocation-size assertion;
its UNVERIFIED mark changes only after a matched source function actually accesses members through that view.
`include/recovered/signatures.h` is a complete compile context for experiments; normal drafts declare referenced
callees individually so speculative signatures do not conflict with unrelated definitions. Re-run recovery after
settling to refresh verification marks. During parallel campaigns, `AUTODECOMP_FREEZE_CONTEXT=1` consumes the
centrally exported context without rewriting shared headers; a missing context is an error.

After `python3 tools/autodecomp.py context --refresh`, run `python3 tools/class_skeletons.py` to recover
the legacy GCC RTTI graph and vtables and write
`include/classes/` and an address/slot index in ignored build output. The generator is the sole owner
of these headers: put verified corrections in its evidence configuration and regenerate. RTTI names,
base links and virtual slots carry separate evidence from inferred signatures and field accesses.
Opaque prefixes and accessor offsets do not establish a complete object size. Xbox layouts remain
leads until PS2 code and an exact source match verify them. See `include/classes/README.md` for the
generated API and verification limits.

Type and instruction support, all of it mechanical and checked by exact matches:

- **Types.** `python3 tools/ghidra_types.py` writes `include/types_ghidra.h` from the raw Ghidra pages in `.local/ghidra/`
  (`structures_N.json`, one `get-structure-info` response per structure listed by `list-structures`, and the signatures in
  `config/symbols.txt`): 25 structures (the PS2 collision, game-object, Kynapse and AI/route types the Ghidra program holds)
  and 267 signatures under the image's `func_XXXXXXXX` names, with compile-time offset and size asserts. They are recovered
  guesses; each structure is marked `UNVERIFIED` until a matched function actually accesses its members.
  `ctx.c` combines these layouts with recovered signatures and access views; every draft includes the Ghidra header.
  `tools/m2c_wrap.py` is m2c with one change: a dereference of an untyped expression becomes `M2C_FIELD(expr, T *, 0)` (valid
  C) instead of `*expr`.
- **Stack objects.** m2c's frame objects (`sp`, `&spN`, `spN`) become one `u8 sp[N] __attribute__((aligned(16)))` buffer whose
  size is searched against the frame size; reads of an argument register the function never sets become `argN`.
- **EE instructions** (`tools/ee_prep.py`). SN GCC 2.95 for the EE has `long` = 64 bits and `long long` = 128 bits. `lq`/`sq`/
  `por rd, rs, $0` are `long long` loads, stores and moves; `ldl`+`ldr` / `sdl`+`sdr` pairs are 8-byte accesses at byte
  alignment (`struct { char c[8]; }` copies, packed members). The assembly shown to m2c has `ld`/`sd`/`daddu` instead, and
  its 64-bit types are turned into the 128-bit type (or `M2C_UNALIGNED64`) afterwards, but only when the function has no real
  64-bit access. Callee results and arguments of 128-bit type are found from the callee's code (`wide_info`) and enter the
  context as `s64`. `max.s`/`min.s` and MMI/VU0 instructions m2c cannot read are reported by instruction (`next.py ee`).
  The vector layer (`include/game/ai_vector.hpp`, compile with `-mvu0-use-vf0-vf31`) is the form SN accepts for them.
  `m2c_input.py` decodes EE `sqrt.s` (FT input, FS zero), including generic `c1` text.
  Direct roots use `mod/math/scalar.h` (C++ `ModMath::SquareRoot`); recognized libc
  `sqrtf` calls and errno-handling sequences retain their library semantics.
- **Tail calls and indexed globals.** m2c drops the delay-slot instruction of a `j func` tail call (an argument set there is lost):
  `ee_prep.py` puts it before the jump. m2c writes `&D_x + n` for byte arithmetic on a global of unknown type, which C scales by the
  size of `D_x`: `byte_addresses` makes such addresses integers and types the dereferences (`*(s32 *)(...)`). Together +22 functions.
- **Owned rodata** (`autodecomp.py rodata`). An exact draft that owns `.rodata` gets the run defined in its unit, as
  `const u32 rodata_XXXXXXXX[] __asm__("D_XXXXXXXX")` words or a `const char` string array laid out as the original run, and
  string literals point at the array. Then `register`/`settle` place it.
- **Families** (`family`). Exact sources are cloned onto the members of a family of identical bodies by renaming symbols (also
  for functions that own rodata); a template for a family is adopted with `autodecomp.py adopt ADDR file.c` and tried with
  `tools/trysrc.py ADDR file.c`.

An exact draft is only a candidate: `register` writes it as a unit (adjacent exact drafts are grouped, at most 24) and
`settle` uses `tools/settle_units.py` to demote whatever does not link identically; a demoted group is retried one function
per unit. Results and reasons (`verify-failed`: `size` = the function owns rodata that the source does not define, `extra`,
`layout`, `bytes`) are kept in `build/auto.json` (ignored). The drafts keep m2c's variable names (`temp_5`, `var_3`) and
`M2C_FIELD` accesses; they compile as C under the image's `func_XXXXXXXX` names, so assembly callers link unchanged, and
carry `origin: auto` in `config/units.yaml`. Later phases turn them into C++ methods once classes are known.
