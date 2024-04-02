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

LIST *CreateGraph(int NodeCount);

NODE *CreateNode(int Vertex);

STACK *Create(int Vertex);

void Push(STACK *Stack, int Vertex);

void Pop(STACK *Stack);

void Insert(LIST *Graph, int MainVertex, int IncVertex);

int FillGraph(LIST *Graph, int NodeCount, int EdgesCount);

void DFS(LIST *Graph, STACK *Stack, int Vertex, int *Visited);

int IsCycled(LIST *Graph, int NodeCount);

void CycleDFS(LIST *Graph, int Vertex, int *Colour, int *Cycle);

void TopSort(LIST *Graph, STACK *Stack, int *Visited, int NodeCount);

int Errors(int NodeCount, int EdgesCount, int Start, int End, int Cycle);

#endif
