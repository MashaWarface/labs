#include "topSort.h"
#include "stdio.h"
#include "malloc.h"

int Errors(int NodeCount, int EdgesCount, int Start, int End, int Cycle) {
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
    if (Cycle == 1) {
        puts("impossible to sort");
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

void Push(STACK *Stack, int Vertex) {
    STACK *NewElement = Create(Vertex);
    STACK *OldElement = Stack->Next;
    NewElement->Next = OldElement;
    Stack->Next = NewElement;
}

void Pop(STACK *Stack) {
    if (Stack->Next) {
        STACK *OldElement = Stack->Next;
        Stack->Next = OldElement->Next;
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
        if (!(Errors(NodeCount, EdgesCount, Start, End, 0)))
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

void CycleDFS(LIST *Graph, int *Colour, int Vertex, int *Cycle) {
    *(Colour + Vertex) = -1;        // Black = 1, Gray = -1, White = 0
    NODE *CurNode = (Graph + Vertex)->First;

    while (CurNode != NULL) {
        int IncVertex = CurNode->Vertex;
        if (*(Colour + IncVertex) == -1) {
            *Cycle = 1;
            return;
        }
        CycleDFS(Graph, Colour, IncVertex, Cycle);
        CurNode = CurNode->Next;
    }

    *(Colour + Vertex) = 1;
}

int IsCycled(LIST *Graph, int *Colour, int NodeCount, int Cycle) {
    for (int i = 0; i < NodeCount; i++)
        if (*(Colour + i) == 0)
            CycleDFS(Graph, Colour, i, &Cycle);

    return Cycle;
}


void DFS(LIST *Graph, STACK *Stack, int Vertex, int *Visited) {
    *(Visited + Vertex) = 1;
    NODE *CurNode = (Graph + Vertex)->First;

    while (CurNode != NULL) {
        int IncVertex = CurNode->Vertex;
        if (!(*(Visited + IncVertex)))
            DFS(Graph, Stack, IncVertex, Visited);
        CurNode = CurNode->Next;
    }

    Push(Stack, Vertex);
}

void TopSort(LIST *Graph, STACK *Stack, int *Visited, int NodeCount) {
    for (int i = 0; i < NodeCount; i++)
        if (*(Visited + i) == 0)
            DFS(Graph, Stack, i, Visited);

    while (Stack->Next)
        Pop(Stack);
}
