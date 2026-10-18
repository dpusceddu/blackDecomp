// Unmatched: func_00107470: indexed feedback aliases and float register allocation.
#ifdef NONMATCHING
extern char* D_0040F0E0;
struct FrontendControllerFeedback {
    char reserved[0x77c];
    unsigned char enabled;
    unsigned char dirtyPrimary,dirtySecondary;
    char reserved77f;
    float primary,secondary,target;
    float primaryTime,secondaryTime,strength,fadeTime;
    unsigned char enabledGlobal,resetPending[2];
    void Update(signed char index) __asm__("func_00107470");
};
void FrontendControllerFeedback::Update(signed char index) {
    char* bytes=(char*)this;
    FrontendControllerFeedback* lane=(FrontendControllerFeedback*)(bytes+index*4);
    unsigned char* control=(unsigned char*)bytes+index;
    if((lane->primary>0 || lane->secondary>0) && !control[0x77c]) control[0x79d]=1;
    if(control[0x79d]) {
        lane->primary=0; lane->secondary=0; lane->primaryTime=0;
        lane->secondaryTime=0; lane->target=0; lane->strength=0; lane->fadeTime=0;
        control[0x77d]=1; control[0x77e]=1; control[0x79d]=0;
        return;
    }
    if(lane->primaryTime>0) {
        lane->primaryTime-=*(float*)(D_0040F0E0+0x2013c);
        if(lane->primaryTime<=0) { lane->primary=0; control[0x77d]=1; }
        else if(lane->primary!=1) { lane->primary=1; control[0x77d]=1; }
    }
    float value;
    if(lane->secondaryTime>0) {
        lane->secondaryTime-=*(float*)(D_0040F0E0+0x2013c);
        if(lane->secondaryTime<=0) {
            value=lane->target;
            if(lane->secondary!=value) { lane->secondary=value; control[0x77e]=1; }
            lane->strength=0;
            return;
        }
        if(lane->secondaryTime<=lane->fadeTime) {
            value=lane->strength/3.2f;
            if(value<=lane->target) {
                if(lane->secondary!=lane->target) {
                    lane->secondary=lane->target; lane->strength=lane->target; control[0x77e]=1;
                }
            } else if(lane->secondary!=value) {
                lane->secondary=value; lane->strength=value; control[0x77e]=1;
            }
            return;
        }
        value=lane->strength;
    } else value=lane->target;
    if(value!=lane->secondary) { lane->secondary=value; control[0x77e]=1; }
}

#endif
