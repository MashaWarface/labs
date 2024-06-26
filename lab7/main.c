#include "topSort.h"
#include "stdio.h"
#include "malloc.h"

int main(void) {
    int NodeCount, EdgesCount, Cycle = 0;
    int *Colour = NULL;
    LIST *Graph = NULL;
    STACK *Vertices = NULL;

    Vertices = Create(0);

    if (scanf("%d %d", &NodeCount, &EdgesCount) != 2) {
        puts("bad number of lines");
        return 0;
    }

    Graph = CreateGraph(NodeCount);
    if (!FillGraph(Graph, NodeCount, EdgesCount))
        return 0;

    Colour = malloc(NodeCount * sizeof(int));
    for (int i = 0; i < NodeCount; i++)
        *(Colour + i) = WHITE;

    if (!Errors(NodeCount, EdgesCount, 1, 1))
        return 0;

    TopSort(Graph, Vertices, Colour, NodeCount, Cycle);

    free(Vertices);
    free(Colour);

    return 0;
}
