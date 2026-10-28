# Game input

The project targets the USA retail PS2 executable, `SLUS_213.76`. Supply your own ISO to
[setup](setup.md#game-input), or put the extracted executable at `orig/SLUS_213.76/SLUS_213.76`.
Only the boot executable is needed for matching; game assets are not required.

| Input | Expected value |
| --- | --- |
| Boot executable | `SLUS_213.76` |
| Executable size | 3,371,868 bytes |
| Executable SHA-256 | `141b05209570458af9c8e27ab1911f258da6353909d813cd572df026254ffe4c` |
| Disc image size | 3,919,609,856 bytes |
| Disc image SHA-256 | `65768cade88bfbaf566b67a3ef7a0bda5a9669779833914ffe7cd73a3e45cccd` |

`config/versions.json` records the input identity. Setup verifies the executable before accepting it;
`config/SLUS_213.76/checksums.sha256` records the required rebuilt image hash. The supplied ISO is preserved.

## Executable structure

The executable is a statically linked 32-bit little-endian MIPS ELF with `e_flags 0x20924001` and one PT_LOAD segment.
Its sections include `.text`, `.vutext`, `.reginfo`, `.DVP.*` overlays, `.debug_str`, `.data`, `.vudata`, `.rodata`,
`.gcc_except_table`, `.lit4`, `.sdata`, `.sbss`, `.bss` and `.vubss`.

It contains no symbol table, usable debug information or compiler banner. The `.debug_str` section holds one NUL byte.
The video decoder retains the source-path string `GameShared/GameClasses/Graphical/VideoDecoder/Ps2/vibuf.c`;
middleware build strings identify some libraries. Names, types and translation-unit boundaries must otherwise be
recovered from the binary's code and data. See [translation-unit evidence](units.md#recovering-original-translation-units)
and [naming](naming.md).

## What the first disassembly round found

Reassembling the USA retail `.text` with the EE-aware GNU assemblers (an early check, since removed; rabbitizer's R5900
support, numeric registers) reproduces every one of the 256 distinct mnemonics (2,684 words) and 40 random windows of 1,500
words, with three points that shaped the build:

1. **Short-loop padding.** Backward branches that jump back five words or fewer (941 of the 6,412 backward branches in
   retail, among 54,624 branches) make the assembler insert NOPs before the branch or refuse the file. The game was not
   assembled with that padding, so such branches are emitted as raw `.word` values. Local loop offsets do not change when a
   function moves, so this does not hurt the shiftable build.
2. **Words rabbitizer does not decode.** 579 words print as `.word` (459 COP1 words with a zero format field and function
   `0x24`, and 120 `vsqrt` words `0x4a......`) and 4 `0x00ff00ff` words in `.text`. They survive byte-exactly as data but are
   unreadable.
3. **`e_flags`.** GNU-assembled objects get `0x20920001`; SN objects and the retail ELF have `0x20924001`, so the packer
   (`tools/build/pack_elf.py`) writes the final flags explicitly.

SN GCC 2.95.3 build 1.36 under `-O2 -G0 -snas` produces ELF32 relocatable MIPS objects with `e_flags 0x20924001`, like the retail
executable: no `.mdebug` (the SN assembler does not emit one), uninitialised globals as common symbols, `HI16/LO16` pairs and no
`GPREL16`. With `-G8` it uses small-data symbols and `GPREL16` relocations; C++ output keeps the GCC 2.95 layout of one
`.gnu.linkonce.*` section per vtable, type info and inline function. `-snas` must be a separate argument (it is an option of the
driver, not of `cc1`).
