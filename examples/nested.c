#include <autoreleasepool/allocs.h>
#include <stdio.h>

int main() {
    autoreleasepool (
        char *c = charAlloc(53);

        autoreleasepool (
            int *i = intAlloc(10);
            {
                int iter = 0;

                while (iter < 10) {
                    i[iter] = iter;
                    printf("%i ", i[iter]);
                    iter++;
                }
            }
        )

        if (c) {
            for (int iter = 0; iter < 53; ++iter) {
                c[iter] = 'A' + iter;
            }
            c[52] = '\0';

            printf("\nString: %s\n", c);
        }
    )

    return 0;
}
