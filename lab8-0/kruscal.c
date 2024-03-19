#include "kruscal.h"
#include "stdlib.h"
#include "stdio.h"
#include "limits.h"

int Errors(int NodeCount, int Start, int Finish, int EdgesCount, unsigned int Length) {
    if (NodeCount == 0 || EdgesCount == 0) {
        puts("no spanning tree");
        return 0;
    }
    if (Start < 1 || Start > NodeCount || Finish < 1 || Finish > NodeCount) {
        puts("bad vertex");
        return 0;
    }
    if (NodeCount < 0 || NodeCount > 5000) {
        puts("bad number of vertices");
        return 0;
    }
    if (EdgesCount < 0 || EdgesCount > NodeCount * (NodeCount + 1) / 2) {
        puts("bad number of edges");
        return 0;
    }
    if (Length > INT_MAX) {
        puts("bad length");
        return 0;
    }
    return 1;
}

EDGE *init(int start, int finish, unsigned int length) {
    EDGE *new = malloc(sizeof(EDGE));
    new->start = start;
    new->finish = finish;
    new->length = length;
    return new;
}

int compareEdges(const void *a, const void *b) {
    return ((EDGE *) a)->length - ((EDGE *) b)->length;
}

EDGE *makeList(EDGE *List, int NodeCount, int EdgesCount) {
    int start, finish;
    unsigned int length;
    EDGE *edge;

    if (!Errors(NodeCount, 1, 1, EdgesCount, INT_MAX))
        return 0;

    List = malloc(EdgesCount * sizeof(EDGE *));

    for (int i = 0; i < EdgesCount; i++) {
        if (scanf("%d %d %u", &start, &finish, &length) != 3) {
            puts("bad number of lines");
            return 0;
        }
        if (!Errors(NodeCount, start, finish, EdgesCount, length))
            return 0;
        if (NodeCount - EdgesCount > 1) {
            puts("no spanning tree");
            return 0;
        }
        edge = init(start, finish, length);
        List[i] = *edge;
    }

    qsort(List, EdgesCount, sizeof(EDGE), compareEdges);
    return List;
}

int find(int *list, int length, int a) {
    for (int i = 0; i < length; i++)
        if (a == list[i])
            return 1;
    return 0;
}

void fillEdges(int **Edges, int ind, int start, int finish) {
    if (start < finish) {
        Edges[ind][0] = start;
        Edges[ind][1] = finish;
    } else {
        Edges[ind][1] = start;
        Edges[ind][0] = finish;
    }
}

void Kruskal(EDGE *List, int NodeCount, int EdgesCount) {
    int *Vertices, indexList = 0, indexVert = 0, indexEdges = 0;
    EDGE *edge;
    int **Edges;

    Edges = malloc(EdgesCount * sizeof(int *));
    for (int i = 0; i < NodeCount - 1; i++)
        Edges[i] = malloc(2 * sizeof(int));

    Vertices = malloc(NodeCount * sizeof(int));

    for (int i = 0; i < NodeCount; i++)
        Vertices[i] = 0;

    while (indexList < EdgesCount) {
        edge = &List[indexList++];

        if (find(Vertices, NodeCount, edge->start) && find(Vertices, NodeCount, edge->finish))
            continue;
        else if (find(Vertices, NodeCount, edge->start)) {
            Vertices[indexVert++] = edge->finish;
            fillEdges(Edges, indexEdges++, edge->start, edge->finish);
        } else if (find(Vertices, NodeCount, edge->finish)) {
            Vertices[indexVert++] = edge->start;
            fillEdges(Edges, indexEdges++, edge->start, edge->finish);
        } else {
            Vertices[indexVert++] = edge->start;
            Vertices[indexVert++] = edge->finish;
            fillEdges(Edges, indexEdges++, edge->start, edge->finish);
        }
    }

    if (EdgesCount == 1) {
        puts("no spanning tree");
        return;
    }

    if (find(Vertices, NodeCount, 0)) {
        puts("no spanning tree");
        return;
    }

    for (int i = 0; i < NodeCount - 1; i++)
        printf("%d %d\n", Edges[i][0], Edges[i][1]);
}
