// This prefix view preserves the record stride and the two observed flag words.
struct BkFlagRecordPS2 {
    char opaque[0x58];
    unsigned short flags58, flags5a;
    char trailing[0x74];
};
struct BkFlagAssetPS2 {
    char opaque[0x48];
    BkFlagRecordPS2 *records;
};
extern "C" int func_001AFBF0(void *);

extern "C" bool func_001AFBA8(BkFlagAssetPS2 *asset) {
    BkFlagRecordPS2 *record = &asset->records[func_001AFBF0(asset)];
    if (record) return (record->flags5a >> 5) & 1;
    return false;
}

extern "C" bool func_001AFC30(BkFlagAssetPS2 *asset) {
    BkFlagRecordPS2 *record = &asset->records[func_001AFBF0(asset)];
    if (record) return (record->flags58 >> 14) & 1;
    return false;
}
