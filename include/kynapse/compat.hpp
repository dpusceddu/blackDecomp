// Declarations the Kynapse sources use from the C library and from Windows-style
// keywords the reconstructed code was written with. The compiler catalog has no
// complete target SDK headers, so they are supplied here. Carried over from the
// companion project's studies/ps2_xbox_compat.hpp.
#ifndef BLACK_KYNAPSE_COMPAT_HPP
#define BLACK_KYNAPSE_COMPAT_HPP

#define __cdecl
#define __stdcall
#define __thiscall
#define __fastcall
#define __forceinline inline
#define __declspec(x) __attribute__((x))
#define __int64 long
#define NULL 0

typedef unsigned int size_t;
typedef int ptrdiff_t;
extern "C" {
size_t strlen(const char*);
int strcmp(const char*, const char*);
int strncmp(const char*, const char*, size_t);
int _stricmp(const char*, const char*);
int _strnicmp(const char*, const char*, size_t);
char* strcpy(char*, const char*);
char* strncpy(char*, const char*, size_t);
char* strcat(char*, const char*);
char* strchr(const char*, int);
char* strstr(const char*, const char*);
void* memcpy(void*, const void*, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
int memcmp(const void*, const void*, size_t);
void* malloc(size_t);
void free(void*);
void qsort(void*, unsigned int, unsigned int, int (*)(const void*, const void*));
int abs(int);
int rand();
int atoi(const char*);
long atol(const char*);
double atof(const char*);
int sprintf(char*, const char*, ...);
double sin(double);
double cos(double);
double tan(double);
double asin(double);
double acos(double);
double atan(double);
double atan2(double, double);
double sqrt(double);
double fabs(double);
double floor(double);
double ceil(double);
double fmod(double, double);
double pow(double, double);
float sqrtf(float);
float fabsf(float);
int _finite(double);
int _isnan(double);
}

#endif
