// Unmatched: busy boolean normalization, fallthrough scheduling and saved-register allocation.
#if 0
#include "game/frontend/movie_stream.hpp"
extern "C" FrontendStreamRequest* D_0040F4C4;
extern "C" int func_0035D728(char*,const char*,...);
extern "C" void func_00109E78(void*,FrontendStreamImage**);
extern "C" int func_001093C0(void*,const char*,int,int,void (*)(void*,FrontendStreamImage**),void*,unsigned char,int);
int FrontendMovieState::Prepare(void* decoderObject,void* renderTarget) {
    char path[64];
    switch(phase) {
    case 1:
        phase=55;
    case 55:
        firstStream=1;
        streamIndex=1;
        phase=2;
        streams[0].name=0;
    case 2:
        if(D_0040F4C4[8].busy || D_0040F4C4[8].loading) return 0;
        func_0035D728(path,"sound\\streams\\%s.ssh",streams[streamIndex].name);
        streams[streamIndex].data=0;
        func_001093C0(D_0040F4C4,path,8,9,func_00109E78,&streams[streamIndex].data,firstStream,0x02000000);
        firstStream=0;
        phase=3;
    case 3:
        if(!streams[streamIndex].data) return 0;
        ++streamIndex;
        if(streamIndex<18) {phase=2;return 0;}
        phase=28;
    case 28:
        decoder=decoderObject;
        target=renderTarget;
        state=1;
        stopRequested=0;
        requested=0;
        return 1;
    }
    return 0;
}
#endif
