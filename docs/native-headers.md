# Shared mod context

The shared context owner maintains this directory. `config/mod_context.json` maps
its exact PS2 source consumers, subsystem entry points and unresolved parts.
Run `python tools/mod_context.py verify` to check native consumers, relocation
targets, preservation of committed source addresses and the identical full image.
Private disassembly and experiment logs stay under ignored build output.

| Area | Entry headers | Verified scope |
| --- | --- | --- |
| Camera/player input | `camera/controller.hpp`, `camera/axes.hpp`, `camera/pad_backend.hpp` | Camera child dispatch, input accumulators, pad fields/edges and backend state |
| Weapons/shots | `weapons/controller.hpp`, `weapons/instance.hpp`, `weapons/moving.hpp`, `weapons/inventory.h` | Native controller, reload, hit collector, moving/delayed shots and reserve access |
| Arms/animation | `animation/runtime.h`, `animation/sampling.h`, `arms/instance.hpp`, `arms/owner.hpp` | Pose/instance and sampling views, adjusted selector calls, empty matrix constructor and profile cleanup |
| Effects | `effects/runtime.hpp`, `effects/slot_views.hpp`, `effects/random.h`, `effects/asset.h` | Native lifecycle matrices, adjusted actor callbacks, seed state and asset timers |

These are accessed prefixes and descriptive views, not recovered original class
identities, complete hierarchies or allocation sizes. A verified consumer proves
its actual accesses and calling recipe. Fields marked as instruction evidence
have no native control yet. Moving-shot pool stride comes from PS2 loops; it is
now also has a placed native allocator control. Animation `owner84_unverified` remains
unverified, and legacy instance/playback/channel views retain distinct semantics.

Reuse `ps2/ee_types.h`, `ps2/vu0.hpp` and `ps2/matrix.hpp` for their scoped exact
recipes. Preserve mixed argument order, narrow returns, component spill order and
per-unit flags. Source order can alter scheduling even when runtime banks agree.
Matrix inverse/axis-angle and complete query payload contracts remain open.

`camera/aim.hpp` and the muzzle, attachment-manager and timed-transform views in
`effects/runtime.hpp` have PS2 instruction evidence only. The latter manager has
80 entries, distinct from the generic pool; timed transforms have eight rows of
stride `0xb0`. Muzzle resource `+0xc4` is a pointer and variant/phase are signed
bytes. `effects/vu_math.h` preserves the existing unverified VU polynomial and
lane masks. A transitive include does not verify these unused types or helpers.
All four muzzle RNG high-half shifts are arithmetic; logical shifts by one belong
to unsigned float conversion. Preserve each site's floating multiplication order.

Sampling declarations retain C linkage for native C++ callers. The pair wrap flag
is one byte at `+0xc`; its trailing three bytes are unverified. Matrix-building
microcalls still need their complete clobber and synchronization contracts. A
worker probe confirms SN AS takes byte addresses: quaternion call operand
`0x1a8` encodes microinstruction index `0x35`; operand `0x35` selects another call.

Parent native ports and the counterpart map supply behavioral and identity leads.
They do not establish PS2 field offsets or Xbox-exact C++ provenance. The map keeps
those confidence levels separate from placed PS2 source controls. Compatibility
includes preserve existing type identities and mangled symbols.
