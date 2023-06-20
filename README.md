# autoreleasepool-for-c

## General

An autoreleasepool library for the c language, which
is capable of creating nested autoreleasepools.

## Limitations

In order to use the autoreleasepool you have to use the provided alloc function(s).

## Recommended example usage:
``` c
...
autoreleasepool (
  // your code
  // e.g.:
  char *str = (char*)alloc(100);
)
...
```
using allocs.h
``` c
...
autoreleasepool (
  // your code (again)
  // e.g.:
  yourStruct *instance = alloc_b(yourStruct, 16);
)
```

More examples can be found in the example folder.
