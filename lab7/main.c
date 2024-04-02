#include "topSort.h"
#include "stdio.h"
#include "malloc.h"

int main(void) {
    int NodeCount, EdgesCount, Cycle = 0;
    int *Visited = NULL, *Colour = NULL;
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

    Visited = malloc(NodeCount * sizeof(int));
    for (int i = 0; i < NodeCount; i++)
        *(Visited + i) = 0;
    Colour = malloc(NodeCount * sizeof(int));
    for (int i = 0; i < NodeCount; i++)
        *(Colour + i) = 0;

    Cycle = IsCycled(Graph, Colour, NodeCount, Cycle);

    if (!Errors(NodeCount, EdgesCount, 1, 1, Cycle))
        return 0;

    TopSort(Graph, Vertices, Visited, NodeCount);

    free(Vertices);
    free(Visited);
    free(Colour);

    return 0;
}
