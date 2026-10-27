# Instructions for AI agents

[CONTRIBUTING.md](CONTRIBUTING.md) is the rulebook; follow it. This file adds what is specific to agents.

- Read what the task needs, not everything: CONTRIBUTING.md, the [matching handbook](docs/matching-handbook.md) before a TU,
  [docs/status.md](docs/status.md) for open problems. The maintainer docs (listed in CONTRIBUTING.md) only when you change
  the build.
- Build and compile only through `ninja` and the tools in `tools/`; never start the proprietary compilers or assemblers
  directly.
- Sessions use native Linux x86-64, with system dependencies, a Python virtual environment and the pinned toolchain
  provisioned once by the user or harness (`python3 tools/setup.py --provision`). Run project commands directly.
  If prerequisites are missing, report the provisioning command; do not choose a container because an image happens to
  be available, or manage container lifetimes and command prefixes during matching.
- Keep scratch files in `.local/` or `build/` (both ignored). Check free disk space before unpacking disc images, and
  process one image at a time.
- Commit without attribution lines. Do not push unless asked; a work session pushes to its own draft pull request.
- Say in every pull request that an AI agent did the work, and under whose direction.

## Work session

When asked to "do a work session" (or to work on the decompilation without more detail), follow these steps.

**Parallel work.** Independent sessions must not overwrite each other's source edits or generated files (`build/`, `asm/`
and `data/`). Use the harness's isolation and coordination facilities for parallel work.
Split the processor between sessions (`ninja -j` with the core count divided by the number of sessions): the SN tools can
stall under heavy load.

1. **Prepare.** Run `python3 tools/setup.py`: it checks dependencies and prepares assembly, metadata and `objdiff.json`
   without compiling all objects or linking an image, and must end with `Ready`.
   Save `build/SLUS_213.76/units.json` as `.local/session-baseline-units.json`; its functions with status
   `source` are the protected set.
2. **Pick.** Run `python3 tools/next.py --pick`: one unclaimed file, drawn at random from the best candidates (game code
   first), so sessions that start together rarely collide. If its functions make no sense to you, pick again; add related
   unclaimed files of the same family (`python3 tools/next.py` lists the candidates). Then run `python3 tools/brief.py
   <file>`: the file's recipe, recovered functions, earlier drafts and their notes, and for each target its callers,
   callees, data, an m2c draft and the assembly. Start from it instead of exploring the repository.
3. **Claim.** Open a draft pull request at once, before the real work: an empty commit is enough, with a description line
   `Claims: src/<file> [src/<file> ...]`. Then run `python3 tools/next.py claims`: if one of your files is listed with a
   lower pull request number than yours, it was claimed first; drop it from your claim and pick again. Without GitHub
   access, run only one session at a time and say so in the final report.
4. **Work by family.** Recover the shared types and layouts first (types decide most mismatches), then decompile all of the
   family's tractable functions as one batch, compile the changed units, compare in objdiff and iterate. Use
   `ninja build/SLUS_213.76/objdiff/base/<unit>.o` for each affected unit; this does not link the image. About five object
   builds per hypothesis per function; then leave the draft in `#ifdef NON_MATCHING` with a one-line `// Unmatched:` note
   and move on. Use the permuter only for near misses, with seeds that leave out unrelated `INCLUDE_ASM` bodies. A per-file flag or assembler
   change in `splits.yaml` needs a concrete reason in the native code, in a `note:` on the entry; reject one that only
   makes one function match by coincidence. No filler, padding or byte patches.
5. **Commit.** Keep every function of the protected set `source`, and check affected objects before committing. Commit per
   file or small batch; push to the draft pull request. Object matches are candidates until the final full-image check.
   New headers of the family go in their own commits; a change to a header that other files use goes alone in a commit
   whose message starts with `Shared:`.
6. **Log.** Keep `.local/session.md` (ignored): per batch, candidate functions and bytes matched in objdiff, time per
   candidate, blockers; after the final image check, record the verified gains. At the top, keep a short handoff
   (current file, pending candidates, next target).
7. **Stop** after about four hours, or earlier when two hours pass without a new candidate matching in objdiff, the build
   breaks in a way you cannot fix, or the claimed files have no tractable functions left. Finish the batch, then run one full-image `ninja`
   check before marking the pull request ready for review. Fix failures and repeat the check as needed; earlier image
   builds are for diagnosing concrete integration problems, not a per-function or per-commit requirement. Require `OK`
   and verify that every protected function is still `source`. Run `ninja progress`, push, and turn the draft into a
   ready pull request whose description gives baseline counts from the saved units and final verified progress, the
   functions matched, the drafts left and why, any per-file flags or tool fixes with their reasons, and that the work was
   done by an AI agent. A session that continues later reads the handoff first.
