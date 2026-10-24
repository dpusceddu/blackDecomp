# Rules for AI-assisted contributions

Short, neutral rules for coding assistants and the people directing them. They are the same rules as in
[CONTRIBUTING.md](CONTRIBUTING.md).

- Start with [README.md](README.md) (setup, build), [docs/status.md](docs/status.md) (state, method, open problems) and the
  [matching handbook](docs/matching-handbook.md) before working on a TU.
- Use the build tools in `tools/`; they run the pinned compilers through `tools/toolchain.py` (local) or an optional
  backend plugin named in the ignored `.local/config.json` (`docs/build.md`). Never start compilers or other toolchain
  programs directly. If the backend reports a failure ("Build backend failed"), stop and report it; do not work around it.
- Never commit game bytes, extracted files, generated assembly or data, savestates, compilers or build output. `orig/`,
  `asm/`, `data/`, `build/`, `.local/` and `.venv/` are ignored; keep it that way.
- Keep committed text free of machine-specific details: host names, user names, absolute paths, network addresses and
  credentials belong only in `.local/`.
- Check free disk space before unpacking disc images and process one image at a time.
- Source layout: `src/<library>/<name>.c|cpp` (`src/game/<subsystem>/` for game code, see CONTRIBUTING.md; libraries: game, apt, kynapse, animation, physics, rw_core, rw_audio, sony,
  libc; link-once copies in `src/<library>/inline/`), one file per TU listing every function (recovered code, `INCLUDE_ASM` lines, drafts in `#ifdef NON_MATCHING` blocks). Headers follow the
  libraries in `include/<library>/` (shared helpers in `include/ps2/`). `tools/layout.py` has the naming rules.
- Build with `ninja`; every commit leaves it printing `OK` for USA retail (`SLUS_213.76`, the only version checked routinely).
  Run `python3 tools/check_versions.py` (all five versions) before releases or after changing shared build tools. Work by replacing a function's `INCLUDE_ASM` line in its TU file; the
  build inputs are `config/SLUS_213.76/splits.yaml`, `symbols.txt` and `equivalent.yaml` (edited by hand and by `autodecomp.py register`). Report progress with `ninja progress`; when it changes, run `ninja badges` and commit `progress/`.
- Names, prototypes, types and partial views are hand-maintained source: `config/SLUS_213.76/symbols.txt` (`// type:func alias`
  lines are readable names that never change linking), `include/ps2/prototypes.h`, `include/ps2/recovered_types.h` and
  `include/<library>/partial/`. Mark what no matched function confirms `UNVERIFIED`. Nothing here needs analysis data from outside
  the repository; an analysis tool such as Ghidra is optional and personal, and its output enters only as edits to these files.
- Evidence tiers: `exact` (byte-identical in the full image), `equivalent` (agrees on recorded states, recorded in
  `equivalent.yaml`; never replaces assembly), `draft`. Do not claim more than the evidence shows.
- Tools live in `tools/` (core) and `tools/studies/` (finished experiments); every tool needs a purpose docstring and
  `--help`. Keep docs short and current: no per-function proof journals, a one-line `// Unmatched:` comment on
  non-matching functions.
- Format new C/C++ with `.clang-format`; do not reformat existing sources.
- Commit without attribution lines. Do not push unless asked.
