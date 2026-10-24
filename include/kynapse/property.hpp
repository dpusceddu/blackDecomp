#ifndef BLACK_PS2_KYNAPSE_PROPERTY_HPP
#define BLACK_PS2_KYNAPSE_PROPERTY_HPP
namespace BlackPS2 {
namespace Kynapse {
// Shared authored-property fallback. Keep the bool return and the two getter calls:
// caching the string or spelling this condition in the caller changes exact PS2 control flow.
// Entry's layout is not assumed; its GetSecond() contract comes from the consumer declaration.
template<class Entry>
static inline bool IsPrivateProperty(Entry *entry)
{
    if (entry) {
        if (entry->GetSecond()) {
            if (*entry->GetSecond() == '_') return true;
        }
    }
    return false;
}
}
}
#endif
