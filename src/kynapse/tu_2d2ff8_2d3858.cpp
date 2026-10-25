// This virtual dispatch uses the TU's independently verified no-first-scheduler recipe.
extern "C" int func_002D3858(void* self) {
    void** target=*(void***)((char*)self+0xC);
    void* table=*target;
    return (*(int (**)(void*,void**))((char*)table+0x5C))(
        (char*)target+*(short*)((char*)table+0x58),target);
}
