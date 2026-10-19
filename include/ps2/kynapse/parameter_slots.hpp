// Parameter-table owner prefix. Only slotCount/indexCount and the getter are exact-backed;
// the table pointer's semantic type and the complete owner allocation remain UNVERIFIED.
#ifndef BLACK_PS2_KYNAPSE_PARAMETER_SLOTS_HPP
#define BLACK_PS2_KYNAPSE_PARAMETER_SLOTS_HPP
struct SlotTable;
struct SlotOwner {
    unsigned char unknown00[0x10];
    unsigned int slotCount;
    SlotTable* table;
    unsigned int indexCount;
};
extern SlotOwner* gSlotOwner;

inline SlotOwner* GetSlotOwner()
{
    return gSlotOwner;
}

typedef char SlotOwnerSlotCountOffset[(unsigned int)&((SlotOwner*)0)->slotCount==0x10?1:-1];
typedef char SlotOwnerIndexCountOffset[(unsigned int)&((SlotOwner*)0)->indexCount==0x18?1:-1];
#endif
