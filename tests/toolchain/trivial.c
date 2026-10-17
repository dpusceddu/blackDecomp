/* Phase 0 toolchain probe: plain C with a global, a small-data candidate and a call. */
int counter;
static int table[4] = {1, 2, 3, 4};
extern int external_value;

int bump(int step)
{
    counter += step + table[step & 3];
    return counter + external_value;
}
