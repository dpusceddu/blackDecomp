# Modding

The rebuild links every function and data object from separate pieces and lays them out with a generated linker script, so
adding, removing or growing code moves everything behind it and the linker fixes the references (`jal`, `%hi/%lo`, gp-relative
accesses, pointers in data, exception tables). A test inserting 200 NOPs into one function relinks with no inconsistency
([build.md](build.md#shiftability)); the known exceptions are raw numbers in data that look like addresses. To change
behavior, edit a translation unit file (`src/<library>/`, listed in `config/SLUS_213.76/splits.yaml`) and rebuild; the result is a modified
executable, not a match, so `ninja` will report a mismatch against the original hash. Never distribute the game's executable
or assets; distribute patches in a form that needs the user's own copy.
