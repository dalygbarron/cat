#include "pack.h"
#include "util.h"

int treePack(
    struct Picture **pictures,
    int n,
    float (*comparison)(struct Picture const *in)
) {
    sort(pictures, n, comparison);
    int x = 0;
    for (int i = 0; i < n; i++) {
        pictures[i]->x = x;
        x += pictures[i]->width;
    }
    return 1;
}
