#include "prim.h"
#include "stdio.h"

int main(void) {
    int NodeCount, EdgesCount;
    unsigned int **Matrix = NULL;

    scanf("%d %d", &NodeCount, &EdgesCount);

    if (NodeCount == 1) {
        puts("");
        return 0;
    }

    Prim(Matrix, NodeCount, EdgesCount);
    return 0;
}
