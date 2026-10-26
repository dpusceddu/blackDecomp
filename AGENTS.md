# Rules for AI-assisted contributions

Short, neutral rules for coding assistants and the people directing them. They are the same rules as in
[CONTRIBUTING.md](CONTRIBUTING.md); terms are in the [glossary](docs/glossary.md).

- Start with [README.md](README.md) (setup, build), [docs/status.md](docs/status.md) (state, method, open problems) and the
  [matching handbook](docs/matching-handbook.md) before working on a TU.
- Use the build tools in `tools/`; they run the pinned local compilers installed by `tools/toolchain.py` in the Linux
  x86-64 environment documented in README.md. Build with ordinary `ninja` targets; never start proprietary tools directly.
- Commit only real work: source, drafts, headers, hand-edited configuration, docs and tests. Whatever the executable plus the committed
  sources and configuration determine (TU map, splat configuration, ELF layout, function boundaries, link-once owners, class skeletons,
  decompiler context) is generated into `build/` by `ninja` or a tool and never committed. Never commit game bytes, extracted files,
  generated assembly or data, savestates, compilers or build output. `orig/`,
  `asm/`, `data/`, `build/`, `.local/` and `.venv/` are ignored; keep it that way.
- Keep committed text free of machine-specific details: host names, user names, absolute paths, network addresses and
  credentials belong only in `.local/`.
- Check free disk space before unpacking disc images and process one image at a time.
- Every function belongs to exactly one file (`python3 tools/where.py func_XXXXXXXX` names it); work on a file only after claiming it (CONTRIBUTING.md, "Claiming a file"). Names follow the "Naming" section of CONTRIBUTING.md: no `Mod`, `Campaign` or `Black` prefixes, placeholders until the evidence supports a name.
- Source layout: `src/<library>/<name>.c|cpp` (`src/game/<subsystem>/` for game code, see CONTRIBUTING.md; libraries: game, apt, kynapse, animation, physics, rw_core, rw_audio, sony,
  libc; link-once copies in `src/<library>/inline/`), one file per TU listing every function (recovered code, `INCLUDE_ASM` lines, drafts in `#ifdef NON_MATCHING` blocks). Headers follow the
  libraries in `include/<library>/` (shared helpers in `include/ps2/`). `tools/build/layout.py` has the naming rules.
- Build with `ninja`; every commit leaves it printing `OK` for USA retail (`SLUS_213.76`, the only version checked routinely).
  Run `python3 tools/check_versions.py` (all five versions) before releases or after changing shared build tools. Work by replacing a function's `INCLUDE_ASM` line in its TU file; the
  build inputs are `config/SLUS_213.76/splits.yaml`, and `symbols.txt` (edited by hand and by `autodecomp.py register`). Report progress with `ninja progress` in the pull request description; do not commit `progress/` or the progress table of the README (`ninja badges` writes them; the maintainer regenerates them after merging, so pull requests never conflict on them).
- Names, prototypes, types and layouts are hand-maintained source: `config/SLUS_213.76/symbols.txt` (`// type:func alias`
  lines are readable names that never change linking), `include/ps2/prototypes.h`, `include/ps2/recovered_types.h` and the
  headers under `include/<library>/` (recovered layouts are `Recovered_*` structs with `unk_XX` fields). Mark what no matched function confirms `UNVERIFIED`. Nothing here needs analysis data from outside
  the repository; an analysis tool such as Ghidra is optional and personal, and its output enters only as edits to these files.
- Evidence: `exact` (byte-identical in the full image) or `draft` (a `NON_MATCHING` block). Do not claim more than the evidence shows.
- Drafts only as `#ifdef NON_MATCHING` above the function's `INCLUDE_ASM` line; no `#if 0` blocks or other draft macros.
- Tools: the everyday ones in `tools/`, build internals in `tools/build/`, the automatic pipeline in `tools/pipeline/`,
  maintainer and analysis tools in `tools/maint/` (index: `docs/tools.md`); every tool needs a purpose docstring and
  `--help`. Keep docs short and current: no per-function proof journals, a one-line `// Unmatched:` comment on
  non-matching functions.
- Format new C/C++ with `.clang-format`; do not reformat existing sources.
- Commit without attribution lines. Do not push unless asked.

## Work session

When asked to "do a work session" (or to work on the decompilation without more detail), follow these steps. Several agents
can run sessions at the same time, each in its own Git worktree and branch; the claims keep them apart.

1. **Build.** Work in a worktree of your own on a branch from the current `main` (or `upstream/main`). Run `ninja`: it must
   print `OK`. Save `build/SLUS_213.76/units.json` as `.local/session-baseline-units.json`; its functions with status
   `source` are the protected set.
2. **Pick.** Run `python3 tools/next.py --pick`: one unclaimed file, drawn at random from the best candidates (game code
   first), so sessions that start together rarely collide. If its functions make no sense to you, pick again; add related
   unclaimed files of the same family (`python3 tools/next.py` lists the candidates).
3. **Claim.** Open a draft pull request at once, before the real work: an empty commit is enough, with a description line
   `Claims: src/<file> [src/<file> ...]`. Then run `python3 tools/next.py claims`: if one of your files is listed with a
   lower pull request number than yours, it was claimed first; drop it from your claim and pick again. Without GitHub
   access, run only one session at a time and say so in the final report.
4. **Work by family.** Recover the shared types and layouts first (types decide most mismatches), then decompile all of the
   family's tractable functions as one batch, build, compare in objdiff and iterate. About five builds per hypothesis per
   function; then leave the draft in `#ifdef NON_MATCHING` with a one-line `// Unmatched:` note and move on. Use the
   permuter only for near misses, with seeds that leave out unrelated `INCLUDE_ASM` bodies. A per-file flag or assembler
   change in `splits.yaml` needs a concrete reason in the native code, in a `note:` on the entry; reject one that only
   makes one function match by coincidence. No filler, padding or byte patches.
5. **Commit.** Each commit leaves `ninja` printing `OK` and keeps every function of the protected set `source`. Commit per
   file or small batch; push to the draft pull request. New headers of the family go in their own commits; a change to a
   header that other files use goes alone in a commit whose message starts with `Shared:`.
6. **Log.** Keep `.local/session.md` (ignored): per batch, functions and bytes matched, time per match, blockers; at the
   top, a short handoff (current file, pending candidates, next target).
7. **Stop** after about four hours, or earlier when two hours pass without a new match, the build breaks in a way you
   cannot fix, or the claimed files have no tractable functions left. Finish the batch, push, and turn the draft into a
   ready pull request whose description gives `ninja progress` before and after, the functions matched, the drafts left
   and why, any per-file flags or tool fixes with their reasons, and that the work was done by an AI agent. A session that
   continues later reads the handoff first.
