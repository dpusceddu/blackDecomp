# Generated PS2 class interfaces

`tools/class_skeletons.py` is the single owner of this directory. Change verified
ABI evidence in `config/class_skeletons.json` or `config/rtti_evidence.json`, then
regenerate; do not edit generated headers. Run `tools/class_skeletons.py --check`
to check the complete generated tree. The detailed catalog stays in ignored
`build/classes/catalog.json`.

The recovered context cache is required. Refresh it before generating and checking:

```sh
.venv/bin/python tools/autodecomp.py context --refresh
.venv/bin/python tools/class_skeletons.py
.venv/bin/python tools/class_skeletons.py --check
```

RTTI names and semantic base hierarchies are decoded from retail. `Hierarchy_*`
types preserve those relationships, without representing PS2 object storage.
Unknown vtable owners and callback-like runs remain explicitly unverified.

Class views expose PS2 field offsets through inline references. They do not claim
complete allocation sizes or C++ inheritance layouts. `VirtualInterface*` lists
slots in their actual order; unknown signatures are marked. The separate `ABI_*`
dispatch views exist only where an exact source probe verified the vptr position
and call signature. Ordinary inferred virtual interfaces must not be used as
verified layouts. A matched function verifies only the specific field accesses
it actually uses, not every field grouped with its vtable.
Exact code proves access and ABI compatibility, not the original semantic argument,
return or field types.
