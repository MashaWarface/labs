#ifndef LAB8_0_KRUSCAL_H
#define LAB8_0_KRUSCAL_H

#define EDGE struct edge

EDGE {
    int start;
    int finish;
    unsigned int length;
};

int Errors(int NodeCount, int Start, int Finish, int EdgesCount, unsigned int Length);

EDGE *makeList(EDGE *List, int NodeCount, int EdgesCount);

int find(int *list, int length, int a);

void fillEdges(int **Edges, int ind, int start, int finish);

void Kruskal(EDGE *List, int NodeCount, int EdgesCount);

#endif
