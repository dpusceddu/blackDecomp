# Agent rules

- Read `PLAN.md` (goal, method, state, open problems) and `README.md` (setup, build, working on a TU) first;
  `docs/inputs.md` has the inputs and variants. Read `docs/matching-handbook.md` before each TU.
- Never run SDK, compiler or assembler binaries on the host. Use `tools/compile.py` and `tools/sandbox.py`, which use
  the build backend in `.local/config.json`. If the build backend is unreachable (connection error), stop and report it;
  do not work around the isolation.
- Never commit game bytes, extracted files, generated assembly or data, savestates, compilers or build output. `orig/`,
  `asm/`, `data/`, `build/`, `.local/` and `.venv/` are ignored; keep it that way.
- Keep committed text free of machine-specific details: host names, user names, absolute paths, network addresses and
  credentials belong only in `.local/`.
- Check free disk space before unpacking disc images and process one image at a time.
- Source layout: `src/<library>/<name>.c|cpp` (libraries: game, apt, kynapse, animation, physics, rw_core, rw_audio, sony,
  libc, linkonce), one file per recovered TU; drafts no unit uses go to `src/<library>/nonmatching/`. Headers stay in
  `include/`. `tools/layout.py` has the naming rules and `tools/relayout.py` re-applies them.
- Build with `ninja`; every commit leaves it printing `OK` for USA retail. Claim a unit in `config/units.yaml` before
  editing its source. `units.yaml` is maintained by `tools/settle_units.py` and the autodecomp tools; each unit records
  `library`, `provenance` and `tier`. Report progress with `ninja progress`.
- Evidence tiers: `exact` (byte-identical in the full image), `equivalent` (agrees on recorded states, recorded in function
  `evidence:`; never replaces assembly), `draft`. Do not claim more than the evidence shows.
- Tools live in `tools/` (core) and `tools/studies/` (finished experiments); every tool needs a purpose docstring and
  `--help`. Keep docs short and current: no per-function proof journals, a one-line `// Unmatched:` comment on
  non-matching functions.
- Commit without attribution lines. Do not push.
