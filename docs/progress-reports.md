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
in `config/units.yaml`, a pair of objects under `build/SLUS_213.76/objdiff/`:

- **target**: the original machine code of the unit's functions (their split assembly, assembled again), symbols named
  `func_XXXXXXXX` with their original sizes;
- **base**: the object compiled from the unit's source, with its function symbols and references renamed to the same
  `func_`/`D_` names.

Functions that no unit covers get a target object only (one per translation unit of `config/tus.yaml`, hidden from the
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

## Publishing a report

A maintainer uploads reports; CI does not, because generating one needs a finished build and therefore the game executable,
and uploading needs a secret. The repository workflows contain neither.

decomp.dev was the usual home for such reports (`https://decomp.dev/dpusceddu/blackDecomp` would be this project's page). Its
front page announces that the site is being sunset: existing projects continue to be served, but adding new projects is
disabled. If the project is not already registered there, reports cannot be uploaded today. The report format
(`build/SLUS_213.76/report.json`, objdiff's own) is not tied to the site: any tool that reads objdiff reports, or a plain
badge built from `measures.matched_code_percent`, can use it. For a site that accepts uploads, the steps are the same:

1. build with your own executable (`ninja`, then `ninja report`);
2. take `build/SLUS_213.76/report.json` and, for a site that wants versions, `objdiff.json` next to it;
3. upload it with the site's documented command or action, using a token that stays in your own environment (never in the
   repository or in a public workflow).
