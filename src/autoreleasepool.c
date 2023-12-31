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
        pool->useNext = NULL;
        pool->allocated = NULL;
        globalPool = pool;
    }
    else {
        globalPool = pool;
    }

    return pool;
}

void *AutoreleaseAlloc(int bytes) {
    return NewAutoreleaseAllocToPool(globalPool, bytes);
}

void *NewAutoreleaseAllocToPool(Autoreleasepool *pool, int bytes) {
     if (pool != NULL) {
        void *alloc = malloc(bytes);
        if (alloc == NULL) {
            printf("[AutoReleaseError in NewAutoreleaseAllocToPool: failed to allocate memory (%i bytes)]\n", bytes);
            return NULL;
        }
        char **buffer = (void**)realloc(allocated, (++pool->size)*sizeof(void*));
        if (buffer == NULL) {
            printf("[AutoReleaseError in NewAutoreleaseAllocToPool: failed to allocate memory (%i bytes)]\n", (pool->size)*sizeof(void*));
            free(alloc);
            size--;
            return NULL;
        }
        pool->allocated = buffer;
        pool->allocated[globalPool->size-1] = alloc;
        return alloc;
    }
    printf("[AutoReleaseError in NewAutoreleaseAllocToPool: no pool found matching %p]\n", pool);
    return NULL;
}

void *PreservedAutoreleaseAlloc(int bytes) {
    if (globalPool == NULL) {
        printf("[AutoReleaseError in PeservedAutoreleaseAlloc: no pool found]\n",);
        return NULL;
    }
     
    Autoreleasepool *prev = globalPool->prev;
    Autoreleasepool *pool = globalPool;
    while (prev != NULL) {
        pool = prev;
        prev = pool->prev;
    }
    return NewAutoreleaseAllocToPool(pool, bytes);
}

void AddAutoreleaseAllocToPool(Autoreleasepool *pool, void *allocated) {
    if (allocated == NULL) {
        return;
    }
 
    if (pool == NULL) {
        printf("[AutoReleaseError in AddAutoreleaseAllocToPool: no pool found matching %p]\n", pool);
        return;
    }

    if (pool->allocated == NULL) {
        pool->allocated = (void**)malloc(sizeof(void*));
        pool->size++;
    }
    else {
        void **buffer = (void**)realloc(pool->allocated, (++pool->size)*sizeof(void*));
        if (buffer == NULL) {
            printf("[AutoReleaseError in AddAutoreleaseAllocToPool: failed to allocate memory (%i bytes)]\n", (pool->size)*sizeof(void*));
            return;
        }
        pool->allocated = buffer;
    }
    pool->allocated[pool->size-1] = allocated;
}

void *AutoreleaseRealloc(Autoreleasepool *pool, void *allocated, int bytes) {
    if (allocated == NULL) {
        return NULL;
    }
    
    if (pool == NULL) {
        printf("[AutoReleaseError in AutoreleaseRealloc: no pool found matching %p]\n", pool);
        return NULL;
    }

    // find allocated in pool by iterating
    for (int iter = 0; iter < pool->size; ++iter) {
        if (allocated == pool->allocated[iter]) {
            void *buffer = realloc(allocated, bytes);
            if (buffer == NULL) {
                printf("[AutoReleaseError in AutoreleaseRealloc: failed to allocate memory (%i bytes)]\n", (pool->size)*sizeof(void*));
                return NULL;
            }
            pool->allocated[iter] = buffer;
            return buffer;
        }
    }
    return NULL;
}

void ReleaseFromPool(Autoreleasepool *pool, void *allocated) {
    if (allocated == NULL) {
        return;
    }
 
    if (pool == NULL) {
        printf("[AutoReleaseError in ReleaseFromPool: no pool found matching %p]\n", pool);
        return;
    }
    
    // find allocated in pool by iterating
    for (int iter = 0; iter < pool->size; ++iter) {
        if (pool->allocated[iter] == allocated) {
            free(pool->allocated[iter]);
            // mark free position in allocation array to be used next
            if (pool->useNext == NULL) {
                useNext = pool->allocated[iter];
            }
            else {
                // we now point to an empty element and become the element to be use next
                pool->allocated[iter] = useNext;
                useNext = pool->allocated[iter];
            }
            return;
        }
    }
}

void ReleaseFromCurrentPool(void *allocated) {
    ReleaseFromPool(globalPool, allocated);
}

void ReleaseAutoreleasepool(Autoreleasepool *pool) {
    if (pool == NULL) {
        printf("[AutoReleaseError in ReleaseAutoreleasepool: no pool found matching %p]\n", pool);
        return;
    }

    if (pool->allocated != NULL) {
        for (int iter = 0; iter < pool->size; ++iter) {
            free(pool->allocated[iter]);
        }

        free(pool->allocated);
    }

    // transfer pointer to next pool to previous pool
    if (pool->prev != NULL) {
        pool->prev = (pool->next != NULL ? pool->next : NULL);
    }

    // and transfer pointer to prev pool to next pool
    if (pool->next != NULL) {
        pool->next = (pool->prev != NULL ? pool->prev : NULL);
    }
    else {
        // if there is no next pool, we were the globalPool so we have to set the prev pool as next globalPool
        globalPool = (pool->prev != NULL ? pool->prev : NULL);
    }

    free(pool);
}

void ReleaseCurrentPool() {
    ReleaseAutoreleasepool(globalPool);
}
