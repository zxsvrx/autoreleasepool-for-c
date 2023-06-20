#include "autoreleasepool.h"

Autoreleasepool *globalPool = NULL;

Autoreleasepool *CreateAutoreleasepool() {
    Autoreleasepool *pool = (MMReleasePool*) malloc(sizeof(MMReleasePool));

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
        void **buffer = (void**)realloc(globalPool->allocated, ++globalPool->size);
        if (buffer == NULL) {
            printf("[AutoReleaseError in AutoreleaseAlloc: failed to allocate memory (%i bytes)]\n", bytes);
            return NULL;
        }
        globalPool->allocated = buffer;
        globalPool->allocated[globalPool->size-1] = alloc;
        return alloc;
    }
    printf("[AutoReleaseError in MMAlloc: no pool found]\n");
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
