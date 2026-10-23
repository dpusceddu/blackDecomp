/* Phase 1 interpreter negative control; compiled only in the build backend. */
#ifndef EE_CONTROL_VALUE
#define EE_CONTROL_VALUE 1
#endif

int eeharness_constant(void)
{
    return EE_CONTROL_VALUE;
}
