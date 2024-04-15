
#define NODE struct node
#define LIST struct list

NODE {
    int Vertex;
    NODE *Next;
};

LIST {
    NODE *First;
};

NODE *CreateNode(int Vertex);

void Insert(LIST *Graph, int MainVertex, int AdjVertex);

LIST *CreateGraph(int NodeCount);

int FillGraph(LIST *Graph, int NodeCount, int EdgesCount);