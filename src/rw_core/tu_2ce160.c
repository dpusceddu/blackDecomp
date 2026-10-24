// RenderWare immediate-mode plugin; names inferred from operations.
#include "rw_core/im3d_operations.h"

void *func_002CE7C8(void *instance) {
 func_002CF5D8(&IM3D_PLUGIN->defaultTriangleFan);func_002CF5D0(&IM3D_PLUGIN->defaultTriangleList);D_0040E6EC--;return instance;
}

void *func_002CE848(int primitive) {
 void *pipeline=0;
 switch(primitive) {
 case 3:pipeline=IM3D_PLUGIN->triangleList;break;
 case 5:pipeline=IM3D_PLUGIN->triangleFan;break;
 case 4:pipeline=IM3D_PLUGIN->triangleStrip;break;
 case 1:pipeline=IM3D_PLUGIN->lineList;break;
 case 2:pipeline=IM3D_PLUGIN->polyLine;break;
 case 6:pipeline=IM3D_PLUGIN->pointList;break;
 default:{RwImErrorView error;error.plugin=1;error.error=func_002A5548(0x25,primitive);func_002A55D8(&error);}
 }
 return pipeline;
}

// Unmatched: func_002CE160 needs matching pipeline switch and callback lifetime scheduling.
// Unmatched: func_002CE2F0 needs matching pipeline switch and callback lifetime scheduling.
// Unmatched: func_002CE470 needs matching pipeline switch and callback lifetime scheduling.
// Unmatched: func_002CE708 needs matching pipeline switch and callback lifetime scheduling.
// Unmatched: func_002CE828 needs matching pipeline switch and callback lifetime scheduling.
// Unmatched: func_002CE948 needs matching pipeline switch and callback lifetime scheduling.
