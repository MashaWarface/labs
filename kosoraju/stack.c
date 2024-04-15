#include "stack.h"

#include "stdio.h"
#include "malloc.h"

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

int Pop(STACK *Vertices) {
    if (Vertices->Next) {
        STACK *OldElement = Vertices->Next;
        Vertices->Next = OldElement->Next;
        int r = OldElement->Vertex;
        free(OldElement);
        return r;
    }
    return 0;
}