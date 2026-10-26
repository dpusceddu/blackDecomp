# Contributing

Thank you for helping. The project reconstructs the source of the PS2 version of *Black*; a contribution is a recovered
function, a better type or name, a tool improvement or documentation. Read [README.md](README.md) first (setup and build) and
[docs/status.md](docs/status.md) (what exists, what is hard). You need your own copy of the game; nothing derived from it may
be committed. Terms are in the [glossary](docs/glossary.md).

## Picking work

`python3 tools/next.py` lists the files to work on next: game code first, files with the most untried functions of
tractable size at the top, claimed files left out. The objdiff unit list shows unit sizes and match percentages, and
`python3 tools/next.py near|types|identical|data|ee` adds analyses objdiff does not show (near-miss causes, missing types,
identical bodies, owned-data obstacles, unsupported EE instructions). Claim the file before editing it.

### Claiming a file

A claim is an open pull request: the files it changes, plus the ones named on a `Claims:` line of its description, are
claimed. Open a draft pull request when you start (an empty commit is enough), with a line such as
`Claims: src/game/ai/tu_18c260.c`, and push as you go; `tools/next.py` skips claimed files for everyone, and also files that
your other local worktrees change, so several sessions on one machine do not collide. If two pull requests claim the same
file, the lower number keeps it (`python3 tools/next.py claims` lists such files). A draft without updates for 48 hours
lapses: push your work in progress, or comment, to keep it. Edit only the files you claimed; shared headers (`include/ps2/`) and `config/SLUS_213.76/splits.yaml` are small,
reviewed changes. Pull requests do not touch `progress/` or the progress table of the README (see Commit rules).

## The matching workflow

Each translation unit (TU) is one file, `src/<library>/tu_<address>.c|cpp`, that lists the functions it owns in address
order. Recovered functions are C or C++; the others are `INCLUDE_ASM` lines. Every function is listed in exactly one file:
`python3 tools/where.py func_XXXXXXXX` prints the file and the line, with no game files or build needed.

0. Setup for the loop: `ninja` once, then `ninja objdiff`, and open the repository root in the
   [objdiff](https://github.com/encounter/objdiff) GUI. Pick the unit and the function; every time you save the TU file objdiff
   runs the unit's single-object Ninja target and shows the diff. `ninja` remains the
   byte-exact check of the whole image.
1. Read the [matching handbook](docs/matching-handbook.md) before each TU: measured recipes for the usual obstructions and
   the order in which to try things. Types, callee signatures and object lifetimes explain most mismatches. The assembly of a
   function is `asm/SLUS_213.76/nonmatchings/<file>/func_XXXXXXXX.s` after the first `ninja`.
2. Replace the function's `INCLUDE_ASM` line with your C or C++ and run `ninja`. It ends with `OK`, or with
   `MISMATCH src/game/unsorted/tu_100258.c: func_00100258: differs from the original` (compile errors name the file too). A first
   draft: `python3 tools/decompile.py func_00100258` prints an m2c draft (with the project's context) and the file and line
   it belongs to; `--write` replaces the `INCLUDE_ASM` line in place, and you then edit and rebuild. For many functions at
   once, `python3 tools/autodecomp.py run ...` ([docs/pipeline.md](docs/pipeline.md)); to try one hand-written function without
   editing the TU, `python3 tools/trysrc.py ADDR file.c`. When a few instructions differ, run
   [decomp-permuter](docs/pipeline.md#using-decomp-permuter-directly) on the function directly.
3. If it does not match yet, keep the readable version under `#ifdef NON_MATCHING` with the marker as the `#else` branch, and a
   one-line `// Unmatched:` comment saying what differs. `python3 configure.py --non-matching` followed by `ninja` builds all
   drafts into a separate, non-matching executable (`python3 configure.py` goes back):

   ```c
   #ifdef NON_MATCHING
   // Unmatched: loop scheduling differs.
   int func_001B78D8(BkEffectPoolPS2* pool) { ... }
   #else
   INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/<file>", func_001B78D8);
   #endif
   ```
4. A function that compiles under another name (a C++ method) needs one line in `config/SLUS_213.76/symbols.txt`
   (`Reset__4Game = 0x1b78d8; // type:func`); code that needs other compiler flags than the rest of its file gets a file of its
   own and an entry in `splits.yaml` (`python3 tools/split_function.py func_XXXXXXXX [--cpp] [--flags "-O1 -G0 -snas"]` does both;
   see [docs/units.md](docs/units.md)); a name the code uses without defining also goes in
   `symbols.txt`. A readable name that is not a definition is an alias line (`Reset = 0x1b78d8; // type:func alias`): it
   never changes the build ([docs/build.md](docs/build.md#symbols-and-progress)). A normal contribution edits one source file
   and at most one `splits.yaml` entry and `symbols.txt` line.
5. Run `ninja`, `ninja progress` and the tests (below). Do not commit `progress/` or the table in `README.md`, even when your
   change moves the numbers: they are generated (`ninja badges`) and the maintainer regenerates them after merging, so that
   pull requests never conflict on them. Put the before/after numbers of `ninja progress` in the pull request description.

Example: edit `func_00201960` directly in its existing file. It loads two fields and calls a function; no file split is
needed. Start with a clean working tree, and save the exact file before the experiment:

```sh
python3 tools/where.py func_00201960
cp src/game/unsorted/tu_1fcd90_201518.c build/example.before.c
python3 tools/decompile.py func_00201960 --write
ninja build/SLUS_213.76/objdiff/base/tu_1fcd90_201518.o
# Inspect the function in the objdiff GUI, then:
ninja
cp build/example.before.c src/game/unsorted/tu_1fcd90_201518.c
ninja
rm build/example.before.c
```

An unfinished edit can have a different size: objdiff still builds its object. The full-image check prints, for example,
`func_00201960: size differs (40 bytes, original 32)` and an instruction diff. Commit an unfinished body under
`#ifdef NON_MATCHING` with the INCLUDE_ASM alternative, as above. Restore only your experiment's file when reverting.

Evidence matters: a function is `exact` (the whole image stays byte-identical) or a `draft` (a `NON_MATCHING` block); never
describe a function as more than that.

## Naming

Placeholders are named after an address (`func_00100258`, `D_0040F0E0`, `unk_10`; see the [glossary](docs/glossary.md)). A better
name is a normal contribution, but only where the evidence supports it; the build must still print `OK`. The examples below were
each tried on a scratch copy of the repository and give an identical build. Names are inside the compiler's symbols, so a
rename that is not just a local variable touches `config/SLUS_213.76/symbols.txt`; keep that file ordered by address.

### Where names come from

1. **RTTI**: the executable names the classes that have run-time type information (the `Kaim::` classes and a few others) and
   their base classes. These names are original; use them as they are (`Kaim::CBrain`). `ninja classes` writes the full list
   with the virtual tables into the ignored `build/classes/`.
2. **Aliases**: readable names found by analysis (`Name = 0x...; // type:func alias` in `symbols.txt`). They are working names,
   not original ones, and never change the build.
3. **Placeholders**: `func_<address>`, `D_<address>` and `unk_<offset>`, plus two generated ones: `UnknownVtable_<address>` for a
   class known only by its virtual table (no type-info name; the class view lives in `include/game/classes/` under that name) and
   `Function_<address>` for an unnamed virtual method in a generated class view. They are kept until a better name is justified.
4. **Descriptive names** we choose for classes and namespaces that have no original name: plain English for what the code does
   (`Weapons`, `WorldObjects`, `HideAgent`), never prefixed with `Mod`, `Campaign` or `Black`, and namespaces that hold only
   partial layouts end in `Views`. Names such as `Fragment34FE10` or `KaimAvoidance` are scopes local to one file or group of files, not
   class names. Do not take a name from the Xbox build as if it were a PS2 fact.

### A readable name for a C function

`func_00367460` is the BIOS call that sets the GS video mode, and `symbols.txt` has it as an alias. To make `SetGsCrt` the real
name, rename the definition, turn the alias line into a bound-name line (drop `alias`) and update the prototype:

```sh
sed -i 's/^void func_00367460(void) {/void SetGsCrt(void) {/' src/sony/tu_367450.c
sed -i 's|^SetGsCrt = 0x367460; // type:func alias|SetGsCrt = 0x367460; // type:func|' config/SLUS_213.76/symbols.txt
sed -i 's|^extern void func_00367460(void); /\* SetGsCrt \*/|extern void SetGsCrt(void);|' include/ps2/prototypes.h
ninja        # OK; assembly callers of func_00367460 still link, because the bound name is the address's name
```

A name used by other source files must be renamed there too (`grep -rn func_00367460 src include`).

### A C++ method

`func_002D5368` is a getter of the hide behaviour in `src/kynapse/hide_agent_2d3c90.cpp`; HideAgent is a class view in
`include/kynapse/hide_agent.hpp`. Make it a method of the class: declare it in the class, define it with the class name, and bind
the mangled name to the address.

```cpp
// include/kynapse/hide_agent.hpp, in struct HideAgent (namespace HideViews):
const Vec3* CurrentPosition();

// src/kynapse/hide_agent_2d3c90.cpp, in place of  extern "C" const Vec3 *func_002D5368(HideAgent *self) { ... }
namespace HideViews {
    const Vec3 *HideAgent::CurrentPosition() {
        if (found) { if (fresh) return &destination; }
        return &context->actor->position;
    }
}
```

```
# config/SLUS_213.76/symbols.txt: GCC 2.95 mangling is  Method__<class path>  with <len><name> for each part,
# Q<n> for a nested path:  HideViews::HideAgent::CurrentPosition()  ->  CurrentPosition__Q29HideViews9HideAgent
CurrentPosition__Q29HideViews9HideAgent = 0x2D5368; // type:func
```

A method of a class in the global namespace is `Method__<len>Class` (`Reset__4Game`), a `const` method has `C` before the class
(`Head__C10RouteQueue`), parameters follow the class (`i`, `f`, `Pv`, `P<len>Name`). If the binding is wrong, `ninja` reports `func_002D5368: no definition in object`. Inspect the compiled object
with `python3 tools/objdump.py build/SLUS_213.76/obj/units/<unit>.o` and put its actual mangled name in `symbols.txt`. `python3 tools/where.py func_002D5368` finds the definition afterwards (it also understands
`Class::Method`).

### A type or struct rename with unk_ fields

A recovered layout is a `Recovered_<Name>` struct with `unk_XX` fields named after the PS2 offset (`unk_118` is the field at
0x118). When the class is known, drop the prefix and name the fields you understand; leave the others as they are:

```sh
grep -rn "Recovered_AnimationParameterBank\|unk_118" src include          # every use
sed -i 's/Recovered_AnimationParameterBank/AnimationParameterBank/g; s/unk_118/activeCount/g' src/animation/tu_350140.c
ninja        # OK
```

Renaming changes no bytes in C. For a C++ class or namespace it changes the mangled symbols that contain its name (the length
prefix too: `Q29HideViews9HideAgent` becomes `Q210SearchView9HideAgent`), so search `symbols.txt` and the `__asm__("...")` labels
for the old name and rewrite them together with the length. Mark a field `UNVERIFIED` when no matched function uses it.

### Moving a file into a subsystem directory

New game files start in `src/game/unsorted/`; move one when you learn what it is (`src/game/README.md` lists the directories):

```sh
python3 tools/relocate_sources.py src/game/unsorted/tu_153058.c src/game/ai/tu_153058.c
ninja        # OK
```

The tool does the `git mv` and rewrites the `src:` paths of every split entry of the file and every other mention of the path
(documentation, headers, comments); `--dry-run` only counts. For several files give it a file of `old new` pairs instead.

## Commit rules

- **The build stays identical.** Every commit leaves `ninja` printing `OK` for USA retail (`SLUS_213.76`), the only version
  routine work builds and checks. The other four versions are rebuilt from assembly; run `python3 tools/check_versions.py`
  (all five, `OK` or `MISMATCH` each) before a release and after changing shared build tools, linker or splitting code. `ninja progress` must not regress: never demote a previously exact function to claim a gain.
- **Never commit game data**: no executables, disc contents, extracted files, generated assembly (`asm/`, `build/`, `data/`),
  savestates, compiler archives or build output. They live in ignored directories. Only real work is committed: what the executable plus the
  committed sources and configuration determine is generated into `build/` and not committed (`config/README.md`).
- **Names, prototypes, types and layouts are ordinary source.** `config/SLUS_213.76/symbols.txt`, `include/ps2/prototypes.h`,
  `include/ps2/recovered_types.h` and the headers under `include/<library>/` are edited by hand and reviewed like code. A recovered layout is a
  `Recovered_<Name>` struct with `unk_XX` fields (named after the PS2 offset) for the accessed prefix of an object: define it in the one
  source file that uses it, or in a plainly named header when several files do, and fold it into the class header once the class is known; mark what is not
  confirmed by a matched function `UNVERIFIED`. No tool or test needs data from outside the repository. If you analyse the
  executable with Ghidra, IDA or another disassembler, that is your own tool: put what you learn into these files.
- **Keep committed text free of machine-specific details**: host names, user names, absolute paths, network addresses and
  credentials. Local settings go in `.local/` (ignored).
- Small logical commits with a clear message (what and why). One TU or one tool change per commit is ideal.
- Keep documentation short and current; update the relevant file in `docs/` when behavior changes.

## Checking and inspecting a build

`ninja` ends with `tools/check_elf.py`, which compares the rebuilt executable with the expected hashes and names the
functions that differ. `tools/diffelf.py REF BUILT` diffs two executables section by section and `tools/objdump.py` prints
the sections, symbols and relocations of an object file; they are conveniences, not requirements. The ordinary binutils work
on the same files: `mipsel-linux-gnu-objdump -d` and `mipsel-linux-gnu-readelf` (package `binutils-mipsel-linux-gnu`).

## Cleanup work

Matching is not the only useful contribution. Two kinds of cleanup are always welcome, as long as `ninja` still prints `OK`:

- **Readable C++ for automatic drafts.** Many matched game, Kynapse, animation and physics functions are plain C named
  `func_XXXXXXXX`, as the decompiler produced them, although those libraries are C++. Turning them into methods of known
  classes (`include/<library>/classes/`), with real names, types and parameter names, makes the code useful. The mangled
  name changes with the declaration: update `config/SLUS_213.76/symbols.txt` so assembly callers still link (see Naming). RenderWare,
  the Sony libraries and libc are C, so C is correct there.
- **Real file names and directories.** Files are named `tu_<address>` until evidence shows the original name or class
  (strings, RTTI, class ownership). The rule for `src/game/`: **move a file when you learn what it is, rename it when the
  original name is known.** Moving means a `git mv` into the subsystem directory plus the `src:` path in `splits.yaml`
  (`python3 tools/relocate_sources.py old new` does both, see Naming); a rename is the same. A new file starts in `src/game/unsorted/`. Compiler-emitted
  inline and template copies go in `src/<library>/inline/` (the build computes whose they are, `build/SLUS_213.76/inline_owners.txt`).

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
- Source layout: `src/<library>/<name>.c|cpp` (`src/game/<subsystem>/` for the game library), one file per TU with every function of the TU (INCLUDE_ASM lines, drafts in
  `#ifdef NON_MATCHING` blocks). Headers follow the libraries (`include/<library>/`, shared helpers in `include/ps2/`).
  `tools/build/layout.py` has the naming rules.
- Name functions and types after what the code does only where the evidence supports it; unknown functions stay
  `func_XXXXXXXX`. Mark field offsets that are only accessed, not understood, as such (`UNVERIFIED`).
- Python tools: stdlib first, a purpose docstring and `--help` for every tool, no machine-specific paths.
- Do not push generated or private artifacts; do not add dependencies without a reason.

## Using AI assistants

Automated contributors follow the same rules; see [AGENTS.md](AGENTS.md). Whoever opens the pull request is responsible for
it: read the diff, run the build and say in the description how the change was produced.

## License

By contributing you agree that your contribution is dedicated to the public domain under [CC0 1.0](LICENSE).
