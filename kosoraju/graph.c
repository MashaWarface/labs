#include "graph.h"
#include "malloc.h"
#include "stdio.h"

NODE *CreateNode(int Vertex) {
    NODE *Node = malloc(sizeof(NODE));
    Node->Vertex = Vertex;
    Node->Next = NULL;
    return Node;
}

void Insert(LIST *Graph, int MainVertex, int AdjVertex) {
    NODE *Node = CreateNode(AdjVertex);
    Node->Next = (Graph + MainVertex)->First;
    (Graph + MainVertex)->First = Node;
}

LIST *CreateGraph(int NodeCount) {
    LIST *Graph = malloc(NodeCount * sizeof(LIST));
    for (int i = 0; i < NodeCount; i++)
        (Graph + i)->First = NULL;
    return Graph;
}

LIST *FillGraph(LIST *Graph, int *NodeCount, int *EdgesCount) {
    int Start, End;

    scanf("%d %d", NodeCount, EdgesCount);

    Graph = CreateGraph(*NodeCount);

    for (int i = 0; i < *EdgesCount; i++) {
        if (scanf("%d %d", &Start, &End) != 2)
            return 0;
        Insert(Graph, Start, End);
    }

    return Graph;
}
