#include "kruscal.h"
#include <stdlib.h>
#include "stdio.h"

int main(void) {
    int NodeCount, EdgesCount;
    EDGE *List = NULL;

    scanf("%d %d", &NodeCount, &EdgesCount);

    if (NodeCount == 1) {
        puts("");
        return 0;
    }

    List = makeList(List, NodeCount, EdgesCount);
    if (List == 0)
        return 0;

    Kruskal(List, NodeCount, EdgesCount);

    return 0;
}
