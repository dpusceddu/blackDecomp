#include "kynapse/agents/sound.hpp"

namespace Kaim {
static inline float DistanceSquared(const SoundEvent* sound, const Listener* listener) {
    const Vec3& b = *(const Vec3*)&listener->x;
    const Vec3& a = *(const Vec3*)&sound->x;
    float dz = a.z - b.z;
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dz * dz + dx * dx + dy * dy;
}

bool SoundPool::Restart() {
    lastTime = gNow;
    return Reset();
}

void SoundPool::Update() {
    float now = gNow;
    float previousTime = lastTime;
    if (previousTime == now)
        return;
    int current = activeHead;
    int previous = -1;
    while (current != -1) {
        float expiry = events[current].expiry;
        if (expiry <= gNow && expiry != -1.0f) {
            int next = events[current].next;
            RemoveSound(current, previous);
            current = next;
        } else {
            previous = current;
            current = events[previous].next;
        }
    }
    lastTime = gNow;
}

bool SoundPool::AddSound(unsigned kind, const Vec3& position, int radius, Listener* owner, float duration) {
    int index = ReserveSound(kind);
    if (index == -1)
        return false;
    float expiry = gNow + duration;
    *(Vec3*)&events[index].x = position;
    events[index].owner = owner;
    events[index].category = kind;
    events[index].radius = radius;
    events[index].expiry = expiry;
    return true;
}

bool SoundPool::Matches(Listener* listener, SoundEvent* event) {
    if (!(event->expiry <= gNow)) {
        float distance = DistanceSquared(event, listener);
        if (distance == 0.0f) {
            if (event->radius > 0)
                return true;
        } else {
            float level = float(event->radius * event->radius) / distance;
            AuthoredProperty* hearing = listener->GetAuthoredProperty(&gSoundKey2B4F00);
            if (hearing) {
                float sensitivity = hearing->value;
                if (level > 0.0f) {
                    if (1.0f / level < sensitivity * sensitivity)
                        return true;
                }
            } else if (level > 0.0f) {
                return true;
            }
        }
    }
    return false;
}

} // namespace Kaim
