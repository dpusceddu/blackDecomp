# Rules for AI-assisted contributions

Short, neutral rules for coding assistants and the people directing them. They are the same rules as in
[CONTRIBUTING.md](CONTRIBUTING.md).

- Start with [README.md](README.md) (setup, build), [docs/status.md](docs/status.md) (state, method, open problems) and the
  [matching handbook](docs/matching-handbook.md) before working on a TU.
- Use the build tools in `tools/`; they run the pinned compilers through `tools/toolchain.py` (local) or an optional backend plugin configured in the ignored `.local/config.json`. If the backend reports a failure (for example a connection error), stop and report it; do not work around it.
- Never commit game bytes, extracted files, generated assembly or data, savestates, compilers or build output. `orig/`,
  `asm/`, `data/`, `build/`, `.local/` and `.venv/` are ignored; keep it that way.
- Keep committed text free of machine-specific details: host names, user names, absolute paths, network addresses and
  credentials belong only in `.local/`.
- Check free disk space before unpacking disc images and process one image at a time.
- Source layout: `src/<library>/<name>.c|cpp` (libraries: game, apt, kynapse, animation, physics, rw_core, rw_audio, sony,
  libc, linkonce), one file per recovered TU; drafts no unit uses go to `src/<library>/nonmatching/`. Headers follow the
  libraries in `include/<library>/` (shared helpers in `include/ps2/`). `tools/layout.py` has the naming rules and
  `tools/relayout.py` re-applies them.
- Build with `ninja`; every commit leaves it printing `OK` for USA retail (`SLUS_213.76`, the only version checked routinely).
  Run `python3 tools/check_versions.py` (all five versions) before releases or after changing shared build tools. Edit the units you own in `config/units.yaml`;
  that file is maintained by `tools/settle_units.py` and the autodecomp tools, and each unit records `library`,
  `provenance` and `tier`. Report progress with `ninja progress`; when it changes, run `ninja badges` and commit `progress/`.
- Evidence tiers: `exact` (byte-identical in the full image), `equivalent` (agrees on recorded states, recorded in function
  `evidence:`; never replaces assembly), `draft`. Do not claim more than the evidence shows.
- Tools live in `tools/` (core) and `tools/studies/` (finished experiments); every tool needs a purpose docstring and
  `--help`. Keep docs short and current: no per-function proof journals, a one-line `// Unmatched:` comment on
  non-matching functions.
- Format new C/C++ with `.clang-format`; do not reformat existing sources.
- Commit without attribution lines. Do not push unless asked.
