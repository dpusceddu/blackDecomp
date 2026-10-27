# Naming reference

Placeholders are named after an address (`func_00100258`, `D_0040F0E0`, `unk_10`; see the [glossary](glossary.md)). A better
name is a normal contribution where the evidence supports it. The examples below were tried on a scratch copy of the
repository and gave an identical build. Follow the [validation impact rule](../CONTRIBUTING.md#rules) for your change.
Names are inside the compiler's symbols, so a rename that is not just a local variable touches
`config/SLUS_213.76/symbols.txt`; keep that file ordered by address.

## Where names come from

1. **RTTI**: the executable names the classes that have run-time type information (the `Kaim::` classes and a few others) and
   their base classes. These names are original; use them as they are (`Kaim::CBrain`). `ninja classes` writes the full list
   with the virtual tables into the ignored `build/classes/`.
2. **Aliases**: readable names found by analysis (`Name = 0x...; // type:func alias` in `symbols.txt`). They are working names,
   not original ones, and never change the build.
3. **Placeholders**: `func_<address>`, `D_<address>` and `unk_<offset>`, plus two generated ones: `UnknownVtable_<address>` for a
   class known only by its virtual table (no type-info name; the class view lives in `include/game/classes/` under that name) and
   `Function_<address>` for an unnamed virtual method in a generated class view. They are kept until a better name is justified.
4. **Descriptive names** we choose for classes and namespaces that have no original name: plain English for what the code does
   (`Weapons`, `WorldObjects`, `HideAgent`), never prefixed with `Mod`, `Campaign` or `Black`, and namespaces that hold only
   partial layouts end in `Views`. Names such as `Fragment34FE10` or `KaimAvoidance` are scopes local to one file or group of files, not
   class names. Do not take a name from the Xbox build as if it were a PS2 fact.

## A readable name for a C function

`func_00367460` is the BIOS call that sets the GS video mode, and `symbols.txt` has it as an alias. To make `SetGsCrt` the real
name, rename the definition, turn the alias line into a bound-name line (drop `alias`) and update the prototype:

```sh
sed -i 's/^void func_00367460(void) {/void SetGsCrt(void) {/' src/sony/tu_367450.c
sed -i 's|^SetGsCrt = 0x367460; // type:func alias|SetGsCrt = 0x367460; // type:func|' config/SLUS_213.76/symbols.txt
sed -i 's|^extern void func_00367460(void); /\* SetGsCrt \*/|extern void SetGsCrt(void);|' include/ps2/prototypes.h
ninja        # OK; assembly callers of func_00367460 still link, because the bound name is the address's name
```

A name used by other source files must be renamed there too (`rg func_00367460 src include`).

## A C++ method

`func_002D5368` is a getter of the hide behaviour in `src/kynapse/hide_agent_2d3c90.cpp`; HideAgent is a class view in
`include/kynapse/hide_agent.hpp`. Make it a method of the class: declare it in the class, define it with the class name, and bind
the mangled name to the address.

```cpp
// include/kynapse/hide_agent.hpp, in struct HideAgent (namespace HideViews):
const Vec3* CurrentPosition();

// src/kynapse/hide_agent_2d3c90.cpp, in place of  extern "C" const Vec3 *func_002D5368(HideAgent *self) { ... }
namespace HideViews {
    const Vec3 *HideAgent::CurrentPosition() {
        if (found) { if (fresh) return &destination; }
        return &context->actor->position;
    }
}
```

```
# config/SLUS_213.76/symbols.txt: GCC 2.95 mangling is  Method__<class path>  with <len><name> for each part,
# Q<n> for a nested path:  HideViews::HideAgent::CurrentPosition()  ->  CurrentPosition__Q29HideViews9HideAgent
CurrentPosition__Q29HideViews9HideAgent = 0x2D5368; // type:func
```

A method of a class in the global namespace is `Method__<len>Class` (`Reset__4Game`), a `const` method has `C` before the class
(`Head__C10RouteQueue`), parameters follow the class (`i`, `f`, `Pv`, `P<len>Name`). If the binding is wrong, `ninja` reports `func_002D5368: no definition in object`. Inspect the compiled object
with `python3 tools/objdump.py build/SLUS_213.76/obj/units/<unit>.o` and put its actual mangled name in `symbols.txt`. `python3 tools/where.py func_002D5368` finds the definition afterwards (it also understands
`Class::Method`).

## A type or struct rename with unk_ fields

A recovered layout is a `Recovered_<Name>` struct with `unk_XX` fields named after the PS2 offset (`unk_118` is the field at
0x118). When the class is known, drop the prefix and name the fields you understand; leave the others as they are:

```sh
rg "Recovered_AnimationParameterBank|unk_118" src include          # every use
sed -i 's/Recovered_AnimationParameterBank/AnimationParameterBank/g; s/unk_118/activeCount/g' src/animation/tu_350140.c
ninja        # OK
```

Renaming changes no bytes in C. For a C++ class or namespace it changes the mangled symbols that contain its name (the length
prefix too: `Q29HideViews9HideAgent` becomes `Q210SearchView9HideAgent`), so search `symbols.txt` and the `__asm__("...")` labels
for the old name and rewrite them together with the length. Mark a field `UNVERIFIED` when no matched function uses it.
