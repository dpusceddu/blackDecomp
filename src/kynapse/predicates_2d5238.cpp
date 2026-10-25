#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"
#ifdef NON_MATCHING
#include "kynapse/hide_agent.hpp"
#endif

// /SLUS_213.76 0x2d5238

bool IsSet50::IsSet() const { if (value != 0) return true; return false; }

#ifdef NON_MATCHING
using namespace HideViews;
namespace HideViews {
// Unmatched: one redundant argument reload differs.
    bool HideAgent::Consider(const Candidate* candidate, const Vec3* offset, bool* handled)
   {
        if (candidate->id != currentId) {
            *handled = false;
            bool proceed = true;
            float score;
            bool usable = Evaluate(candidate, offset, &score, handled, &proceed);
            if (!proceed)
            return false;
            if (usable) {
                if (score > bestScore || !hasBest) {
                    destination = candidate->position;
                    currentId = candidate->id;
                    rank = graphSlot;
                    found = true;
                    hasBest = true;
                }
            }
        }
        return true;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/predicates_2d5238", func_002D5248);
#endif
