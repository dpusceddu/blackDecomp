#include "game/frontend_resources.hpp"

int FrontendCallbackQueue::Enqueue(void (*next)(), void* data) {
    if (callback) return 0;
    callbackData=data;
    callback=next;
    return 1;
}
