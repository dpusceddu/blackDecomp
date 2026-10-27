# Automatic pipeline

The m2c-based draft pipeline (`tools/autodecomp.py`), its context recovery and the shared PS2 helper headers.

## Pipeline

Shared PS2 inline helpers and target types live in [include/ps2/](../include/ps2/README.md). Reuse these headers and
preserve their helper order, widths and VU spill recipes; unverified layouts remain explicitly partial.

VU math: `tools/pipeline/vu0_micro.py` decodes conservative contracts keyed by uploaded image and entry address.
Their generated site lists belong under `build/`. Library labels inherited from the TU map are
qualified evidence, and overlapping shape counts are not additive. An
operation is promoted to a shared recipe only with two complete exact source consumers. Full matrix/transpose and several normalization recipes remain
unverified. Animation's recurring fixed-VF macros have a separate header from allocatable `j` helpers.

For a targeted retry, select `users[].address` from the inventory with repeated `--addr` arguments and
run `AUTODECOMP_VU0=1 python3 tools/autodecomp.py run --redo --tu all ...` (game region first).
Use `AUTODECOMP_RESULTS=build/math-study/auto.json` to retain an independent experiment ledger.
This opt-in path models native 128-bit transfers, preserves live partial lanes and lowers a closed
subset to shared operations. Unknown upper lanes, flags, microcalls and open ACC/Q state still fail
explicitly; it does not invent a general VU library. Every accepted result still requires `confirm`
and an identical full link. Microcode stays binary; SN cannot express special-register clobbers, so
the documented micro/macro wrappers require hidden ACC/Q/I/flag state to be dead at their boundary.

Drafts C for assembly functions with no per-function judgment and keeps what rebuilds byte-identically. Setup, once:

```sh
.venv/bin/pip install -r requirements.txt            # m2c (pinned git commit), pycparser, toml
.venv/bin/python tools/autodecomp.py setup           # decomp-permuter at its pinned commit, into .venv/ (git clone)
```

Drafting and scoring read and write text. Candidate compilation uses individual local toolchain invocations in the
Linux environment of the README. m2c's little-endian MIPS GCC target
is `-t mipsee-gcc-c` (with `--valid-syntax`, which turns unknown field accesses into `M2C_FIELD` macros, see
`include/ps2/prelude.h`).

```sh
python3 tools/autodecomp.py run --max-size 100            # all assembly functions under 100 bytes -> build/auto.json
python3 tools/autodecomp.py rescore                     # revalidate saved drafts after shared headers change
python3 tools/autodecomp.py run --min-size 100 --max-size 300 --region game
python3 tools/autodecomp.py run --max-size 100 --status near --status mismatch --ctx ctx2.c --tag arity-int
python3 tools/autodecomp.py permute --max-score 8         # decomp-permuter on near misses (one member per group of identical bodies)
python3 tools/autodecomp.py clone                         # clone exact sources onto identical-body functions
python3 tools/autodecomp.py register                      # exact drafts -> their TU files (the INCLUDE_ASM line is replaced)
python3 tools/autodecomp.py confirm                       # compile, link, put back the INCLUDE_ASM line of what does not place identically; ninja must say OK
python3 tools/autodecomp.py report [--max-size N]         # outcome classes, failure reasons
python3 tools/next.py [files|near|types|identical|data|ee]  # best next work (files: what to claim next)
```

### Using decomp-permuter directly

Use the project's import wrapper and upstream decomp-permuter's `permuter.py` in Linux, WSL 2, or the project container. Install
`cpp` in that environment (`apt install cpp` on Debian). `autodecomp.py setup` clones the pinned permuter into `.venv/`.
Prepare a target and its per-file settings, then import your draft:

```sh
python3 tools/permuter/prepare.py func_00105BC0
python3 tools/permuter/import.py --settings build/permuter/func_00105BC0.toml \
  src/game/ui/tu_105bc0.c build/permuter/func_00105BC0.s
python3 .venv/decomp-permuter/permuter.py build/permuter/nonmatchings/func_00105BC0 -j 2
```

`tools/permuter/cc.py --file <source>` reads the file's compiler, flags and assembler from `splits.yaml` for each candidate.
The generated import settings also select the owning file's target assembler and enable upstream's inline-assembly
literal handling. The wrapper keeps scalar typedef attributes in opaque compiler declarations with parser-only views,
and checks that `s128`, `u128`, `EeS128`, `EeU128` and other `mode(TI)` aliases are 16 bytes on every compile. Import must
parse and compile successfully before searching. It always uses `--no-prune` to retain those declarations and opaque
helper bodies. The automatic pipeline uses the same typedef protection. There is no project permuter service or
search supervisor. Upstream C++ parsing is a known limitation; unsupported C++/EE constructs may need an upstream
`PERM_IGNORE`/`PERM_PRETEND` parser view. Such a view must preserve the actual compiler input and ABI. Review improved
candidates, copy them into the TU, inspect objdiff, and require `ninja` to print `OK` before claiming a match.

Per function: (1) m2c on its `.s` (plus the sibling `.lit4.s`), with the recovered whole-callgraph context (`ctx.c`);
`ctx2.c` and `ctx3.c` retain scalar/pointer fallback variants; `ctx_void.c` tests unresolved scalar returns as void; (2) mechanical cleaning: missing leading parameters, K&R
declarations for callees, function-pointer globals, strings the function owns turned back into literals; (3) compile as
C named `func_XXXXXXXX` with `-O2 -G0 -snas`, plus `-G8` when the original addresses small data through `$gp`; on a miss
the flag set is varied (`-O1`, `-O3`, `-fbyte-bool`, `-G8`, `-fno-peephole`, `-fno-schedule-insns2`); (4) score: the
compiled `.text` is compared with the original words, relocated fields masked, and each relocation target (symbol address
plus addend; constants by their bytes) must equal the symbolic operand of the original assembly; (5) up to 8 differing
instructions: decomp-permuter's randomizer, a hill climb on the compile score, 50 candidates per function and round
compiled individually with the pinned toolchain; (6) identical bodies (`clone`): an exact source is cloned onto the other functions with the same body
by renaming symbols; (7) functions m2c cannot read but that are a few special instructions (`li $v1, N; syscall`,
`ei`, `di`, `sync`) come from one inline-asm template.

Known HI16/LO16 address pairs also compare their complete encoded instructions, including signed-low
carry and REL addends. This handles a retail LUI shared by several addresses when only the compiled
object has a symbolic relocation. Unknown symbols and unpaired highs stay unresolved; no output bytes
are rewritten, and full-image equality remains the placement check.

`python3 tools/autodecomp.py context --refresh` exports both contexts and analyzes every function, matched C/C++ signatures, the recovered
prototypes in `include/ps2/prototypes.h` and optional counterpart source leads. Normal `run` refreshes stale context automatically; `--refresh-context` forces
it. `build/auto/context.json` keeps evidence, unresolved arities and conflicts. Integer and floating argument banks are
independent on the EE. Caller counts and register-use constraints are lower bounds; the original order of mixed
parameters is unknown without a signature. Xbox types remain leads and never establish PS2 field offsets.

A recovered layout is a struct `Recovered_<Name>` whose fields are named after their PS2 offsets (`unk_30`, with `unk_4[45]` for a gap)
and cover the accessed prefix only, not the allocation size. A committed layout is ordinary source: it is defined in the one
source file that uses it, or, when several files share it, in a plainly named header under `include/<library>/` (the sources include
it by that name); once its owner class is known, fold it into the class header. There is no directory of generated views.
`python3 tools/autodecomp.py context --refresh` writes what the recovery infers from the executable and the committed sources to the
ignored `build/auto/` (`context.json` lists each layout's `verified_by` functions, `ctx.c` is the m2c context: the committed
`ps2/recovered_types.h` and `ps2/prototypes.h`, the recovered layouts and the recovered signatures). A draft that names a
`Recovered_<Name>` includes the committed header that defines it, or carries the recovered struct written out above the
function; it is a starting point for the layout you commit, never a replacement for it. Normal drafts declare referenced callees individually so
speculative signatures do not conflict with unrelated definitions. When several runs share a checkout,
`AUTODECOMP_FREEZE_CONTEXT=1` consumes the already exported context; a missing context is an error.

No tool rewrites a committed header: `decompile.py`, `autodecomp.py` and the build only write under `build/auto/` (the m2c
context: `context.json`, `ctx*.c`, `recovered_layouts.c`) from the committed headers, sources and configuration, which is all a
fresh checkout has. `python3 tools/maint/class_skeletons.py` (after `python3 tools/autodecomp.py context --refresh`) recovers the legacy GCC RTTI graph
and vtables and writes class skeletons and an address/slot index into the ignored `build/classes/`; the class views the sources
include (`include/game/classes/`, `include/kynapse/classes/`) are hand-edited headers that began as such skeletons. Verified ABI
evidence for the generator is in `config/SLUS_213.76/class_method_abi.json`. RTTI names,
base links and virtual slots carry separate evidence from inferred signatures and field accesses.
Opaque prefixes and accessor offsets do not establish a complete object size. Xbox layouts remain
leads until PS2 code and an exact source match verify them. See `include/game/classes/README.md` for the
API and verification limits.

Type and instruction support, all of it mechanical and checked by exact matches:

- **Types and signatures.** `include/ps2/recovered_types.h` holds 24 structures (the PS2 collision,
  game-object, Kynapse and AI/route types) with compile-time offset and size asserts, and `include/ps2/prototypes.h` 267 signatures
  under the image's `func_XXXXXXXX` names (the readable alias of each in a comment). Both are hand-maintained and recovered guesses:
  each structure is marked `UNVERIFIED` until a matched function actually accesses its members, and a prototype is only a weak
  declaration that a proved ABI correction (`selected_prototype`) or a matched definition overrides. `ctx.c` combines them with the
  recovered signatures and layouts; every draft includes `ps2/recovered_types.h`. Files that call a prototyped function include
  `ps2/prototypes.h`, which includes the types. `tools/pipeline/m2c_wrap.py` is m2c with one change: a dereference of an untyped expression
  becomes `M2C_FIELD(expr, T *, 0)` (valid C) instead of `*expr`.
- **Stack objects.** m2c's frame objects (`sp`, `&spN`, `spN`) become one `u8 sp[N] __attribute__((aligned(16)))` buffer whose
  size is searched against the frame size; reads of an argument register the function never sets become `argN`.
- **EE instructions** (`tools/pipeline/ee_prep.py`). SN GCC 2.95 for the EE has `long` = 64 bits and `long long` = 128 bits. `lq`/`sq`/
  `por rd, rs, $0` are `long long` loads, stores and moves; `ldl`+`ldr` / `sdl`+`sdr` pairs are 8-byte accesses at byte
  alignment (`struct { char c[8]; }` copies, packed members). The assembly shown to m2c has `ld`/`sd`/`daddu` instead, and
  its 64-bit types are turned into the 128-bit type (or `M2C_UNALIGNED64`) afterwards, but only when the function has no real
  64-bit access. Callee results and arguments of 128-bit type are found from the callee's code (`wide_info`) and enter the
  context as `s64`. `max.s`/`min.s` and MMI/VU0 instructions m2c cannot read are reported by instruction (`next.py ee`).
  The vector layer (`include/game/ai_vector.hpp`, compile with `-mvu0-use-vf0-vf31`) is the form SN accepts for them.
  `m2c_input.py` decodes EE `sqrt.s` (FT input, FS zero), including generic `c1` text.
  Direct roots use `game/math/scalar.h` (C++ `Math::SquareRoot`); recognized libc
  `sqrtf` calls and errno-handling sequences retain their library semantics.
- **Tail calls and indexed globals.** m2c drops the delay-slot instruction of a `j func` tail call (an argument set there is lost):
  `ee_prep.py` puts it before the jump. m2c writes `&D_x + n` for byte arithmetic on a global of unknown type, which C scales by the
  size of `D_x`: `byte_addresses` makes such addresses integers and types the dereferences (`*(s32 *)(...)`). Together +22 functions.
- **Owned rodata** (`autodecomp.py rodata`). An exact draft that owns `.rodata` gets the run defined in its unit, as
  `const u32 rodata_XXXXXXXX[] __asm__("D_XXXXXXXX")` words or a `const char` string array laid out as the original run, and
  string literals point at the array. Then `register`/`confirm` place it.
- **Identical bodies** (`clone`). Exact sources are cloned onto the other functions with the same body by renaming symbols (also
  for functions that own rodata); a template for such a group is adopted with `autodecomp.py adopt ADDR file.c` and tried with
  `tools/trysrc.py ADDR file.c`.

An exact draft is only a candidate: `register` replaces the function's INCLUDE_ASM line in its TU file by the draft
(`tools/pipeline/tu_files.py`; declarations go after the includes; a function compiled with other flags than its file, or whose group
failed, gets a small file of its own and a line in `config/SLUS_213.76/splits.yaml`, and its mangled name a line in
`symbols.txt`). `confirm` compiles and links, puts the marker back for whatever does not place identically, and retries a
failed file's new functions one per file. Results and reasons (`verify-failed`: `size` = the function owns rodata that the source does not define, `extra`,
`layout`, `bytes`) are kept in `build/auto.json` (ignored). The drafts keep m2c's variable names (`temp_5`, `var_3`) and
`M2C_FIELD` accesses; they compile as C under the image's `func_XXXXXXXX` names, so assembly callers link unchanged, and
are plain C in the TU files. Later phases turn them into C++ methods once classes are known.
