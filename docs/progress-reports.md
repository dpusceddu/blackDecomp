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

Every source object has one comparison pair under `build/SLUS_213.76/objdiff/`: the target contains all its original
functions, and the base contains its recovered functions. The linked object contains the actual INCLUDE_ASM code as well;
only the comparison base removes it. Even a file consisting entirely of INCLUDE_ASM has a visible unit, so the sidebar's
sizes and match percentages cover the work still to do. Files with several ranges remain one unit. Orphan pieces are
excluded. The nine progress categories use the source library names.

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

`ninja report` runs `objdiff-cli report generate` and prints the totals; they are the headline figures of the README table
(written by `ninja badges`, which fails if they disagree with a current report). A *function* there is what objdiff counts: the
orphan `<instruction>; nop` pieces between functions are not functions, and *code* is matched function bytes over total
function bytes, without alignment padding. The image measure of `ninja progress` counts the same matched functions over all
function starts of the image, including the orphan pieces, and the bytes between function starts, including padding; it is the
smaller number's cousin and is only ever quoted as the image measure.

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
function, edit the source file, and objdiff rebuilds the unit's object and shows the diff. The build command is `ninja build/SLUS_213.76/objdiff/base/<unit>.o`: one object and its comparison view, without a
full link or size check. Run `ninja objdiff` to prepare the project. An ignored `.local/objdiff.json` can override
`custom_make` and `custom_args`; the default is ordinary Ninja.

## Publishing

The README badges and table are written by `ninja badges` (`tools/badges.py`) from the code measure of `ninja progress`,
which equals this report and needs no extra download. The two badge files are committed under `progress/` and
served by shields.io from the repository (the per-library badges go to the ignored `build/SLUS_213.76/badges/`). The objdiff report (`build/SLUS_213.76/report.json`) stays available for any
tool that reads it.

As of 2026-10 decomp.dev does not accept new projects, so this project is not registered there.
