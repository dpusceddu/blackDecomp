# Progress reports (objdiff)

The headline "code" percentage is objdiff's definition, the one decomp.dev shows: bytes of matched functions / bytes of all
functions, with function sizes as objdiff measures them (up to the `endlabel`, no alignment padding, orphan pieces left
out). `ninja progress` computes it from the same extents as `tools/objdiff.py`, so `ninja badges` needs no objdiff-cli, and
its overall figure equals `ninja report`'s `matched_code / total_code` exactly. `ninja progress` also prints a secondary
measure, the image measure: bytes of the finished image, with alignment padding and orphan pieces included. It is the
ground-truth view of the rebuilt `.text`, not the headline.

## What is generated

```sh
python3 configure.py && ninja              # the build must print OK first
python3 tools/toolchain.py install --objdiff   # once: the pinned objdiff-cli, into build/toolchain/bin/ (macOS and Linux)
ninja objdiff                              # objdiff.json and the per-unit objects
ninja report                               # build/SLUS_213.76/report.json
```

The image is linked as one program, but objdiff compares objects. `tools/objdiff.py` therefore derives, for every source unit
in `config/SLUS_213.76/splits.yaml` that compiles at least one function, a pair of objects under `build/SLUS_213.76/objdiff/`:

- **target**: the original machine code of the unit's recovered functions (their split assembly, assembled again), symbols
  named `func_XXXXXXXX`;
- **base**: the object compiled from the unit's source, with its function symbols, references and `-ffunction-sections`
  section names renamed to the same `func_`/`D_` names.

A function belongs to exactly one unit: the one whose source compiles it. Functions that stay `INCLUDE_ASM` (also those inside a
source file that is partly recovered), and every function of a split that compiles nothing, get a target object only (one per
translation unit of `config/tus.yaml`, hidden from the objdiff sidebar), so the report covers the whole program and unrecovered
code counts as unmatched. Several splits of one file (`-D` selectors, overlapping ranges) are separate units, each with the
functions it compiles. Orphan pieces are left out. `objdiff.json` (project root, ignored by Git) lists all units with one
progress category per library. Source units apply to USA retail (`SLUS_213.76`) only.

objdiff compares symbol names, instructions and relocation types, so the two objects are normalized until a byte-identical
function also looks identical to it. Each rule exists because a function that `ninja progress` counts as exact was reported
as partly or not matching without it:

- **Sizes** stop at the function's `endlabel`; the alignment padding that follows is not code (the compiler's symbol size
  excludes it, and a trailing `nop` made every such function at most 99 % similar). A function with switch cases spans all its
  labelled fragments.
- **Names** of the base follow the address names even where the object also refers to the function (a function pointer in its
  own vtable), and the `-ffunction-sections` section follows its symbol (a mangled destructor name left in the section name
  made objdiff leave the pair unmatched).
- **ABI flags**: the EE assembler leaves the ABI field of the ELF header empty, the compiler sets EABI64, and objdiff names
  `$8`..`$11` `t0`..`t3` or `a4`..`a7` by it; the target takes the base's flags.
- **Data the unit owns** (a compiler-local `.rodata`/`.lit4` constant) gets a symbol at the original address name, so
  `%hi(D_003F7150)` in the original and `.rodata+0x8` in the object compare equal; `R_MIPS_LITERAL` relocations (compiler
  `.lit4` access) are retyped `R_MIPS_GPREL16` as in the split assembly.
- **Numeric names** such as `%lo(D_10F00)`, where the original holds a number and no relocation, are replaced by the number in
  the target.

`ninja report` runs `objdiff-cli report generate` and prints the totals. At the time of writing: 11,227 functions, of which
5,563 match (49.55 %), and 14.95 % of the code (401,428 of 2,685,060 bytes) matches; this is the headline. The image
measure counts the same 5,563 functions over all 11,899 functions and 2,715,464 bytes (15.11 %); it additionally holds the
672 orphan `<instruction>; nop` pieces (9,488 bytes) and the alignment padding behind functions (20,916 bytes in total,
8,956 of them behind recovered functions).

Agreement check: when `build/SLUS_213.76/report.json` exists and is not older than the build, `ninja progress` (and so
`ninja badges`) compares the set of exact functions (the image check: a split compiles them) with the functions objdiff
counts as 100 % matched, and also the report's `total_code`, `matched_code`, `total_functions` and `matched_functions` with
its own. Any difference stops with `AGREEMENT FAILED` and the functions on one side only; `progress.py --check` also fails
when there is no current report. A stale report is skipped with a note, so run `ninja report` after `ninja`.
Libraries in the table are by address (`tools/build/layout.py`; a link-once copy counts for its owner library, see [build.md](build.md#link-once-copies)); the report's categories attribute a matched function to the
library of its source file, so its per-category figures differ for functions compiled in another library's file (templates
placed in `src/<library>/inline/`), while the totals agree.

Other differences in what is measured:

- objdiff compares instructions and relocations, the image comparison compares bytes and placement, so a function could
  match here and still not be byte-exact in the image (data placement), and the other way round for constants that the
  compiler names differently. For this build the first case does not occur: every function that is exact is matched. The
  build's `OK` stays the authority for exactness.

When the numbers move apart again after a change to `tools/objdiff.py`, compare the per-function match percentages in
`report.json` with the functions `ninja progress` counts (`tools/build/units.py`, status `source`); a function that is exact in the
image but below 100 % in the report points at a normalization rule that is missing. `tests/tools/test_objdiff.py` covers
the unit and function mapping with a small split list.

To work on a function, open the repository root as an objdiff project (objdiff GUI: Project, Open), pick the unit and the
function, edit the source file, and objdiff rebuilds the unit's object and shows the diff. The build command in
`objdiff.json` is `tools/objdiff.py --build <object>`: it runs the incremental compile stage of `ninja` through the build
backend for the changed sources (seconds), then rebuilds that unit's two objects. Run `ninja objdiff` once after a full
`ninja` (and again when units are added) to create the objects and the project file.

## Publishing

The README badges and table are written by `ninja badges` (`tools/badges.py`) from the code measure of `ninja progress`,
which equals this report and needs no extra download. The files are committed under `progress/` and
served by shields.io from the repository. The objdiff report (`build/SLUS_213.76/report.json`) stays available for any
tool that reads it; CI does not generate one, because that needs the game executable.

decomp.dev no longer accepts new projects (it is being sunset), so this project is not registered there.
