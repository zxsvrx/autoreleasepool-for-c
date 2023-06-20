/*
 autoreleasepool-for-c
 
 Copyright (c) 2023 zxsvrx
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "autoreleasepool.h"

Autoreleasepool *globalPool = NULL;

Autoreleasepool *CreateAutoreleasepool() {
    Autoreleasepool *pool = (Autoreleasepool*) malloc(sizeof(Autoreleasepool));

    if (pool == NULL) {
        printf("[AutoReleaseError in CreateAutoreleasepool: failed to allocate Autoreleasepool]\n");
        return NULL;
    }

    if (globalPool != NULL) {
        globalPool->next = pool;
        pool->prev = globalPool;
        pool->next = NULL;
        pool->size = 0;
        pool->allocated = NULL;
        globalPool = pool;
    }
    else {
        globalPool = pool;
    }

    return pool;
}

void *AutoreleaseAlloc(int bytes) {
    if (globalPool != NULL) {
        void *alloc = malloc(bytes);
        // check for valid pool->allocated!
        void **buffer = (void**)realloc(globalPool->allocated, ++globalPool->size);
        if (buffer == NULL) {
            printf("[AutoReleaseError in AutoreleaseAlloc: failed to allocate memory (%i bytes)]\n", bytes);
            free(alloc);
            return NULL;
        }
        globalPool->allocated = buffer;
        globalPool->allocated[globalPool->size-1] = alloc;
        return alloc;
    }
    printf("[AutoReleaseError in AutoreleaseAlloc: no pool found]\n");
    return NULL;
}

void *AddAutoreleaseAllocToPool(Autoreleasepool *pool, int bytes) {
 if (pool != NULL) {
        void *alloc = malloc(bytes);
  // check for valid pool->allocated!
        void **buffer = (void**)realloc(pool->allocated, ++pool->size);
        if (buffer == NULL) {
            printf("[AutoReleaseError in AutoreleaseAlloc: failed to allocate memory (%i bytes)]\n", bytes);
            free(alloc);
            return NULL;
        }
        pool->allocated = buffer;
        pool->allocated[globalPool->size-1] = alloc;
        return alloc;
    }
    printf("[AutoReleaseError in AutoreleaseAlloc: no pool found]\n");
    return NULL;
}

void ReleaseAutoreleasepool(Autoreleasepool *pool) {
    if (pool == NULL) {
        return;
    }

    if (pool->allocated != NULL) {
        for (int iter = 0; iter < pool->size; ++iter) {
            free(pool->allocated[iter]);
        }

        free(pool->allocated);
    }

    if (pool->prev != NULL) {
        pool->prev = (pool->next != NULL ? pool->next : NULL);
    }

    if (pool->next != NULL) {
        pool->next = (pool->prev != NULL ? pool->prev : NULL);
    }
    else {
        // this is globalPool
        globalPool = (pool->prev != NULL ? pool->prev : NULL);
    }

    free(pool);
}

void ReleaseCurrentPool() {
    ReleaseAutoreleasepool(globalPool);
}
