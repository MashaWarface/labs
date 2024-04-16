#include "kosaraju.h"
#include "stdio.h"

int main(void) {
    int NodeCount, EdgesCount, *Visited = NULL;
    LIST *Graph = NULL, *InvertGraph = NULL;

    Graph = FillGraph(Graph, &NodeCount, &EdgesCount);

    Kosaraju(Graph, InvertGraph, Visited, NodeCount);

    return 0;
}
