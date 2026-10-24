# Source units

How source replaces assembly in the build (`config/units.yaml`, `tools/settle_units.py`).

## Units

A *unit* is a source file that replaces a run of adjacent functions of the image. List it in `config/units.yaml`
(the file is maintained by `tools/settle_units.py`; the format is described in `tools/units.py`):

```yaml
variant: SLUS_213.76
units:
- name: kynapse_leaf_2d15a0
  source: src/kynapse/leaf_functions_2d15a0.cpp
  origin: kynapse                    # kynapse | game | vector, for the progress report
  flags: [-O2, -G0, -snas, -fbyte-bool]
  externs: {gIdA: 0x44ecd0}          # name the code refers to but does not define -> original address
  functions:
  - {addr: 0x2d15a0, symbol: Kaim_AllIdsValid__Fv, size: 108, status: source}   # asm + reason: to keep the assembly
```

`symbol` is the exact mangled name the compiler emits; `make_ld.py` makes the image's `func_XXXXXXXX` name an alias of it,
so assembly callers link against the source. The unit's `.text` and its constants take the place of the functions'
objects; its other sections (unwind data in `.data`, vtables and inline copies in `.gnu.linkonce.*`) are not linked by default, and
global symbols they defined are bound to the originals through `externs`. Then:

```sh
python3 tools/settle_units.py      # compile every unit, demote what cannot be placed identically, relink until OK
ninja && ninja progress
```

`settle_units.py` uses `tools/units_verify.py`: `prepare` checks each object (symbol, size, extra code, constants it brings
that the original did not migrate, unbound externs), `link` demotes units the linker names, `compare` demotes the units
that own any differing word of the linked image. Reasons recorded in `config/units.yaml`: `extra` (the unit emits other
functions too), `name`, `size`, `section`, `shared`, `layout`, `extern`, `labels`, `link`, `bytes`, `compile`. Provenance
of the first sources: `tools/studies/import_kynapse.py` and `tools/studies/import_game.py` port the PS2-exact bodies of the companion project
(headers in `include/kynapse/`, `include/game/`, sources in `src/kynapse/`, `src/game/`; now under `tools/studies/`, they need the companion project and were run once). Diagnostic helpers:
`tools/objdump.py` (sections, symbols, relocations of an object), `BLACK_UNITS_ALL=1` (pretend every unit function is
source, to compile demoted units).

Text and owned data may end before their slot boundary when the actual next cached input section's alignment fills exactly that gap
and the original gap contains only zeros. This accepts natural linker alignment without changing the object or adding
instructions; the full-image comparison remains mandatory.
An absent owned-data section cannot stand in for a table or constant.
When one splat label combines an ordinary ASCIZ with adjacent runtime type data, a live unit may request
`rodata_type_splits: ['0x40a668']`. The boundary must be the next actual item after the complete first string and its
natural alignment, and begin a validated legacy GCC class name or standard exception name. This opt-in split preserves
all directives and recomputes references/ownership on each side; it does not claim the runtime tail for the first string's TU.
Settlement protects the source addresses committed in `HEAD` and restores its input units file if a candidate causes
their demotion, so a placement error cannot silently discard earlier matches.

## Full TU compiler context

With function sections, `full_tu_context: true` permits real unfinished function bodies to remain visible to the compiler.
Every emitted function must be a declared unit function or an explicitly listed `unlinked_context_helpers` symbol.
The latter list names reviewed algorithm helpers and makes no original-address or evidence claim. Only `status: source`
inputs are retained; all other allocated inputs receive discard-only names, and their globals resolve to the original
assembly definitions. This prevents an unrenamed `.text.*` input from leaking through the sorted output wildcard.
Native metadata may point to an assembly-backed function through a local section symbol. A kept `R_MIPS_32`
pointer to a uniquely named function entry is rebound to that function's existing global symbol. Interior,
ambiguous and non-function references remain unresolved; this does not replace metadata bytes or function extents.

Kept functions still require exact sizes, natural section tails, real callee bindings and the identical full image.
Unplaced function/constant relocations do not introduce dependencies. A kept call to an unplaced helper still requires
its actual original binding; the option cannot supply invented callees or discard constants referenced by kept code.
Without this opt-in, the existing extra-function rejection remains in force. Monolithic `.text` cannot use this option.

## Explicit source data

A live source unit can opt into storage using exact half-open ranges:

```yaml
data_ranges:
- {section: .data, input: .data.my_tu, start: '0x3ea768', end: '0x3ea7e8'}
- {section: .data, input: .data, start: '0x3c9364', end: '0x3c94a4', kind: unwind}
- {section: .bss, input: .bss, start: '0x4513d8', end: '0x4514f0'}
```

Supported output sections are `.data`, `.sdata`, `.rodata`, `.bss` and `.sbss`. `input` names the compiled section to retain.
Each input must fill its range completely, with the correct PROGBITS/NOBITS kind and compatible alignment. A NOBITS
input may leave a small natural tail only when the actual immediately following linked NOBITS input proves that alignment;
unknown inputs and larger gaps are rejected. Const initialized inputs may be read-only; the final ELF verifies output
permissions. Uninitialized inputs must remain writable. Ranges cannot overlap, and each edge must be an existing splat `dlabel` or the output section's end; the tool never cuts an item.
Explicit `.rodata` inputs must be complete read-only PROGBITS sections. Their ranges replace inferred constant migration
only at existing object labels; partial cuts through function-owned constant runs are rejected, and retained runs keep every item.
The optional `kind: unwind` permits an unlabeled edge only for a complete decoded original CIE/FDE group. The decoder
checks version, relative CIE backlinks, function extents and the terminator, then introduces split labels in build output.
It cannot authorize an arbitrary interior cut or a partial metadata record.
Use typed definitions and symbolic relocations. SN 1.36 emits a custom `.bss.name` attribute as PROGBITS; ordinary
uninitialized storage in `.bss` retains NOBITS. Inspect the object before declaring a range.

`split_objects.py` carves only opted-in sections; `make_ld.py` substitutes the named source input and preserves original
interior labels as section-relative aliases. Retained fragments split again at aligned labels when necessary to preserve
their original alignment phase. Unlisted sections retain their existing behavior. `units_verify.py` checks
the input and attributes data mismatches or missing interior labels to the owning unit. A full identical image is still
required. Owning these ranges does not establish semantic field names or prove the TU map's proposed data ownership.
Settlement refreshes placement before generating the linker script; direct linker generation requires current placement.

A `shared_exception_tables: ['0x...']` opt-in migrates an original exception-table object shared by several functions
only when every handler belongs to an exact source function in that same unit. The complete native compiler table must
still match. It neither cuts a record nor permits a table to cross unit boundaries.
