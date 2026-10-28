<!-- Keep the description short. Do not attach game files, executables, disassembly or build output. -->

## What this changes

<!-- Which file(s) / functions / tool. Keep the "Claims:" line while the work is in progress. -->

## Checks

<!-- Follow CONTRIBUTING.md's validation impact rule; mark checks that do not apply as N/A. -->

- [ ] `ninja` prints `OK` for SLUS_213.76 on a clean build
- [ ] the tests pass: `python3 -m unittest discover -s tests`
- [ ] `ninja progress` did not get worse; before / after (functions, code bytes):
- [ ] I did not commit `progress/`, generated sections of `docs/status.md`, game data, generated assembly or build output
- [ ] a function that does not match stays an `INCLUDE_ASM` line with its draft under `#ifdef NON_MATCHING` and a one-line `// Unmatched:` note
- [ ] names follow the "Naming" section of CONTRIBUTING.md

## Session

<!-- Required from the initial draft claim onward. Use exact configured settings, or "not exposed" when unavailable.
     List each model / reasoning setting and its role if several contributed. Keep these fields current. -->

- Model:
- Reasoning effort:
- Directed by:
