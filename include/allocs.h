#ifndef allocs_h
#define allocs_h

#include "autoreleasepool.h"

#define alloc_b(type, wantSize) (type*)alloc(sizeof(type)*wantSize)

#define charAlloc   (char*)alloc
#define intAlloc    (int*)alloc
#define longAlloc   (long*)alloc
#define floatAlloc  (float*)alloc
#define doubleAlloc (double*)alloc

#endif
