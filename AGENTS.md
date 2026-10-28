# Instructions for AI agents

[CONTRIBUTING.md](CONTRIBUTING.md) is the rulebook; follow it. This file adds what is specific to agents.

- Build and compile only through `ninja` and the tools in `tools/`; never start the proprietary compilers or assemblers directly.
- Use the [prepared native Linux environment](docs/setup.md#native-linux-prepared-once) and run project commands directly.
  On a new host, run `python3 tools/setup.py --provision` once if dependency installation is already authorized;
  otherwise report that command. Do not manage containers during matching.
- Commit without attribution lines. Do not push unless asked; a work session pushes to its own draft pull request.
- Include the model identifier, reasoning effort and person directing the work in every pull request, including draft
  claims. Record settings that are not exposed as `not exposed`; never guess. See [PR requirements](CONTRIBUTING.md#checks-and-pull-requests).

## Work session

When asked to "do a work session" (or to work on the decompilation without more detail), follow these steps.

1. **Prepare.** Read `.local/session.md` first when continuing a session. Use the supplied USA ISO (`orig/*.iso` or
   `python3 tools/setup.py --iso PATH`) or extracted executable; setup checks it without modifying the ISO.
   Require Git identity and authenticated `gh` access to `dpusceddu/blackDecomp`; setup checks both.
   Run `python3 tools/setup.py` and require `Ready`.
   Activate `. .venv/bin/activate` before further commands, repeating activation in each fresh shell. If setup used an
   already active venv, keep using that environment instead.
   Save `build/SLUS_213.76/units.json` as `.local/session-baseline-units.json`; its functions with status
   `source` are the protected set and must remain `source` throughout the session.
2. **Pick and claim.** Run `python3 tools/next.py --pick`, then `python3 tools/brief.py <file>`; use the brief to orient
   yourself, then inspect relevant code and callers as needed. Follow
   [picking and claiming](CONTRIBUTING.md#picking-and-claiming-work) before editing: push a session branch to a writable
   remote, open a draft PR explicitly against `dpusceddu/blackDecomp`, and recheck competing claims. Pick again if the
   functions make no sense to you; add related unclaimed files of the same family.
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
