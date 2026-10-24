# Contributing

Thank you for helping. The project reconstructs the source of the PS2 version of *Black*; a contribution is a recovered
function, a better type or name, a tool improvement or documentation. Read [README.md](README.md) first (setup and build) and
[docs/status.md](docs/status.md) (what exists, what is hard). You need your own copy of the game; nothing derived from it may
be committed.

## Picking work

- `python3 tools/next.py tus` lists candidate translation units (TUs); other views are `near` (functions a few instructions
  from matching), `types`, `families` (identical bodies), `data` and `ee` (vector and 128-bit code).
- `python3 tools/progress.py --tus 15` lists the partly recovered TUs closest to completion; `ninja progress` shows the whole
  picture.
- Small TUs with a single class or library function are the best first targets. Large functions (over 300 bytes), vector code
  and the Sony and RenderWare libraries are hard; the [open problems](docs/status.md#open-problems) say why.
- Open an issue or a draft pull request naming the TU before you start, so two people do not match the same file. An entry of
  `config/SLUS_213.76/splits.yaml` may carry an `owner` field for the same purpose; edit only the files you own.

## The matching workflow

Each translation unit (TU) is one file, `src/<library>/tu_<address>.c|cpp`, that lists every function of the TU in address
order. Recovered functions are C or C++; the others are `INCLUDE_ASM` lines.

1. Read the [matching handbook](docs/matching-handbook.md) before each TU: measured recipes for the usual obstructions and
   the order in which to try things. Types, callee signatures and object lifetimes explain most mismatches. The assembly of a
   function is `asm/SLUS_213.76/nonmatchings/func_XXXXXXXX.s` after the first `ninja`.
2. Replace the function's `INCLUDE_ASM` line with your C or C++ and run `ninja`. It ends with `OK`, or with
   `MISMATCH src/game/tu_100258.c: func_00100258: differs from the original` (compile errors name the file too). Drafts come
   from `python3 tools/autodecomp.py run ...` ([docs/pipeline.md](docs/pipeline.md)), or write the source by hand and try one
   function with `python3 tools/trysrc.py ADDR file.c`; `autodecomp.py register` then `settle` put exact drafts into their TU files.
3. If it does not match yet, keep the readable version under `#ifdef NON_MATCHING` with the marker as the `#else` branch, and a
   one-line `// Unmatched:` comment saying what differs. `python3 configure.py --non-matching` followed by `ninja` builds all
   drafts into a separate, non-matching executable (`python3 configure.py` goes back):

   ```c
   #ifdef NON_MATCHING
   // Unmatched: loop scheduling differs.
   int func_001B78D8(BkEffectPoolPS2* pool) { ... }
   #else
   INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B78D8);
   #endif
   ```
4. A function that compiles under another name (a C++ method) needs one line in `config/SLUS_213.76/symbols.txt`
   (`Reset__4Game = 0x1b78d8; // type:func`); code that needs other compiler flags than the rest of its file gets a file of its
   own and an entry in `splits.yaml` (see [docs/units.md](docs/units.md)); a name the code uses without defining also goes in
   `symbols.txt`. A normal contribution edits one source file and at most one `splits.yaml` entry and `symbols.txt` line.
5. Run `ninja`, `ninja progress` and the tests (below). If the change moves progress, run `ninja badges` and commit
   `progress/` (and the table it refreshes in `README.md`) with it.

Example: `func_00100258` is `return arg0;`. In `src/game/tu_100258.c` the line `INCLUDE_ASM("asm/SLUS_213.76/nonmatchings",
func_00100258);` becomes `s32 func_00100258(s32 arg0) { return arg0; }`; `ninja` says `OK` and `ninja progress` counts one
more function.

Evidence tiers matter: never describe a function as more than its tier (`exact`, `equivalent`, `draft`).

## Commit rules

- **The build stays identical.** Every commit leaves `ninja` printing `OK` for USA retail (`SLUS_213.76`), the only version
  routine work builds and checks. The other four versions are rebuilt from assembly; run `python3 tools/check_versions.py`
  (all five, `OK` or `MISMATCH` each) before a release and after changing shared build tools, linker or splitting code. `ninja progress` must not regress: never demote a previously exact function to claim a gain.
- **Never commit game data**: no executables, disc contents, extracted files, generated assembly (`asm/`, `build/`, `data/`),
  savestates, compiler archives or build output. They live in ignored directories. Generated headers and data are committed
  only when a tool in `tools/` owns and can regenerate them.
- **Keep committed text free of machine-specific details**: host names, user names, absolute paths, network addresses and
  credentials. Local settings go in `.local/` (ignored).
- Small logical commits with a clear message (what and why). One TU or one tool change per commit is ideal.
- Keep documentation short and current; update the relevant file in `docs/` when behavior changes.

## Cleanup work

Matching is not the only useful contribution. Two kinds of cleanup are always welcome, as long as `ninja` still prints `OK`:

- **Readable C++ for automatic drafts.** Many matched game, Kynapse, animation and physics functions are plain C named
  `func_XXXXXXXX`, as the decompiler produced them, although those libraries are C++. Turning them into methods of known
  classes (`include/<library>/classes/`), with real names, types and parameter names, makes the code useful. The mangled
  name changes with the declaration: update `config/SLUS_213.76/symbols.txt` so assembly callers still link. RenderWare,
  the Sony libraries and libc are C, so C is correct there.
- **Real file names.** Files are named `tu_<address>` until evidence shows the original name or class (strings, RTTI,
  class ownership). Rename with `git mv` and update the `src:` path in `splits.yaml`.

## Tests

```sh
python3 -m unittest discover -s tests          # build and linker tests
python3 -m unittest discover -s tests/tools    # tool tests
```

Tests need no game files; those that would need private inputs skip. CI runs both, checks that every tool answers `--help`, and
(informationally) compiles a trivial file with the pinned toolchain.

## Code style

- Format new C/C++ with the repository's `.clang-format` (4-space indents, attached braces, `T* p`, 120 columns). Do not
  reformat existing files: matching depends on exact source shape, and unrelated whitespace changes make review harder.
- Source layout: `src/<library>/<name>.c|cpp`, one file per TU with every function of the TU (INCLUDE_ASM lines, drafts in
  `#ifdef NON_MATCHING` blocks). Headers follow the libraries (`include/<library>/`, shared helpers in `include/ps2/`).
  `tools/layout.py` has the naming rules.
- Name functions and types after what the code does only where the evidence supports it; unknown functions stay
  `func_XXXXXXXX`. Mark field offsets that are only accessed, not understood, as such (`UNVERIFIED`).
- Python tools: stdlib first, a purpose docstring and `--help` for every tool, no machine-specific paths.
- Do not push generated or private artifacts; do not add dependencies without a reason.

## Using AI assistants

Automated contributors follow the same rules; see [AGENTS.md](AGENTS.md). Whoever opens the pull request is responsible for
it: read the diff, run the build and say in the description how the change was produced.

## License

By contributing you agree that your contribution is dedicated to the public domain under [CC0 1.0](LICENSE).
