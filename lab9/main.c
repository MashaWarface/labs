#include "dijkstra.h"
#include <stdio.h>

int main(void) {
    int NodeCount, Start, Finish, EdgeCount;
    scanf("%d %d %d %d", &NodeCount, &Start, &Finish, &EdgeCount);
    unsigned int **weights = MakeMatrix(NodeCount, Start, Finish, EdgeCount);

    if (weights == 0)
        return 0;

    dijkstra(weights, NodeCount, Start, Finish);

    Free(weights, NodeCount);

    return 0;
}
