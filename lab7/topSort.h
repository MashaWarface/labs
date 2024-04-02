#ifndef LAB7_TOPSORT_H
#define LAB7_TOPSORT_H

#define NODE struct node
#define LIST struct list
#define STACK struct stack

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

void Push(STACK *Stack, int Vertex);

void Pop(STACK *Stack);

LIST *CreateGraph(int NodeCount);

int FillGraph(LIST *Graph, int NodeCount, int EdgesCount);

NODE *CreateNode(int Vertex);

void Insert(LIST *Graph, int MainVertex, int IncVertex);

void CycleDFS(LIST *Graph, int *Colour, int Vertex, int *Cycle);

int IsCycled(LIST *Graph, int *Colour, int NodeCount, int Cycle);

void DFS(LIST *Graph, STACK *Stack, int Vertex, int *Visited);

void TopSort(LIST *Graph, STACK *Stack, int *Visited, int NodeCount);

int Errors(int NodeCount, int EdgesCount, int Start, int End, int Cycle);

#endif
