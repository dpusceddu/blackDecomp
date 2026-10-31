# Progress and open problems

The target is the USA retail executable (`SLUS_213.76`). See [game input](inputs.md) for its identity and checksums,
and the [README](../README.md) for the project and contribution workflow.

## Progress

<!-- progress:begin (tools/badges.py) -->

| Library | Functions matched | Share | Code matched (bytes) | Share |
| --- | ---: | ---: | ---: | ---: |
| game | 4,058 / 6,437 | 63.0 % | 364,840 / 1,453,676 | 25.1 % |
| kynapse | 1,351 / 1,557 | 86.8 % | 146,764 / 303,420 | 48.4 % |
| rw_core | 89 / 381 | 23.4 % | 5,140 / 179,516 | 2.9 % |
| rw_audio | 310 / 674 | 46.0 % | 22,824 / 106,632 | 21.4 % |
| animation | 259 / 377 | 68.7 % | 33,900 / 76,944 | 44.1 % |
| physics | 95 / 184 | 51.6 % | 12,056 / 77,680 | 15.5 % |
| apt | 235 / 705 | 33.3 % | 13,000 / 277,148 | 4.7 % |
| sony | 321 / 703 | 45.7 % | 15,836 / 140,092 | 11.3 % |
| libc | 76 / 209 | 36.4 % | 4,084 / 69,952 | 5.8 % |
| **Total** | **6,794 / 11,227** | **60.5 %** | **618,444 / 2,685,060** | **23.0 %** |

Functions as objdiff counts them: 6,794 of 11,227 (60.5 %); code: 618,444 of 2,685,060 bytes (23.03 %). Image measure (`ninja progress`): 6,794 of 11,899 function starts and 629,864 of 2,715,464 bytes (23.20 %), which includes the 672 orphan pieces and the alignment padding.

<!-- progress:end -->

The figures above are maintained by `ninja badges`. [Progress reports](progress-reports.md) explains the two measures
and their agreement with objdiff. Source and translation-unit facts from the same publication step:

<!-- facts:begin (tools/badges.py) -->

- The split list has 3,810 entries for 2,802 source files; 2,719 of the files hold recovered functions.
- 5,105 functions are still `INCLUDE_ASM` lines (one per function, in the one file that owns it).
- 325 files contain 830 `#ifdef NON_MATCHING` blocks (drafts that do not match yet, plus blocks that only carry includes and notes).
- 110 split entries select `assembler: sn-min6`.
- The TU map has 3,036 translation units; confidence of its boundaries by bytes of `.text`: `exact` 14.5 %, `high` 2.9 %, `medium` 52.8 %, `low` 29.8 %.

<!-- facts:end -->

The automatic pipeline's small-function results do not predict its success above 300 bytes. Code completion alone does
not establish owned-data completion.

## Open problems

1. **Large functions** (over 300 bytes, most of the remaining code): register allocation, scheduling and cleanup lifetimes after
   typing; algorithmic search code; EE vector and mixed 64/128-bit code (the VU0 lowering of the pipeline covers few functions).
2. **Types and classes**: complete class sizes, semantic names for the vtables without RTTI name (`UnknownVtable_<address>`,
   see [CONTRIBUTING.md](../CONTRIBUTING.md#naming)), tagged payloads, iterator and serialization helpers. Layouts verified
   only by matched accesses.
3. **Library code**: Sony and RenderWare code may need the vendor compilers' idioms or may never match from source;
   uncertain boundaries remain leads from the Xbox build.
4. **Assembler provenance** is unresolved: six/seven-word loops mix inside libraries and no position or content rule
   explains them; `sn-min6` is a per-unit recipe, not a recovered rule.
5. **Data**: only part of the TUs have complete owned-data audits. Native CFI and shared pools still block several otherwise
   complete objects.
6. **Names and counterparts**: working names (`alias` lines of `config/SLUS_213.76/symbols.txt`), recovered prototypes
   (`include/ps2/prototypes.h`) and structures (`include/ps2/recovered_types.h`) are reviewed source inputs; the build needs no
   external analysis database. An Xbox-to-PS2 counterpart map is an optional input that this repository does not ship.
