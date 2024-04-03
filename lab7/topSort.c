#include "topSort.h"
#include "stdio.h"
#include "malloc.h"

int Errors(int NodeCount, int EdgesCount, int Start, int End) {
    if (NodeCount < 0 || NodeCount > 2000) {
        puts("bad number of vertices");
        return 0;
    }
    if (EdgesCount < 0 || EdgesCount > NodeCount * (NodeCount + 1) / 2) {
        puts("bad number of edges");
        return 0;
    }
    if (Start < 1 || Start > NodeCount || End < 1 || End > NodeCount) {
        puts("bad vertex");
        return 0;
    }
    return 1;
}

STACK *Create(int Vertex) {
    STACK *NewElement;
    NewElement = malloc(sizeof(STACK));
    NewElement->Vertex = Vertex;
    NewElement->Next = NULL;
    return NewElement;
}

void Push(STACK *Vertices, int Vertex) {
    STACK *NewElement = Create(Vertex);
    STACK *OldElement = Vertices->Next;
    NewElement->Next = OldElement;
    Vertices->Next = NewElement;
}

void Pop(STACK *Vertices) {
    if (Vertices->Next) {
        STACK *OldElement = Vertices->Next;
        Vertices->Next = OldElement->Next;
        printf("%d ", OldElement->Vertex + 1);
        free(OldElement);
    }
}

LIST *CreateGraph(int NodeCount) {
    LIST *Graph = malloc(NodeCount * sizeof(LIST));
    for (int i = 0; i < NodeCount; i++)
        (Graph + i)->First = NULL;
    return Graph;
}

int FillGraph(LIST *Graph, int NodeCount, int EdgesCount) {
    int Start, End;

    for (int i = 0; i < EdgesCount; i++) {
        if (scanf("%d %d", &Start, &End) != 2) {
            puts("bad number of lines");
            return 0;
        }
        if (!(Errors(NodeCount, EdgesCount, Start, End)))
            return 0;
        Insert(Graph, Start, End);
    }

    return 1;
}

NODE *CreateNode(int Vertex) {
    NODE *Node = malloc(sizeof(NODE));
    Node->Vertex = Vertex;
    Node->Next = NULL;
    return Node;
}

void Insert(LIST *Graph, int MainVertex, int IncVertex) {
    IncVertex--;
    NODE *Node = CreateNode(IncVertex);
    Node->Next = (Graph + MainVertex - 1)->First;
    (Graph + MainVertex - 1)->First = Node;
}

void DFS(LIST *Graph, STACK *Vertices, int *Colour, int Vertex, int *Cycle) {
    *(Colour + Vertex) = GREY;
    NODE *CurNode = (Graph + Vertex)->First;

    while (CurNode != NULL) {
        int IncVertex = CurNode->Vertex;
        if (*(Colour + IncVertex) == GREY) {
            *Cycle = 1;
            return;
        }
        if (*(Colour + IncVertex) == WHITE)
            DFS(Graph, Vertices, Colour, IncVertex, Cycle);
        CurNode = CurNode->Next;
    }

    *(Colour + Vertex) = BLACK;
    Push(Vertices, Vertex);
}

void TopSort(LIST *Graph, STACK *Vertices, int *Colour, int NodeCount, int Cycle) {
    for (int i = 0; i < NodeCount; i++)
        if (*(Colour + i) == WHITE)
            DFS(Graph, Vertices, Colour, i, &Cycle);

    if (Cycle == 1) {
        puts("impossible to sort");
        return;
    }

    while (Vertices->Next)
        Pop(Vertices);
}
