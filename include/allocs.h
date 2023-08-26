#ifndef allocs_h
#define allocs_h

#include "autoreleasepool.h"

#define alloc_b(type, n) (type*)alloc(sizeof(type)*n)
#define preserve(type, n) (type*)PreservedAutoreleaseAlloc(type, n)
#define realloc_b(type, pool, n) (type*)AutpreleaseRealloc(pool, type, n)
#define release(alloc) ReleaseFromCurrentPool(alloc)

#define charAlloc(n)    (char*)alloc(sizeof(char)*n)
#define intAlloc(n)     (int*)alloc(sizeof(int)*n)
#define longAlloc(n)    (long*)alloc(sizeof(long)*n)
#define floatAlloc(n)   (float*)alloc(sizeof(float)*n)
#define doubleAlloc(n)  (double*)alloc(sizeof(double)*n)

#define charRealloc(pool, ptr, n)   (char*)AutoreleaseRealloc(pool, ptr, sizeof(char)*n)
#define intRealloc(pool, ptr, n)    (int*)AutoreleaseRealloc(pool, ptr, sizeof(int)*n)
#define longRealloc(pool, ptr, n)   (long*)AutoreleaseRealloc(pool, ptr, sizeof(long)*n)
#define floatRealloc(pool, ptr, n)  (float*)AutoreleaseRealloc(pool, ptr, sizeof(float)*n)
#define doublRealloc(pool, ptr, n)  (double*)AutoreleaseRealloc(pool, ptr, sizeof(double)*n)

#endif
