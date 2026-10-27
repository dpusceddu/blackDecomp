# Contributing

This file is the rulebook for everyone, people and AI agents alike (agents also read [AGENTS.md](AGENTS.md)). A contribution
is a recovered function, a better type or name, a tool fix or documentation. You need your own copy of the game; set up the
build with the [README](README.md#get-started). Terms are in the [glossary](docs/glossary.md).

## Rules

- **Evidence.** A function is `exact` (compiled from source, and the whole image stays byte-identical) or a `draft` (a
  `NON_MATCHING` block). Never describe a function as more than its level, and never demote an exact function to gain another.
- **Validate according to impact.** For recovered source, compiler recipes or committed build inputs, check affected
  objects while iterating and require one full-image `ninja` check printing `OK` for USA retail (`SLUS_213.76`) before
  submitting the final changes for review. Intermediate commits do not require full-image builds. Fix integration failures
  and repeat the check as needed; run an earlier image build when diagnosing a concrete integration problem.
  Run `python3 tools/check_versions.py` (all five versions) when a
  change affects binary construction shared by the regional builds, such as binary splitting, section layout, assembly
  normalization or linking. Helper-only changes (pickers, scratch compilation, configuration writers), docs and tests do
  not need image rebuilds when they leave committed build inputs and the production build path unchanged; use focused
  regression tests and relevant tool checks instead. A file's location under `tools/build/` alone does not require rebuilds.
- **No shortcuts.** No filler, padding, byte patches or hand-written assembly to make something match. A per-file compiler
  flag or assembler in `config/SLUS_213.76/splits.yaml` needs a concrete reason in the native code, written in a `note:` on
  the entry; reject one that only makes a single function match by coincidence.
- **One owner per function.** Every function belongs to exactly one file (`python3 tools/where.py func_XXXXXXXX`). Claim a
  file before editing it and edit only what you claimed. Keep shared-header and `splits.yaml` changes small and review
  their affected consumers; include necessary headers and callers in a coherent change.
- **Drafts** go only in `#ifdef NON_MATCHING` above the function's `INCLUDE_ASM` line, with a one-line `// Unmatched:` note
  saying what differs; no `#if 0` blocks or other draft macros.
- **Only real work is committed**: source, drafts, headers, reviewed configuration, docs and tests. Never commit game
  data or anything generated from it (executables, disc contents, `asm/`, `build/`, `data/`, savestates, compilers, build
  output), nor `progress/` or the progress table of the README (`ninja badges` writes them after merging).
- **Names, prototypes, types and layouts are reviewed source inputs**: `config/SLUS_213.76/symbols.txt`,
  `include/ps2/prototypes.h`, `include/ps2/recovered_types.h`, `include/<library>/`. Names need evidence (see
  [Naming](#naming)); mark what no matched function confirms `UNVERIFIED`. Scripts may edit these inputs, but review
  their diffs; no unreviewed bulk edits or build dependencies on external analysis databases. Findings from Ghidra or IDA
  enter as edits to these files.
- **No machine-specific details** in committed text: host names, user names, absolute paths, addresses, credentials. Local
  settings go in `.local/` (ignored).
- **Style.** Format new C/C++ with `.clang-format`; avoid unrelated formatting churn and preserve compiler-sensitive structure.
  Source layout: `src/<library>/<name>.c|cpp` (`src/game/<subsystem>/` for game code, link-once copies in
  `src/<library>/inline/`), one file per TU listing every function; headers in `include/<library>/`. Tools are stdlib-first
  Python with a purpose docstring and `--help`. Docs stay short and current; no per-function proof journals.
- **Commits** are small, coherent and reviewable, with a clear message.

## Picking and claiming work

`python3 tools/next.py` lists the files to work on next: game code first, files with the most untried functions of
tractable size at the top, claimed files left out (`--pick` draws one of the best at random). The listing shows
both untried work and existing drafts. When both are available, `--pick` revisits drafts 20% of the time, preferring saved
near misses and smaller drafts; historical scores are leads to recheck. The objdiff unit list shows
sizes and match percentages; `python3 tools/next.py near|types|identical|data|ee` adds analyses objdiff does not show.
`python3 tools/brief.py <file>` prints what you need to start on a file: its compile recipe, recovered functions, earlier
drafts with their notes, and for each target its callers, callees, data, an m2c draft and its assembly.

### Claiming a file

A claim is an open pull request: the files it changes, plus the ones named on a `Claims:` line of its description, are
claimed. Open a draft pull request when you start (an empty commit is enough), with a line such as
`Claims: src/game/ai/tu_18c260.c`, and push as you go. `tools/next.py` skips claimed files, and files that your other local
worktrees change. If two pull requests claim the same file, the lower number keeps it (`python3 tools/next.py claims`). A
draft without updates for 48 hours lapses: push your work in progress, or comment, to keep it.

## The matching loop

Each translation unit (TU) is one file that lists the functions it owns in address order: recovered functions in C or C++,
the others as `INCLUDE_ASM` lines.

1. `python3 tools/setup.py` prepares metadata, assembly and `objdiff.json` without an image build. Open the repository root
   in the [objdiff](https://github.com/encounter/objdiff) GUI. Saving a TU file rebuilds its object and shows the diff;
   `ninja build/SLUS_213.76/objdiff/base/<unit>.o` does the same from the shell.
2. Inspect types, callee signatures and object lifetimes; the [matching handbook](docs/matching-handbook.md) has
   diagnostic recipes for common mismatches. A function's assembly is `asm/SLUS_213.76/nonmatchings/<file>/func_XXXXXXXX.s`.
3. Replace the `INCLUDE_ASM` line with C or C++. `python3 tools/decompile.py func_XXXXXXXX` prints an m2c draft with the
   project's context (`--write` puts it in place). For near misses, consider
   [decomp-permuter](docs/pipeline.md#using-decomp-permuter-directly) on the function, with seeds that leave out unrelated
   `INCLUDE_ASM` bodies.
4. Iterate with affected-object comparisons and commit small batches. Apply the [validation impact rule](#rules) before
   review; object matches remain candidates until the required image check passes.
5. A function that compiles under another name (a C++ method) needs a line in `symbols.txt`
   (`Reset__4Game = 0x1b78d8; // type:func`). Code that needs other flags than the rest of its file gets a file of its own
   (`python3 tools/split_function.py func_XXXXXXXX [--cpp] [--flags "..."]`, see [docs/units.md](docs/units.md)).
6. If it does not match yet, keep the draft:

   ```c
   #ifdef NON_MATCHING
   // Unmatched: loop scheduling differs.
   int func_001B78D8(BkEffectPoolPS2* pool) { ... }
   #else
   INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/<file>", func_001B78D8);
   #endif
   ```

   `python3 configure.py --non-matching` and `ninja` build all drafts into a separate executable (`python3 configure.py`
   goes back).

## Naming

Use names supported by evidence. RTTI names are original; aliases and descriptive names are working names, and Xbox names
are not PS2 facts. Keep address/offset placeholders until a better name is justified. Mark layouts or fields not confirmed
by matched code `UNVERIFIED`.

Renames must update definitions, callers, prototypes and affected bindings in `config/SLUS_213.76/symbols.txt` (ordered by
address), including C++ mangled names and assembly labels. The [naming reference](docs/naming.md) covers conventions and
worked examples. Validate according to the [impact rule](#rules).

## Cleanup work

Welcome under the [validation impact rule](#rules):

- **Readable C++ for automatic drafts.** Many matched game, Kynapse, animation and physics functions are plain C named
  `func_XXXXXXXX`, although those libraries are C++. Turning them into methods of known classes, with real names and types,
  makes the code useful (update `symbols.txt` for the new mangled name, see [Naming](#naming)). RenderWare, the Sony
  libraries and libc are C.
- **Real file names and directories.** Move a file into its `src/game/` subsystem when you learn what it is, rename it when
  the original name is known: `python3 tools/relocate_sources.py old new` moves the file and rewrites every mention of its
  path, including the `src:` entries in `splits.yaml` (`src/game/README.md` lists the directories).

## Checks and pull requests

Choose checks according to the [validation impact rule](#rules). Relevant commands:

```sh
ninja                                           # final full-image check: OK for SLUS_213.76
ninja progress                                  # final verified counts; compare with saved baseline units
python3 -m unittest discover -s tests           # build and linker tests
python3 -m unittest discover -s tests/tools     # tool tests
```

Tests need no game files. To inspect a build: `tools/diffelf.py REF BUILT` diffs two executables, `tools/objdump.py` prints
an object's sections, symbols and relocations, and the ordinary `mipsel-linux-gnu-objdump` works too.

Whoever opens a pull request is responsible for it: read the diff, run the checks, and say in the description how the change
was produced (by hand, with tools, or by an AI agent).

## Reference

- For everyone: [docs/status.md](docs/status.md) (state and open problems), [docs/matching-handbook.md](docs/matching-handbook.md),
  [docs/units.md](docs/units.md) (TU files and the split list), [docs/naming.md](docs/naming.md), [docs/glossary.md](docs/glossary.md),
  [docs/tools.md](docs/tools.md) (index of the tools), [docs/setup.md](docs/setup.md), [docs/modding.md](docs/modding.md).
- For maintainers and build work: [docs/build.md](docs/build.md), [docs/pipeline.md](docs/pipeline.md),
  [docs/tus.md](docs/tus.md), [docs/inputs.md](docs/inputs.md), [docs/progress-reports.md](docs/progress-reports.md),
  [docs/history.md](docs/history.md).

## License

By contributing you agree that your contribution is dedicated to the public domain under [CC0 1.0](LICENSE).
