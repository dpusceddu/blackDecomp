# Shared mod context

The shared context owner maintains this directory. `config/mod_context.json` maps
its exact PS2 source consumers, subsystem entry points and unresolved parts.
Run `python tools/mod_context.py verify` to check native consumers, relocation
targets, preservation of committed source addresses and the identical full image.
Private disassembly and experiment logs stay under ignored build output.

| Area | Entry headers | Verified scope |
| --- | --- | --- |
| Camera/player input | `camera/controller.hpp`, `camera/axes.hpp`, `camera/pad_backend.hpp` | Camera child dispatch, input accumulators, pad fields/edges and backend state |
| Weapons/shots | `weapons/state.h`, `weapons/shot.h` | Reload/state/clip access, moving-shot active byte and 128-bit endpoint |
| Arms/animation | `animation/instance.h`, `animation/runtime.h` | Pose header, graph/flags/linked instance offsets and established bank/history helpers |
| Effects | `effects/asset.h`, `effects/slot.h`, `effects/render_state.h` | Asset record flags/timers, adjusted slot callbacks and supporting render buffers |

These are accessed prefixes and descriptive views, not recovered original class
identities, complete hierarchies or allocation sizes. A verified consumer proves
its actual accesses and calling recipe. Fields marked as instruction evidence
have no native control yet. Moving-shot pool stride comes from PS2 loops; it is
not inferred from the active-byte getter. Animation `owner84_unverified` remains
unverified, and legacy instance/playback/channel views retain distinct semantics.

Reuse `ps2/ee_types.h`, `ps2/vu0.hpp` and `ps2/matrix.hpp` for their scoped exact
recipes. Preserve mixed argument order, narrow returns, component spill order and
per-unit flags. Source order can alter scheduling even when runtime banks agree.
Matrix inverse/axis-angle and complete query payload contracts remain open.

Parent native ports and the counterpart map supply behavioral and identity leads.
They do not establish PS2 field offsets or Xbox-exact C++ provenance. The map keeps
those confidence levels separate from placed PS2 source controls. Compatibility
includes preserve existing type identities and mangled symbols.
