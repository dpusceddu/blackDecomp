extern "C" long func_0035E730(const char*);
extern "C" float func_00291C68(long);
#include "kynapse/behaviors/pathway_vectors.hpp"
extern "C" int _stricmp(const char*,const char*);
extern "C" int func_0035E750(const char*);
namespace Kaim {
struct PathFlagControl : FlagControl {
    void Set(bool value) { this->value = value; active = true; }
};
struct PathScalarControl : Control {
    void Set(float value) { active = true; this->value = value; }
    void Write(float value) { this->value = value; active = true; }
    void Zero() { value = 0; active = true; }
};

inline void SetControl(Control* control, float value) {
    control->active = true;
    control->value = value;
}
inline void ZeroControl(Control* control) {
    control->value = 0;
    control->active = true;
}

// Normalize the supplied lvalue, retaining a field write on every iteration.
#define KAIM_NORMALIZE_DEGREES(degrees) do { \
    while ((degrees)<-180.0f || (degrees)>180.0f) \
        (degrees)=(degrees)>180.0f?(degrees)-360.0f:((degrees)<-180.0f?(degrees)+360.0f:(degrees)); \
} while(0)
inline bool BaseConfigure(ChildBuffers* entry) {
    if (entry) {
        if (entry->GetSecond()) {
            if (*entry->GetSecond() == '_')return true;
        }
    }
    return false;
}
bool PathWayAgent::Configure(ChildBuffers* entry) {
    const char* key;
    const char* value;
    if(!entry)goto failed;
    key=entry->GetSecond();
    if(!_stricmp(key,"PathWayName")) {
        value=entry->GetValue();
        if(!value)return false;
        if(pathways)goto findPath;
failed: return false;
findPath:
        pathWay = pathways->Find(value);
        return pathWay ? true : false;
    }
    if(!_stricmp(key,"StartingPointIndex")) {
        pointIndex = func_0035E750(entry->GetValue());
        return true;
    }
    return BaseConfigure(entry);
}
bool PathWayAgent::Update()
{
    unsigned int index;
    bank->ClearActivation();
    if (finished)
        goto succeeded;
    index = pointIndex;
    if (index == (unsigned int)-1)
        return false;
    if (waiting) {
        if (ExecuteAction(index)) {
            if (reverse) {
                unsigned int previous = pointIndex - 1;
                waiting = false;
                pointIndex = previous;
                if (previous == (unsigned int)-1) {
                    if (pathWay->loops) {
                        pointIndex = pathWay->count - 1;
                        goto succeeded;
                    }
                    finished = true;
                    pointIndex = pathWay->count;
                    goto succeeded;
                }
            } else {
                waiting = false;
                unsigned int next = pointIndex + 1;
                pointIndex = next;
                if (next >= pathWay->count) {
                    if (pathWay->loops) {
                        pointIndex = 0;
                        goto succeeded;
                    }
                    finished = true;
                }
            }
        }
        goto succeeded;
    }
    if (provider)goto queryTarget;
    return false;
queryTarget:
    {
        Vec3 target = pathWay->points[index].position;
        if (provider->Query(&target)) {
            bank->Select((PointerBank*)provider->bank);
            if (provider->IsActive()) {
                waiting = true;
                goto succeeded;
            }
            float speed = gEngine->unit * 6.0f;
            if (speedProperty)
                speed = speedProperty->value;

            if (strcmp(pathWay->points[pointIndex].mode, "walk") == 0)
                speed = speed * 0.25f;
            strcmp(pathWay->points[pointIndex].mode,"run");
            if (strcmp(pathWay->points[pointIndex].mode, "crouch") == 0 && crouch) {
                ((PathFlagControl*)crouch)->Set(true);
            }

            if (strcmp(pathWay->points[pointIndex].mode, "jump") == 0 && jump) {
                ((PathFlagControl*)jump)->Set(true);
            }
            if (forward) {
                if (limit && speed > limit->value)
                    speed = limit->value;
                ((PathScalarControl*)forward)->Write(speed);
            }
            if (turn) {
                float current = context->actor->speed;
                if (current > speed * 1.05f) {
                    ((PathScalarControl*)turn)->Set(-1.0f);
                } else if (current < speed * 0.95f) {
                    if (strafe) {
                        float amount = strafe->value;
                        if(amount<1.0f)((PathScalarControl*)turn)->Write(amount);
                        else ((PathScalarControl*)turn)->Write(1.0f);
                    }
                } else ((PathScalarControl*)turn)->Zero();
            }
            goto succeeded;
        }
    }
    return false;
succeeded:return true;
}
inline void PathWayAgent::StopMoving()
{
    if (forward) {
        ZeroControl(forward);
    }
}
bool PathWayAgent::ExecuteAction(unsigned int index)
{
    char word[16];
    char argument[16];
    if (sscanf(pathWay->points[index].command, "%s %s", word, argument) < 2)
        return true;
    float value = func_00291C68(func_0035E730(argument));
    if (strcmp(word, "pause") == 0) {
        if (!paused) {
            float now = gNow;
            paused = true;
            pauseEnd = now + value;
        }
        if (gNow < pauseEnd) {
            StopMoving();
            if (turn) {
                float current = context->actor->speed;
                float threshold = gEngine->unit * 0.05f;
                if (current > threshold)SetControl(turn,-1.0f);
                else if (threshold > current)SetControl(turn,1.0f);
                else ZeroControl(turn);
            }
        } else paused=false;
    }
    if (strcmp(word, "rotate") == 0) {
        if (!rotating) {
            rotateTarget = context->actor->angles.y + value;
            KAIM_NORMALIZE_DEGREES(rotateTarget);
            rotating = true;
        }
        float difference = rotateTarget - context->actor->angles.y;
        KAIM_NORMALIZE_DEGREES(difference);
        if (fabsf(difference) > 3.0f) {
            StopMoving();
            if (turn) {
                float current = context->actor->speed;
                float threshold = gEngine->unit * 0.05f;
                if (current > threshold)SetControl(turn,-1.0f);
                else if (threshold > current)SetControl(turn,1.0f);
                else ZeroControl(turn);
            }
            if (yawControl) {
                SetControl(yawControl,rotateTarget);
            }
            if (lookControl) {
                PathTurnVector direction = PathTurnVector(rotateTarget) - context->actor->angles;
                float change = direction.y;
                if (change > 3.0f)SetControl(lookControl,1.0f);
                else if (change < -3.0f)SetControl(lookControl,-1.0f);
                else ZeroControl(lookControl);
            }
        } else rotating=false;
    }
    if (strcmp(word, "orient") == 0) {
        if (!orienting) {
            orientTarget = value;
            KAIM_NORMALIZE_DEGREES(orientTarget);
            orienting = true;
        }
        float difference = orientTarget - context->actor->angles.y;
        KAIM_NORMALIZE_DEGREES(difference);
        if (fabsf(difference) > 3.0f) {
            StopMoving();
            if (turn) {
                float current = context->actor->speed;
                float threshold = gEngine->unit * 0.05f;
                if (current > threshold)SetControl(turn,-1.0f);
                else if (threshold > current)SetControl(turn,1.0f);
                else ZeroControl(turn);
            }
            if (yawControl) {
                SetControl(yawControl,orientTarget);
            }
            if (lookControl) {
                PathTurnVector direction = PathTurnVector(orientTarget) - context->actor->angles;
                float change = direction.y;
                if (change > 3.0f)SetControl(lookControl,1.0f);
                else if (change < -3.0f)SetControl(lookControl,-1.0f);
                else ZeroControl(lookControl);
            }
        } else orienting=false;
    }
    if (!paused) {
        if (!rotating) {
            if (!orienting)goto done;
        }
    }
    return false;
done:return true;
}

}
