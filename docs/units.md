# Source units

How source replaces assembly in the build (`config/units.yaml`, `tools/settle_units.py`).

## Units

A *unit* is a source file that replaces a run of adjacent functions of the image. List it in `config/units.yaml`
(the file is maintained by `tools/settle_units.py`; the format is described in `tools/units.py`):

```yaml
variant: usa-retail
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
objects; its other sections (unwind data in `.data`, vtables and inline copies in `.gnu.linkonce.*`) are not linked, and
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
Settlement protects the source addresses committed in `HEAD` and restores its input units file if a candidate causes
their demotion, so a placement error cannot silently discard earlier matches.
