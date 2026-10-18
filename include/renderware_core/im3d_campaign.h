#ifndef BLACK_RW_IM3D_CAMPAIGN_H
#define BLACK_RW_IM3D_CAMPAIGN_H
/* Inferred prefixes for immediate-mode pipeline state, from PS2 word accesses. */
typedef struct RwImDrawStateView {unsigned char prefix[32];void *pipeline;int primitive;unsigned short *indices;int count;} RwImDrawStateView;
typedef struct RwIm3DPluginView {
 void *transformPipeline;
 void *triangleList,*triangleFan,*triangleStrip,*lineList,*polyLine,*pointList;
 void *defaultTriangleList,*defaultTriangleFan,*defaultTriangleStrip,*defaultLineList,*defaultPolyLine,*defaultPointList;
 unsigned char reserved34[12];unsigned short indexCount,reserved42;
 void *transformed;unsigned reserved48;RwImDrawStateView draw;
} RwIm3DPluginView;
typedef struct RwImErrorView {int plugin,error;} RwImErrorView __attribute__((aligned(16)));
extern unsigned char D_00449438[];
extern int D_0040E6E8,D_0040E6EC;
extern RwIm3DPluginView *D_0040E0A0;
#define IM3D_PLUGIN ((RwIm3DPluginView *)(D_00449438+D_0040E6E8))
int func_002A5548(int,...);void func_002A55D8(RwImErrorView *);
int func_002CEAE0(void *,RwImDrawStateView *,void *);void func_002CEAD8(void);
void *func_0035C6EC(void *,int,unsigned);
int func_002CF5C0(void **);int func_002CF5C8(void **);void func_002CF5D8(void **);void func_002CF5D0(void **);
#endif
