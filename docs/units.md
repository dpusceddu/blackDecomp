# Translation unit files and the split list

How source replaces assembly in the build. The inputs are `src/`, `config/SLUS_213.76/splits.yaml`, `symbols.txt` and
`equivalent.yaml`; nothing is generated into Git (`tools/build/units.py` derives the *units* into `build/`).

## One file per translation unit

`src/<library>/tu_<address>.c|cpp` (for the game library `src/game/<subsystem>/tu_<address>.c|cpp`, see
[src/game/README.md](../src/game/README.md)) lists every function of one translation unit (`config/tus.yaml`) in address order. A
recovered function is C or C++; the others are markers:

```c
#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100518);
void func_001005A0(void* arg0) { ... }               /* recovered */
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100628);

#ifdef NON_MATCHING
int func_001B78D8(BkEffectPoolPS2* pool) { ... }     /* draft, not exact yet */
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B78D8);
#endif
```

The marker names the function's assembly (`asm/SLUS_213.76/nonmatchings/func_XXXXXXXX.s`, written by the build). Every
function of the file's address range that has no marker must be defined by the file; the build checks that the compiled
function takes the original's place and that the whole image stays identical. A TU without recovered code needs no file.
Hand-written files keep descriptive names (`kynapse/behaviors_pathway.cpp`). Link-once copies (compiler-emitted inline and template
code) live in `src/<library>/inline/` ([build.md](build.md#link-once-copies)).

## The split list

`config/SLUS_213.76/splits.yaml`, one line per file (a TU is split into several files only where a reason is noted):

```yaml
defaults: {compiler: ee-gcc2.95.3-136, flags: [-O2, -G0, -snas], sections: true}
splits:
  - {src: src/game/unsorted/tu_100518.c, range: [0x100518, 0x103858]}
  - {src: src/game/ui/frontend_menu_notify.cpp, range: [0x103db0, 0x103df0], flags: [-O1, -G0, -snas]}
  - {src: src/physics/tu_32bc70.cpp, range: [0x32bc70, 0x32e3d0], flags: [-O2, -G8, -snas], assembler: sn-min6,
     owner: physics-scene, data_ranges: [...], full_tu_context: true, note: "..."}
```

`range` is `[start, end)`. `flags` and `compiler` replace the defaults; `assembler` names a per-unit assembler variant
(`sn-min6`, ... see [tus.md](tus.md)); `sections: false` compiles without `-ffunction-sections` (the compiled functions
must then be adjacent); `owner` marks who works on the file. A file that is compiled several times with `-D` selectors
and carries no markers lists its compiled addresses in `functions`. Rare keys keep the options of the old unit format
(`data_ranges`, `rodata_type_splits`, `shared_exception_tables`, `full_tu_context`, `unlinked_context_helpers`, `externs`).
A function that needs other flags than its neighbours gets its own file and entry. Two files may cover overlapping ranges;
the function is compiled by the file that does not mark it, and the other file keeps its marker.

## Names

`symbols.txt` (splat's `name = 0xADDRESS; // type:func`) holds the names a compiled function may carry (a mangled C++
name; otherwise `func_XXXXXXXX`) and the addresses of names the code uses without defining them (`gClock`, a callee in
another TU). Add a line when the build says a symbol has no address, or when a function is defined under its mangled name.
A line ending in `alias` (`// type:func alias`) is only a readable name and never affects the build
([build.md](build.md#symbols-and-progress)).

`equivalent.yaml` records the functions of the `equivalent` tier (14) with their evidence; they stay assembly.

## What the build does with it

`tools/build/units.py` reads the splits, scans each file's markers (`tools/build/include_asm.py`, which understands `#ifdef NON_MATCHING`
and `-D` flags) and writes `build/<GAME_ID>/units.json`. `tools/build/make_ld.py` places each compiled function (its own
`.text.<symbol>` section) at the slot of the original function and the file's constants at the first slot they replace;
`tools/build/units_verify.py prepare` checks every object (names, extra code, constants, unbound symbols) and writes
`unit_facts.json`; `link` and `compare` name the files and functions that do not link or differ. Reasons: `compile`, `name`,
`extra` (the object has code the original does not: a definition next to an INCLUDE_ASM line), `size`, `section`, `shared`,
`layout` (constants of the assembly functions in between interleave with the file's own), `extern`, `labels`, `link`, `bytes`.
Diagnostics: `tools/objdump.py`, `BLACK_UNITS_ALL=1` (pretend every listed function is source).

Text and owned data may end before their slot boundary when the next input section's alignment fills exactly that gap and
the original gap holds only zeros; the full-image comparison stays mandatory.

## Full TU context

With function sections, `full_tu_context: true` lets real unfinished function bodies stay visible to the compiler. Every
emitted function must be a function of the file or listed in `unlinked_context_helpers` (reviewed helpers, no claim about
originals); all other allocated inputs are discarded and their globals resolve to the original assembly. Kept functions
still require exact sizes, natural section tails, real callee bindings and the identical image.

## Explicit source data

A file can take over storage with exact half-open ranges:

```yaml
data_ranges: [{section: .data, input: .data.my_tu, start: '0x3ea768', end: '0x3ea7e8'},
              {section: .data, input: .data, start: '0x3c9364', end: '0x3c94a4', kind: unwind},
              {section: .bss, input: .bss, start: '0x4513d8', end: '0x4514f0'}]
```

Supported sections are `.data`, `.sdata`, `.rodata`, `.bss` and `.sbss`. Each input must fill its range completely with the
right PROGBITS/NOBITS kind; ranges cannot overlap and each edge must be an existing splat `dlabel`, except `kind: unwind`,
which accepts a complete decoded original CIE/FDE group. Use typed definitions; SN 1.36 emits a custom `.bss.name` attribute
as PROGBITS. `rodata_type_splits: ['0x40a668']` splits a label that combines an ASCIZ with adjacent runtime type data.
`shared_exception_tables: ['0x...']` takes over an exception table shared by several functions when every handler is a
function of the same file. A full identical image is required in every case.
