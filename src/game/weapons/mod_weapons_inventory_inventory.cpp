#include "include_asm.h"

#include "game/weapons/inventory_methods.hpp"

namespace ModWeapons {
    extern "C" {
        void func_00156E70(Weapon*);
        void func_00156E80(Weapon*);
        void func_0013C868(BkModWeaponOwnerPS2*,EeS8);
        void *func_0015D248(void*,EeS8,int);
        int func_00155178(void*,int,EeU8);
        int func_00288790(void*);
        void func_00127060(void*);
        void *func_00107D20(unsigned);
        extern void *D_0040F4E4,*D_0040F4DC,*D_0040F514;
    }
    

#ifdef NON_MATCHING
// Unmatched: 0015BBD8: state-machine and action forwarding context.
// Unmatched: 0015C1A8: pickup slot iteration and return-tail context.
// Unmatched: 0015C3C8: inline VU axis rotation and matrix temporary ordering.
// Unmatched: 0015CC40: catalog classification loops and helper context.
// Unmatched: 0015CEF0: remaining caller register allocation.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0015BBD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0015C1A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0015C3C8);
#endif

Weapon* Inventory::Current(){
        return (Weapon*)Field<Weapon*>(poseManager->pair->primary,0x1b4);
    }
    void Inventory::Switch(){
        if(phase==0){
            Weapon*old=current;
            Weapon*replacement=slots[1-selectedSlot];
            if(old&&replacement!=old&&replacement){
                busy=1;
                phase=2;
                timer=0;
                func_00156E70(old);
            }
        }
    }
    int Inventory::Remaining(){
        int result=0;
        Weapon*selected=current;
        if(selected){
            void*d=func_0015D248(weaponManager,selected->weaponId,0);
            result=func_00155178(this,Field<int>(d,0x64),Field<EeU8>(d,0x60));
        }
        return result;
    }
    int Inventory::Eligible(EeS8 id){
        int result;
        EeS8 a,b;
        Weapon**s;
        if(busy==0){
            s=slots;
            Weapon*left=s[0];
            a=0x7f;
            Weapon*right;
            b=0x7f;
            if(left)a=left->weaponId;
            right=s[1];
            if(right)b=right->weaponId;
            result=0;
            if(id!=a){
                result=1;
                if(id==b)goto blocked;
            }
        }
        else{
            blocked:result=0;
        }
        return result;
    }
    void InventoryManager::ClearCatalog(){
        func_00288790(catalog);
        func_00127060(D_0040F4E4);
    }
    int Inventory::Select(){
        if(busy){
            request=1;
            return 0;
        }
        else{
            Field<EeU8>(current,0x106)=0;
            Field<EeU8>(current,0x107)=0;
            current=next;
            for(EeS8 i=0;i<slotCount;++i)if(next==slots[i])selectedSlot=i;
            func_00156E80(current);
            if(owner->kind==2){
                func_0013C868(owner,selectedSlot);
                current->SetPose(Field<EeU8>(current,0x108));
            }
            return 1;
        }
    }
    void Inventory::Force(Weapon*w){
        next=w;
        current=w;
        for(EeS8 i=0;i<slotCount;++i)if(slots[i]==w)selectedSlot=i;
        if(owner->kind==2){
            void*pose;
            if(Field<EeU8>(current,0x108)){
                pose=poseManager->pair->secondary;
                Field<EeU8>(presentation->animation->state,0x28c)=1;
            }
            else{
                pose=poseManager->pair->primary;
                Field<EeU8>(presentation->animation->state,0x28c)=0;
            }
            int mode=func_0015A948(current->primary);
            func_001D6E78(presentation->animation->graph,pose,*Field<EeU64*>(current,0xe8),mode);
        }
    }
    void Inventory::Allocate(EeS8 n){
        slotCount=n;
        slots=(Weapon**)func_00107D20(n*sizeof(Weapon*));
        for(EeS8 i=0;i<slotCount;++i)slots[i]=0;
    }
    void Inventory::Clear(){
        for(EeS8 i=0;i<slotCount;++i){
            if(slots[i]){
                ((InventoryManager*)weaponManager)->Release(slots[i]);
                slots[i]=0;
            }
        }
        current=0;
        selectedSlot=-1;
    }
}

