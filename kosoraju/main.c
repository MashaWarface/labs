#include "graph.h"
#include "stack.h"

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

void DFS(LIST *Graph, STACK *Vertices, int *Visited, int Vertex, int Number) {
    *(Visited + Vertex) = Number;
    NODE *CurNode = (Graph + Vertex)->First;

    while (CurNode) {
        int AdjVertex = CurNode->Vertex;
        if (*(Visited + AdjVertex) == Number - 1)
            DFS(Graph, Vertices, Visited, AdjVertex, Number);
        CurNode = CurNode->Next;
    }

    Push(Vertices, Vertex);

}

void FullDFS(LIST *Graph, STACK *Vertices, int *Visited, int NodeCount) {
    int Number = 1;
    for (int i = 0; i < NodeCount; i++)
        if (*(Visited + i) == 0)
            DFS(Graph, Vertices, Visited, i, Number);
}

void PrintSCC(STACK *SCC, int Number) {
    puts("");
    printf("%d Component: ", Number);
    while (SCC->Next)
        printf("%d ", Pop(SCC));
}

void Kosaraju(LIST *InvertGraph, int *Visited, int NodeCount, STACK *Vertices) {
    STACK *SCC = NULL;
    int Number = 2, Component = 0;
    SCC = Create(0);
    int Vertex;

    for (int i = 0; i < NodeCount; i++) {
        Vertex = Pop(Vertices);
        if (*(Visited + Vertex) == Number - 1) {
            DFS(InvertGraph, SCC, Visited, Vertex, Number);
            Component++;
            PrintSCC(SCC, Component);
        }
    }
}

int main(void) {
    int NodeCount, EdgesCount;
    int *Visited;
    STACK *Vertices = NULL;
    LIST *Graph = NULL, *InvertGraph = NULL;

    Vertices = Create(0);

    if (scanf("%d %d", &NodeCount, &EdgesCount) != 2)
        return 0;

    Graph = CreateGraph(NodeCount);

    if (!FillGraph(Graph, NodeCount, EdgesCount))
        return 0;

    InvertGraph = Invert(Graph, NodeCount);

    Visited = malloc(NodeCount * sizeof(int));
    for (int i = 0; i < NodeCount; i++)
        *(Visited + i) = 0;

    FullDFS(Graph, Vertices, Visited, NodeCount);

    Kosaraju(InvertGraph, Visited, NodeCount, Vertices);

    return 0;
}
