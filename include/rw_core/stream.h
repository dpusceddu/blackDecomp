#ifndef BLACK_RENDERWARE_CORE_STREAM_H
#define BLACK_RENDERWARE_CORE_STREAM_H
#include "auto/prelude.h"
/* PS2 stream union remains UNVERIFIED; custom callbacks share memory/file offsets.
   The matching chunk classifier verifies the chunk header type field. */
typedef struct RwStreamPS2 {
 u32 type,access,owned;
 union {
  void *file;
  struct {u32 position,size;u8 *buffer;} memory;
  struct {void *close;u32 (*read)(void *,void *,u32);s32 (*write)(void *,const void *,u32);s32 (*skip)(void *,u32);void *context;} custom;
 } data;
} RwStreamPS2;
typedef struct RwChunkHeaderPS2 {u32 type,length,version,build,is_complex;} RwChunkHeaderPS2;
typedef char RwStreamPS2_custom_context[(unsigned)&((RwStreamPS2 *)0)->data.custom.context==0x1c?1:-1];
#endif
