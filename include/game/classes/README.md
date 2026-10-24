# Class views (include/game/classes/, include/kynapse/classes/)

Hand-edited headers: the class views the sources include. Each began as a skeleton that `tools/maint/class_skeletons.py`
produces from RTTI and the vtables; the skeletons are no longer committed. Run `ninja classes` to write the complete set into the
ignored `build/classes/include/` (it needs the recovered context, `tools/autodecomp.py context --refresh`, which `ninja classes`
runs), and copy a skeleton here when a source needs it. ABI evidence for the generator is in
`config/SLUS_213.76/class_method_abi.json` and `config/SLUS_213.76/rtti_abi.json`.

- `hierarchy.hpp` holds the RTTI base relations as empty `Hierarchy_*` types. They say who derives from whom, not how an object is laid out.
- Class views expose PS2 field offsets through inline references. They do not claim complete allocation sizes or C++ inheritance
  layouts, and unknown signatures are marked `UNVERIFIED`. `VirtualInterface*` lists vtable slots in their actual order.
- A matched function verifies only the field accesses it actually uses, not every field of the view. Exact code proves access and
  ABI compatibility, not the original semantic argument, return or field types.
