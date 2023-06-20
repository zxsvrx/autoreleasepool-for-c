#include <autoreleasepool.h>

int main() {
  
  autoreleasepool (
    char * str = (char*)alloc(53);
    
    for (int iter = 0; iter < 52; ++iter) {
      str[iter] = 'A' + iter;
    }
    str[52] = '\0';
    
    printf("String: %s\n", str);
  )
  
  return 0;
}
