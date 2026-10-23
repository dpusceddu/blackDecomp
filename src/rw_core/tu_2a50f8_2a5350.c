#include "rw_core/stream.h"
extern RwStreamPS2 *func_002A71E0(RwStreamPS2 *,const void *,u32);
RwStreamPS2 *func_002A5350(RwStreamPS2 *stream,u32 type,u32 length,u32 version,u32 build) {
 struct {u32 type,length,stamp;} header;
 header.type=type;header.length=length;header.stamp=(((version-0x30000)&0x3ff00)<<14)|((version&63)<<16)|(build&65535);
 return func_002A71E0(stream,&header,12);
}
