# Instructions for AI agents

[CONTRIBUTING.md](CONTRIBUTING.md) is the rulebook; follow it. This file adds what is specific to agents.

- Build and compile only through `ninja` and the tools in `tools/`; never start the proprietary compilers or assemblers directly.
- Use the [prepared native Linux environment](docs/setup.md#native-linux-prepared-once) and run project commands directly.
  If prerequisites are missing, report `python3 tools/setup.py --provision`; do not manage containers during matching.
- Commit without attribution lines. Do not push unless asked; a work session pushes to its own draft pull request.
- Say in every pull request that an AI agent did the work, and under whose direction.

## Work session

When asked to "do a work session" (or to work on the decompilation without more detail), follow these steps.

1. **Prepare.** Run `python3 tools/setup.py` and require `Ready`, then activate the venv with `. .venv/bin/activate`
   (repeat activation in each fresh shell).
   Save `build/SLUS_213.76/units.json` as `.local/session-baseline-units.json`; its functions with status
   `source` are the protected set and must remain `source` throughout the session.
2. **Pick and claim.** Run `python3 tools/next.py --pick`, then `python3 tools/brief.py <file>`; use the brief to orient
   yourself, then inspect relevant code and callers as needed. Follow
   [picking and claiming](CONTRIBUTING.md#picking-and-claiming-work) before editing. Pick again if the functions make no sense to you; add related unclaimed files of the same family.
3. **Match.** Follow the [matching loop](CONTRIBUTING.md#the-matching-loop). Working by family and recovering shared types
   first are useful defaults. Reassess an unproductive hypothesis after about five object builds; use the mismatch and
   remaining time to decide whether to continue or save a draft. Push progress to the session's draft pull request.
4. **Handoff.** Keep `.local/session.md` (ignored) with the current file, saved near misses, blockers and next target.
   At the end, record baseline counts and verified gains.
5. **Stop** after about four hours, or earlier when two hours pass without a new candidate matching in objdiff, the build
   breaks in a way you cannot fix, or the claimed files have no tractable functions left. Finish the batch and complete
   [checks and pull requests](CONTRIBUTING.md#checks-and-pull-requests) before marking the draft ready. Report baseline
   counts, final verified progress, functions matched, drafts left and why, and reasons for any flags or tool fixes.
   A session that continues later reads the handoff first.
