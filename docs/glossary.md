# Glossary

One line per term. Longer explanations are in the files linked at the end of each line.

**TU** (translation unit): the source file (and its headers) that one compiler run turned into one object of the original
program. The TU map (`build/SLUS_213.76/tus.yaml`, written by `ninja tus`) is our estimate of the original TUs; our source files
follow it where the evidence allows. [units.md](units.md#recovering-original-translation-units)

**split**: an entry of `config/SLUS_213.76/splits.yaml`: a source file, the address range of the functions it owns, and the
compiler flags. Every function is owned by exactly one split. [units.md](units.md)

**INCLUDE_ASM**: a line `INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/<file>", func_XXXXXXXX);` that includes the
original assembly in its TU object of one function that is not recovered yet; replacing it by C/C++ is the work. [units.md](units.md)

**NON_MATCHING**: an `#ifdef NON_MATCHING` block holding a readable version of a function that does not compile to the
original bytes (yet); its `#else` branch keeps the `INCLUDE_ASM` line, so the normal build still uses the assembly. A
function in such a block is a *draft*; a function without an `INCLUDE_ASM` marker is *exact*. [CONTRIBUTING.md](../CONTRIBUTING.md)

**exact / draft**: the two evidence levels of a function: byte-identical in the full image, or a readable draft that is not.
[CONTRIBUTING.md](../CONTRIBUTING.md#rules)

**orphan piece**: an eight-byte `<one instruction>; nop` fragment between two functions. It is not code of either neighbour,
stays assembly, and is not a function in the objdiff count. [build.md](build.md#objects-and-includes)

**link-once copy**: code the compiler emits in every object that needs it (inline functions, templates, virtual
destructors, type information) of which the linker keeps the first copy; the kept copies form a block behind the regular code
and live in `src/<library>/inline/`. [build.md](build.md#link-once-copies)

**shiftable**: code and data can change size or move and the linker fixes every reference, so the rebuilt executable can be
modified (the base for modding), not only reproduced. [build.md](build.md#objects-and-includes)

**SN 1.36**: the compiler of the game, SN Systems' build 1.36 of GCC 2.95.3 for the EE (`ee-gcc2.95.3-136`); run with
`-O2 -G0 -snas`. [build.md](build.md#toolchain-facts)

**-snas**: the compiler option that makes the SN driver write the object with SN's own assembler (Ps2EeAs) instead of passing
the assembly to GNU `as`. [build.md](build.md#toolchain-facts)

**sn-min6**: a per-unit assembler recipe: a two-byte patched copy of Ps2EeAs 1.9.25.758 that pads short backward-branch loops
to six words. It reproduces the bytes of the units that use it; it is not a recovered rule about the original build.
[units.md](units.md#assemblers-and-short-loop-padding)

**objdiff code measure**: the headline figure of the README: matched function bytes divided by total function bytes, as objdiff
measures them (padding and orphan pieces excluded); it equals `ninja report`. [progress-reports.md](progress-reports.md)

**image measure**: the other way to count, printed by `ninja progress`: matched functions and bytes over every function start
and every byte between function starts, orphan pieces and alignment padding included. It is only ever quoted as the image
measure. [progress-reports.md](progress-reports.md)

**func_ / D_ / unk_ names**: placeholders named after an address: `func_00100258` is the function at 0x100258, `D_0040F0E0` the
data at 0x40F0E0, `unk_10` a field at offset 0x10 whose meaning is not known. They are replaced by a real or a descriptive name
when the evidence supports one ([CONTRIBUTING.md](../CONTRIBUTING.md#naming)).

**partial or local struct**: a `Recovered_<Name>` struct (or a struct defined in the one source file that uses it) that lists only
the fields some matched function accesses, padded with `unk_XX` fields; it makes no claim about the object's size or the other
fields, and is marked `UNVERIFIED` where no matched function confirms an offset. [CONTRIBUTING.md](../CONTRIBUTING.md#naming)

**bound name / alias**: a name in `config/SLUS_213.76/symbols.txt`. A *bound name* (`Reset__4Game = 0x1b78d8; // type:func`) is
what a compiled function is called, so linking depends on it; an *alias* (`... // type:func alias`) is only a readable working
name and never changes the build. [build.md](build.md#symbols-and-progress)

**UnknownVtable_<address>**: the placeholder name of a class that is known only by its virtual table; the class has no
run-time type information name in the executable. [naming.md](naming.md#where-names-come-from)

**RTTI**: the run-time type information of GCC 2.95 in the executable: it names the classes that have it (the Kaim classes and a
few others), their base classes and their virtual-table slots. [pipeline.md](pipeline.md)
