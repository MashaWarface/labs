#ifndef LAB7_TOPSORT_H
#define LAB7_TOPSORT_H

#define NODE struct node
#define LIST struct list
#define STACK struct stack

#define BLACK 1
#define GREY -1
#define WHITE 0

NODE {
    int Vertex;
    NODE *Next;
};

LIST {
    NODE *First;
};

STACK {
    int Vertex;
    STACK *Next;
};

STACK *Create(int Vertex);

void Push(STACK *Vertices, int Vertex);

void Pop(STACK *Vertices);

LIST *CreateGraph(int NodeCount);

int FillGraph(LIST *Graph, int NodeCount, int EdgesCount);

NODE *CreateNode(int Vertex);

void Insert(LIST *Graph, int MainVertex, int AdjVertex);

void DFS(LIST *Graph, STACK *Vertices, int *Colour, int Vertex, int *Cycle);

void TopSort(LIST *Graph, STACK *Vertices, int *Colour, int NodeCount, int Cycle);

int Errors(int NodeCount, int EdgesCount, int Start, int End);

#endif
