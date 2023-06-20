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
using `allocs.h`
``` c
...
autoreleasepool (
  // your code (again)
  // e.g.:
  yourStruct *instance = alloc_b(yourStruct, 16);
)
```

More examples can be found in the example folder.

## Building

To build a static library (libARPC) do the following:
1. Create a folder called `build`
2. In the folder `build` run `cmake ..` (make sure cmake is installed`
3. Now run `make`
4. You will find the static library in the build folder.


