<!-- Keep the description short. Do not attach game files, executables, disassembly or build output. -->

## What this changes

<!-- Which file(s) / functions / tool. Link the "Claim a TU" issue if there is one: "Closes #123". -->

## Checks

- [ ] `ninja` prints `OK` for SLUS_213.76 on a clean build
- [ ] the tests pass: `python3 -m unittest discover -s tests` and `python3 -m unittest discover -s tests/tools`
- [ ] `ninja progress` did not get worse; before / after (functions, code bytes):
- [ ] I did not commit `progress/`, the progress table of `README.md`, game data, generated assembly or build output
- [ ] a function that does not match stays an `INCLUDE_ASM` line with its draft under `#ifdef NON_MATCHING` and a one-line `// Unmatched:` note
- [ ] names follow the "Naming" section of CONTRIBUTING.md

## How it was produced

<!-- Hand-written, tool-assisted (m2c / autodecomp / permuter) or by an AI assistant under your direction. You are responsible for the diff. -->
