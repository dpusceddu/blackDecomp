#include "include_asm.h"

// RenderWare image quantization; names inferred from operations.
#include "rw_core/quantize.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002AF800);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002AF938);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002AFA48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002AFB90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002AFCB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002AFDB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B0290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B04D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B0780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B0DA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B17C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B1E60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B1E68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B1F90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2af800", func_002B20B0);

int func_002B2288(QuantNode *node,int depth) {
 int count=0;
 if(node) {QuantNode **child=node->child;
  if(depth>0){int next=depth-1;QuantNode **scan=child;do {
   count+=func_002B2288(scan[0],next);count+=func_002B2288(scan[1],next);count+=func_002B2288(scan[2],next);count+=func_002B2288(scan[3],next);count+=func_002B2288(scan[4],next);count+=func_002B2288(scan[5],next);count+=func_002B2288(scan[6],next);count+=func_002B2288(scan[7],next);
   child+=8;scan+=8;
  }while((int)child<(int)(node->child+16));}else count=1;
 }
 return count;
}

unsigned char func_002B24D0(QuantNode *node, unsigned long path, int depth) {
 unsigned char result;
 if(depth==0) result=node->moments.index;
 else result=func_002B24D0(node->child[(int)(path&15)],path>>4,depth-1);
 return result;
}

// Unmatched: func_002AF800 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002AF938 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002AFA48 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002AFB90 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002AFCB8 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002AFDB0 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B0290 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B04D0 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B0780 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B0DA0 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B17C8 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B1E60 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B1E68 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B1F90 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B20B0 requires recovered quantizer vector temporaries and traversal scheduling.
// Unmatched: func_002B2518 requires recovered quantizer vector temporaries and traversal scheduling.

