// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_action_stack_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x181b88
// Unmatched: private EBX stack/EAX event contract and expanded Resolve.
void ActionStack::DispatchEvent(QueuedActionEvent* event)
{
    owner->dispatcher.Event(event);
    for (int index = count; index > 0;) {
        --index;
        if (Resolve(kinds[index])->Event(event)) return;
    }
}

// /SLUS_213.76 0x181c20
// Unmatched: floating-point timer helper expansion and private register contract.
void ActionStack::ExpireTimers()
{
    for (int index = count; index > 0;) {
        --index;
        Action* action = Resolve(kinds[index]);
        CompletionRecord* record = &records[index];
        if (record->timer.Enabled() && record->timer.Expired()) {
            if (record->interval == -1.0f)
                record->timer.Clear();
            else record->timer.Start(record->interval);
            action->Timer();
        }
    }
    RetireFinished();
}

// /SLUS_213.76 0x181d20
// Unmatched: private EAX contract and callback register lifetimes.
void ActionStack::DeliverEvents()
{
    for (int index = 0; index < eventCount; ++index) {
        DispatchEvent(&events[index]);
        events[index].Clear();
        RetireFinished();
    }
    eventCount = 0;
}

}  // namespace BlackGame
