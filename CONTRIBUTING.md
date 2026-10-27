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
  file before editing it and edit only what you claimed; shared headers (`include/ps2/`, headers other files use) and
  `splits.yaml` are small, reviewed changes, in commits of their own.
- **Drafts** go only in `#ifdef NON_MATCHING` above the function's `INCLUDE_ASM` line, with a one-line `// Unmatched:` note
  saying what differs; no `#if 0` blocks or other draft macros.
- **Only real work is committed**: source, drafts, headers, hand-edited configuration, docs and tests. Never commit game
  data or anything generated from it (executables, disc contents, `asm/`, `build/`, `data/`, savestates, compilers, build
  output), nor `progress/` or the progress table of the README (`ninja badges` writes them after merging).
- **Names, prototypes, types and layouts are source**, edited by hand and reviewed like code: `config/SLUS_213.76/symbols.txt`,
  `include/ps2/prototypes.h`, `include/ps2/recovered_types.h`, `include/<library>/`. Names need evidence (see
  [Naming](#naming)); mark what no matched function confirms `UNVERIFIED`. Nothing may depend on data from outside the
  repository: what you learn with Ghidra or IDA enters as edits to these files.
- **No machine-specific details** in committed text: host names, user names, absolute paths, addresses, credentials. Local
  settings go in `.local/` (ignored).
- **Style.** Format new C/C++ with `.clang-format`; never reformat existing sources (matching depends on their shape).
  Source layout: `src/<library>/<name>.c|cpp` (`src/game/<subsystem>/` for game code, link-once copies in
  `src/<library>/inline/`), one file per TU listing every function; headers in `include/<library>/`. Tools are stdlib-first
  Python with a purpose docstring and `--help`. Docs stay short and current; no per-function proof journals.
- **Commits** are small and logical (one file or one tool change is ideal), with a clear message.

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
2. Read the [matching handbook](docs/matching-handbook.md) before each TU: types, callee signatures and object lifetimes
   explain most mismatches. A function's assembly is `asm/SLUS_213.76/nonmatchings/<file>/func_XXXXXXXX.s`.
3. Replace the `INCLUDE_ASM` line with C or C++. `python3 tools/decompile.py func_XXXXXXXX` prints an m2c draft with the
   project's context (`--write` puts it in place). For the last differing instructions, run
   [decomp-permuter](docs/pipeline.md#using-decomp-permuter-directly) on the function.
4. Iterate with object comparisons and commit small batches. Before submitting the final changes for review, run `ninja`
   for the byte-exact check of the whole image: `OK`, or the file and function that differ, with the size and an instruction
   diff. Object matches remain candidates until this passes; preserve every previously exact function.
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

## Cleanup work

Always welcome, as long as `ninja` prints `OK`:

- **Readable C++ for automatic drafts.** Many matched game, Kynapse, animation and physics functions are plain C named
  `func_XXXXXXXX`, although those libraries are C++. Turning them into methods of known classes, with real names and types,
  makes the code useful (update `symbols.txt` for the new mangled name, see [Naming](#naming)). RenderWare, the Sony
  libraries and libc are C.
- **Real file names and directories.** Move a file into its `src/game/` subsystem when you learn what it is, rename it when
  the original name is known: `python3 tools/relocate_sources.py old new` moves the file and rewrites every mention of its
  path, including the `src:` entries in `splits.yaml` (`src/game/README.md` lists the directories).

## Checks and pull requests

Choose checks according to the impact rule above; the image and progress commands apply to source and build-input changes.
Run the image check once at the final revision before review, repeating it after fixes if it fails. Run the relevant test
suites for tool and build behavior changes.

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
  [docs/units.md](docs/units.md) (TU files and the split list), [docs/glossary.md](docs/glossary.md),
  [docs/tools.md](docs/tools.md) (index of the tools), [docs/setup.md](docs/setup.md), [docs/modding.md](docs/modding.md).
- For maintainers and build work: [docs/build.md](docs/build.md), [docs/pipeline.md](docs/pipeline.md),
  [docs/tus.md](docs/tus.md), [docs/inputs.md](docs/inputs.md), [docs/progress-reports.md](docs/progress-reports.md),
  [docs/history.md](docs/history.md).

## License

By contributing you agree that your contribution is dedicated to the public domain under [CC0 1.0](LICENSE).
