#include "kynapse/agents/text.hpp"

namespace KaimText {

bool Script::Load(const char* name)
{
    FileService* files = gEngine->files;
    if (!files)
        return false;
    if (!files->Open(name))
        return false;
    size = files->GetSize(name);
    if (size > 0) {
        text = (char*)KaimAllocate(size + 1);
        if (files->Read(name, text, size) != size) {
            files->Close(name);
            return false;
        }
        text[size] = 0;
    }
    files->Close(name);
    return true;
}

bool Script::LoadFile(const char* name)
{
    void* file = hooks.open(name, "rb");
    if (!file)
        return false;
    size = hooks.seek(file, 0, 2);
    if (size) {
        text = (char*)KaimAllocate(size);
        if (hooks.read(text, 1, size, file) != size) {
            hooks.close(file);
            return false;
        }
    }
    hooks.close(file);
    return true;
}

Script::Script(const Script& other)
{
    *this = other;
}

bool Script::SaveFile(const char* name)
{
    void* file = hooks.open(name, "wb");
    if (!file)
        return false;
    if (hooks.write(text, 1, size, file) != size) {
        hooks.close(file);
        return false;
    }
    hooks.close(file);
    return true;
}

}
