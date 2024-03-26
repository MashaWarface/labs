#include "malloc.h"
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
    if (NodeCount - EdgesCount > 1) {
        puts("no spanning tree");
        return 0;
    }
    return 1;
}

int find(int *list, int length, int a) {
    for (int i = 0; i < length; i++)
        if (a == list[i])
            return 1;
    return 0;
}

unsigned int **memMatrix(int NodeCount) {
    unsigned int **Matrix = NULL;
    Matrix = malloc(NodeCount * sizeof(int *));

    if (Matrix == NULL)
        return 0;

    for (int i = 0; i < NodeCount; i++) {
        Matrix[i] = malloc(NodeCount * sizeof(int));
        if (Matrix[i] == NULL)
            return 0;
    }

    return Matrix;
}

int fillEdges(unsigned int **Matrix, int NodeCount, int EdgesCount) {
    int start, end, length;
    int *Vertices, index = 0;

    if (!Errors(NodeCount, 1, 1, EdgesCount, INT_MAX))
        return 0;

    Vertices = malloc(NodeCount * sizeof(int));

    for (int i = 0; i < NodeCount; i++)
        Vertices[i] = 0;

    for (int i = 0; i < NodeCount; i++)
        for (int j = 0; j < NodeCount; j++)
            Matrix[i][j] = 0;

    for (int i = 0; i < EdgesCount; i++) {
        if (scanf("%d %d %d", &start, &end, &length) != 3) {
            puts("bad number of lines");
            return 0;
        }
        if (!find(Vertices, NodeCount, start))
            Vertices[index++] = start;
        if (!find(Vertices, NodeCount, end))
            Vertices[index++] = end;
        if (!Errors(NodeCount, start, end, EdgesCount, length))
            return 0;

        Matrix[start - 1][end - 1] = length;
        Matrix[end - 1][start - 1] = length;
    }

    if (find(Vertices, NodeCount, 0)) {
        puts("no spanning tree");
        return 0;
    }
    free(Vertices);
    return 1;
}

unsigned int **makeMatrix(int NodeCount, int EdgesCount) {
    unsigned int **Matrix = memMatrix(NodeCount);

    if (Matrix == NULL)
        return 0;

    if (!fillEdges(Matrix, NodeCount, EdgesCount))
        return 0;

    return Matrix;
}

int minKey(unsigned int *key, int *mstSet, int NodeCount) {
    unsigned int min = UINT_MAX;
    int min_index;

    for (int v = 0; v < NodeCount; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMSTEdges(int *parent, int NodeCount) {
    for (int i = 1; i < NodeCount; i++) {
        printf("%d %d\n", parent[i] + 1, i + 1);
    }
}

void primMST(unsigned int **graph, int NodeCount, int EdgesCount) {
    int *parent = malloc(NodeCount * sizeof(int));
    unsigned int *key = malloc(NodeCount * sizeof(unsigned int));
    int *mstSet = malloc(NodeCount * sizeof(int));

    graph = makeMatrix(NodeCount, EdgesCount);

    if (graph == 0)
        return;

    for (int i = 0; i < NodeCount; i++)
        key[i] = UINT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < NodeCount - 1; count++) {
        int u = minKey(key, mstSet, NodeCount);

        mstSet[u] = 1;

        for (int v = 0; v < NodeCount; v++)

            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u, key[v] = graph[u][v];
            }
    }

    if (EdgesCount == 1) {
        puts("no spanning tree");
        return;
    }

    printMSTEdges(parent, NodeCount);
    free(parent);
    free(key);
    free(mstSet);
}
