#include <autoreleasepool/allocs.h>
#include <stdio.h>

struct Point3d {
  int x1;
  int x2;
  int x3;
};

int main() {
  autoreleasepool (
    int n = 0;
    
    printf("How many points do you want: ");
    scanf("%i", n);
    
    Point3d *points = alloc_b(Point3d, n);
  )
  return 0;
}
