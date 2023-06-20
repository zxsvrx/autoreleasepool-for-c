#ifndef allocs_h
#define allocs_h

#include "autoreleasepool.h"

#define alloc_b(type, wantSize) (type*)alloc(sizeof(type)*wantSize)

#define charAlloc(n)    (char*)alloc(sizeof(char)*n)
#define intAlloc(n)     (int*)alloc(sizeof(int)*n)
#define longAlloc(n)    (long*)alloc(sizeof(long)*n)
#define floatAlloc(n)   (float*)alloc(sizeof(float)*n)
#define doubleAlloc(n)  (double*)alloc(sizeof(double)*n)

#endif
