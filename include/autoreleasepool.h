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

#ifndef autoreleasepool_h
#define autoreleasepool_h

#include <stdlib.h>
#include <stdio.h>

#define autoreleasepool(x) CreateAutoreleasepool(); x ReleaseCurrentPool();

#define alloc(x) AutoreleaseAlloc(x)

struct Autoreleasepool {
    void **allocated;
    void *useNext;
    int size;
    struct Autoreleasepool *next;
    struct Autoreleasepool *prev;
};

typedef struct Autoreleasepool Autoreleasepool;

Autoreleasepool *CreateAutoreleasepool(void);

void *AutoreleaseAlloc(int bytes);
void *NewAutoreleaseAllocToPool(Autoreleasepool *pool, int bytes);
// gets passed to the first autoreleasealloc for now; maybe move to last released
void *PreservedAutoreleaseAlloc(int bytes);

// bytes = new bytes not old bytes + new bytes
void *AutoreleaseRealloc(void *source, int bytes);

void *AddAutoreleaseAllocToPool(Autoreleasepool *pool, void *allocated, int bytes);

void ReleaseFromCurrentPool(void *allocated);
void ReleaseFromPool(Autoreleasepool *pool, void *allocated);

void ReleaseCurrentPool(void);
void ReleaseAutoreleasepool(Autoreleasepool *pool);


#endif
