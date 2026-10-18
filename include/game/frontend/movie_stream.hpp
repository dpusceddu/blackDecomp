#ifndef GAME_FRONTEND_MOVIE_STREAM_HPP
#define GAME_FRONTEND_MOVIE_STREAM_HPP

// PS2 views inferred from stream scheduling and movie-state field accesses.
struct FrontendMovieStreamEntry { void* data; const char* name; };
struct FrontendMovieState {
    void* decoder;
    char reserved4[0x40];
    char filename[0x40];
    char name[0x80];
    FrontendMovieStreamEntry streams[18];
    void* target;
    unsigned int flags, startedAt;
    int streamIndex, phase, state, reserved1ac;
    int fade, pendingFade;
    unsigned char requested, stopRequested, active, firstStream;
    int Stop() __asm__("func_00109DC0");
    int Prepare(void*,void*) __asm__("func_00109760");
    void Update() __asm__("func_00109918");
};
struct FrontendStreamRequest {
    char reserved[0x114];
    int callback;
    void* callbackData;
    char reserved11c[0x1c];
    unsigned char busy, loading, reserved13a;
    unsigned char pending;
    char reserved13c[4];
};
struct FrontendStreamScheduler {
    int Schedule(const char*,int,int,int,void*,unsigned,unsigned) __asm__("func_001093C0");
    int ErrorCode(int) __asm__("func_00109EE0");
    void SetCallback(int,int,void*) __asm__("func_00109468");
};
struct FrontendStreamImage {
    char reserved[0x16];
    short count;
    char* entries;
};
typedef char FrontendStreamRequestSize[(sizeof(FrontendStreamRequest)==0x140)?1:-1];
#endif
