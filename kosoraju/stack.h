
#define STACK struct stack

STACK {
    int Vertex;
    STACK *Next;
};

STACK *Create(int Vertex);

void Push(STACK *Vertices, int Vertex);

int Pop(STACK *Vertices);
