# Agent rules

- Read `PLAN.md` (phases, principles) and `docs/inputs.md` (inputs, target decision) first.
- Never run SDK, compiler or assembler binaries on the host. Use `tools/compile.py` and `tools/sandbox.py`,
  which use the build backend in `.local/config.json`. If the build backend is unreachable (connection
  error), stop and report it; do not work around the isolation.
- Never commit game bytes, extracted files, generated assembly, compilers or build output. `orig/`, `asm/`,
  `data/`, `build/`, `.local/` and `.venv/` are ignored; keep it that way.
- Keep committed text free of machine-specific details: host names, user names, absolute paths, network
  addresses and credentials belong only in `.local/`.
- Check free disk space before unpacking disc images and process one image at a time.
- Once the build exists (Phase 1): build with `ninja`, claim a translation unit in `config/units.yaml` before
  editing it, and make every commit leave the build identical to the target.
- Keep docs short. No per-function proof journals; a one-line `// Unmatched:` comment on non-matching functions.
- Commit without attribution lines. Do not push.
