#include "include_asm.h"

#include "game/weapons/inventory_methods.hpp"

namespace ModWeapons {
    extern "C" {
        int func_00288790(void*);
        void *func_00107D20(unsigned);
        void func_00107B78(void*,int,int,int);
        void func_001561F8(Weapon*);
        void func_00158F08(Instance*);
        void func_001632E0(BkModDelayedShotPS2*);
        void func_0015D3D8(MovingShot*);
        void func_00163328(float,BkModDelayedShotPS2*);
        int func_00156450(Weapon*);
        extern char D_0040F0F0;
    }
    

void InventoryManager::Allocate(){
        func_00107B78(&D_0040F0F0,1,16,0);
        void*allocated=func_00107D20(0x31f0);
        for(int i=46;i!=-1;--i){
        }
        controllers=allocated;
        func_00107B78(&D_0040F0F0,1,8,0);
        controllerFlags=(EeU8*)func_00107D20(47);
        instances=(Instance*)func_00107D20(0x708);
        instanceFlags=(EeU8*)func_00107D20(50);
        func_00107B78(&D_0040F0F0,1,128,0);
        for(EeS8 i=0;i<47;++i)func_001561F8((Weapon*)((char*)controllers+i*0x110));
        for(EeS8 i=0;i<50;++i)func_00158F08((Instance*)((char*)instances+i*0x24));
    }
    int InventoryManager::Reset(){
        func_00288790(catalog);
        EeS8 i=0;
        do{
            controllerFlags[i]=0;
        }
        while(++i<47);
        i=0;
        do{
            instanceFlags[i]=0;
        }
        while(++i<50);
        for(EeS8 i=0;i<36;++i)func_001632E0(&delayed[i]);
        for(int i=0;i<16;++i)func_0015D3D8(&shots[i]);
        return 1;
    }
    void InventoryManager::Tick(){
        float dt=frame->delta;
        for(EeS8 i=0;i<36;++i)func_00163328(dt,&delayed[i]);
        for(int i=0;i<16;++i)shots[i].Update(dt);
    }
    void InventoryManager::Release(Weapon*w){
        EeS8 i=0;
        while(w!=(Weapon*)((char*)controllers+i*0x110))++i;
        func_00156450((Weapon*)((char*)controllers+i*0x110));
        controllerFlags[i]=0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0015CC40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0015CEF0);
