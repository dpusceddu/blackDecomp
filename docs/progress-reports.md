# Progress reports (objdiff)

`ninja progress` reports how much of `.text` is provided by source, measured on the finished image. The objdiff report
measures the same recovery per function, in the format the matching-decompilation tooling understands.

## What is generated

```sh
python3 configure.py && ninja              # the build must print OK first
python3 tools/toolchain.py install --objdiff   # once: the pinned objdiff-cli, into build/toolchain/bin/ (macOS and Linux)
ninja objdiff                              # objdiff.json and the per-unit objects
ninja report                               # build/SLUS_213.76/report.json
```

The image is linked as one program, but objdiff compares objects. `tools/objdiff.py` therefore derives, for every source unit
in `config/SLUS_213.76/splits.yaml`, a pair of objects under `build/SLUS_213.76/objdiff/`:

- **target**: the original machine code of the unit's functions (their split assembly, assembled again), symbols named
  `func_XXXXXXXX` with their original sizes;
- **base**: the object compiled from the unit's source, with its function symbols and references renamed to the same
  `func_`/`D_` names.

Functions that no split compiles get a target object only (one per translation unit of `config/tus.yaml`, hidden from the
objdiff sidebar), so the report covers the whole program and unrecovered code counts as unmatched. Orphan pieces are left out.
`objdiff.json` (project root, ignored by Git) lists all units with one progress category per library. Source units apply to
USA retail (`SLUS_213.76`) only.

`ninja report` runs `objdiff-cli report generate` and prints the totals. For orientation, the numbers at the time of writing
were 11,233 functions of which 5,547 match, and 14.76 % of the code matched (`ninja progress` counts 5,563 exact functions and
15.11 % of the bytes, because it also counts the orphan pieces and compares the whole image). The two disagree in details
(constants named differently by the compiler, interior data references), never in direction. The build's `OK` stays the
authority for exactness.

To look at a function, open the repository root as an objdiff project (objdiff GUI: Project, Open). Build objects are not
rebuilt by objdiff; re-run `ninja objdiff` after a change.

## Publishing

The README badges and table are written by `ninja badges` (`tools/badges.py`) from `ninja progress`, not from this report:
that metric is exact, covers the whole image and needs no extra download. The files are committed under `progress/` and
served by shields.io from the repository. The objdiff report (`build/SLUS_213.76/report.json`) stays available for any
tool that reads it; CI does not generate one, because that needs the game executable.

decomp.dev no longer accepts new projects (it is being sunset), so this project is not registered there.
