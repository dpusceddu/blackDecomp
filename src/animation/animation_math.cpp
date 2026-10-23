#include "ps2/vu0_quaternion.hpp"

// Partial PS2 animation transform views, not recovered original class identities.
struct Transform { BkVuVector rotation, position; };
struct Offset { BkVuVector rotation; float position[3]; int index; };
struct Record { unsigned token; int count; Offset *offsets; };
struct Owner { char pad[0x44]; int count; Record *records; };
struct Query { unsigned unknown; Owner *owner; };
struct Key { unsigned unknown[2]; unsigned *token; };

extern "C" Transform *func_003440B8(Transform *out, const Transform *a, const Transform *b)
{
    BlackPS2::AnimationMath::Multiply(&out->rotation, &a->rotation, &b->rotation);
    BlackPS2::AnimationMath::Add(&out->position, &a->position, &b->position);
    return out;
}

extern "C" void *func_00347430(Query *query, void *poses, Key *key)
{
    Owner *owner = query->owner;
    unsigned *token = key->token;
    int count = owner->count;
    Record *r = owner->records;
    for (int i = 0; i < count; ++i, ++r) {
        if (r->token == *token) {
            Offset *o = r->offsets;
            for (int j = 0; j < r->count; ++j, ++o) {
                Transform *p = (Transform *)((char *)poses + 0x20 + (o->index << 5));
                BlackPS2::AnimationMath::Multiply(&p->rotation, &o->rotation, &p->rotation);
                BlackPS2::AnimationMath::Add(&p->position, &o->position, &p->position);
            }
            return poses;
        }
    }
    return poses;
}
