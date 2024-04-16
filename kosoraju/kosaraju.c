#include "kosaraju.h"
#include "stdio.h"
#include "malloc.h"

LIST *Invert(LIST *Graph, int NodeCount) {
    LIST *InvertGraph = CreateGraph(NodeCount);

    for (int i = 0; i < NodeCount; i++) {
        NODE *CurNode = (Graph + i)->First;
        while (CurNode) {
            Insert(InvertGraph, CurNode->Vertex, i);
            CurNode = CurNode->Next;
        }
    }
    return InvertGraph;
}

void DFS(LIST *Graph, STACK *Vertices, int *Visited, int Vertex) {
    *(Visited + Vertex) = 1;
    NODE *CurNode = (Graph + Vertex)->First;

    while (CurNode) {
        int AdjVertex = CurNode->Vertex;
        if (*(Visited + AdjVertex) == 0)
            DFS(Graph, Vertices, Visited, AdjVertex);
        CurNode = CurNode->Next;
    }

    Push(Vertices, Vertex);

}

void FullDFS(LIST *Graph, STACK *Vertices, int *Visited, int NodeCount) {
    Visited = malloc(NodeCount * sizeof(int));
    for (int i = 0; i < NodeCount; i++)
        *(Visited + i) = 0;

    for (int i = 0; i < NodeCount; i++)
        if (*(Visited + i) == 0)
            DFS(Graph, Vertices, Visited, i);
}

void PrintSCC(STACK *SCC, int Number) {
    puts("");
    printf("%d Component: ", Number);
    while (SCC->Next)
        printf("%d ", Pop(SCC));
}

void Kosaraju(LIST *Graph, LIST *InvertGraph, int *Visited, int NodeCount) {
    STACK *SCC = NULL, *Vertices = NULL;
    int Vertex, Component = 0;
    Vertices = Create(0);
    SCC = Create(0);

    FullDFS(Graph, Vertices, Visited, NodeCount);

    InvertGraph = Invert(Graph, NodeCount);

    Visited = malloc(NodeCount * sizeof(int));
    for (int i = 0; i < NodeCount; i++)
        *(Visited + i) = 0;

    for (int i = 0; i < NodeCount; i++) {
        Vertex = Pop(Vertices);
        if (*(Visited + Vertex) == 0) {
            DFS(InvertGraph, SCC, Visited, Vertex);
            Component++;
            PrintSCC(SCC, Component);
        }
    }
}
