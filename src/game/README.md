# src/game/

The game library, grouped by subsystem. A file is one translation unit (or a piece of one); it keeps the name
`tu_<address>` until the original name is known, and only its directory says what it is for.

| Directory | What belongs here | Evidence the grouping uses |
| --- | --- | --- |
| `ai/` | AI actions, action stacks, covers, and what is not specifically movement or navigation | `AIAction*`, `ActionStack`, `Recovered_Action`, the AI address cluster 0x172000-0x19d000 |
| `ai/movement/` | Movement modes (direct, formation, route-following), movement core | `AIMovement*`, `*MovementMode`, `MovementCore` |
| `ai/navigation/` | Routes, route requests and queues, node search, path agents | `AIRoute*`, `RouteRequest`, `RouteMode`, `AINavigation*`, `game_path` |
| `weapons/` | Weapon manager, inventory, reserves, shots | `ModWeapons::*`, `include/game/weapons`, exact consumers of the native weapon views |
| `camera/` | Camera controller, aiming, pad input | `CameraController`, `PadBackend`, `include/game/camera` |
| `effects/` | Emitters, muzzle flashes, lights, effect slots and simulation | `ModEffects::*`, `include/game/effects` |
| `world/` | World, object actors, regions, collision queries | `ModWorld::*`, `GameCollisionQueue` |
| `audio/` | Sound envelopes and voices | `*Envelope`, `sound_envelopes.hpp` |
| `ui/` | Front-end menus, movies, save dialogs, profiles | `Frontend*`, `include/game/frontend` |
| `actor/` | Actor state, entries, renderable and prop state | `CampaignActor::*`, `include/game/actor` |
| `inline/` | Compiler-emitted inline and template copies owned by the game library | `build/SLUS_213.76/inline_owners.txt` (generated) |
| `unsorted/` | Everything without clear evidence yet | none |

The directory a file is in is its subsystem; nothing else records it. `python3 tools/relocate_sources.py old new` moves a file. Do not expect `unsorted/` to be junk: it is mostly
code whose subsystem nobody has established. Move a file when you learn what it is; rename it when the original name is known.
