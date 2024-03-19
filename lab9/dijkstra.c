#include "dijkstra.h"
#include "malloc.h"
#include "limits.h"

int Errors(int NodeCount, int Start, int Finish, int EdgeCount, unsigned int Weight) {
    if (Start < 1 || Start > NodeCount || Finish < 1 || Finish > NodeCount) {
        puts("bad vertex");
        return 0;
    }
    if (NodeCount < 0 || NodeCount > 5000) {
        puts("bad number of vertices");
        return 0;
    }
    if (EdgeCount < 0 || EdgeCount > NodeCount * (NodeCount + 1) / 2) {
        puts("bad number of edges");
        return 0;
    }
    if (Weight > INT_MAX) {
        puts("bad length");
        return 0;
    }
    return 1;
}

unsigned int **MakeMatrix(int NodeCount, int Start, int Finish, int EdgeCount) {
    if (!(Errors(NodeCount, Start, Finish, EdgeCount, INT_MAX)))
        return 0;

    unsigned int **weights = malloc(NodeCount * sizeof(unsigned int *));
    for (int i = 0; i < NodeCount; i++)
        weights[i] = malloc(NodeCount * sizeof(unsigned int));
    for (int i = 0; i < NodeCount; i++)
        for (int j = 0; j < NodeCount; j++)
            weights[i][j] = 0;

    for (int i = 0; i < EdgeCount; ++i) {
        int Row, Column;
        unsigned int Weight;

        scanf("%d %d %u", &Row, &Column, &Weight);

        if (!(Errors(NodeCount, Row, Column, EdgeCount, Weight)))
            return 0;

        weights[Row - 1][Column - 1] = Weight;
        weights[Column - 1][Row - 1] = Weight;
    }

    return weights;
}

int minDistance(int NodeCount, int *sptSet, unsigned int *dist) {
    unsigned int Min = UINT_MAX;
    int MinIndex;

    for (int v = 0; v < NodeCount; v++)
        if (sptSet[v] == 0 && dist[v] < Min)
            Min = dist[v], MinIndex = v;

    return MinIndex;
}

void dijkstra(unsigned int **weights, int NodeCount, int Start, int Finish) {
    unsigned int *dist = malloc(NodeCount * sizeof(unsigned int));
    int *sptSet = malloc(NodeCount * sizeof(int));
    int *way = malloc(NodeCount * sizeof(int));

    for (int i = 0; i < NodeCount; i++)
        dist[i] = UINT_MAX, sptSet[i] = 0;

    dist[Start - 1] = 0;

    for (int count = 0; count < NodeCount; count++) {
        int u = minDistance(NodeCount, sptSet, dist);
        sptSet[u] = 1;
        for (int v = 0; v < NodeCount; v++)
            if (!sptSet[v] && weights[u][v] && dist[u] != UINT_MAX && dist[u] + weights[u][v] < dist[v]) {
                dist[v] = dist[u] + weights[u][v];
                way[v] = u;
            }
    }

    printResults(sptSet, dist, way, Finish, Start, NodeCount);

    free(dist);
    free(sptSet);
    free(way);
}

void printResults(int *sptSet, unsigned int *dist, int *way, int Finish, int Start, int NodeCount) {
    for (int i = 0; i < NodeCount; ++i)
        if (sptSet[i])
            if (dist[i] > INT_MAX)
                printf("INT_MAX+ ");
            else
                printf("%u ", dist[i]);
        else
            printf("oo ");

    puts("");

    if (!sptSet[Finish - 1]) {
        printf("no path \n");
        return;
    }
    int cntIntMax = 0;

    for (int i = 0; i < NodeCount; ++i) {
        if (dist[i] >= INT_MAX && dist[i] != UINT_MAX)
            cntIntMax++;
    }
    if (cntIntMax > 2 && dist[Finish - 1] > INT_MAX) {
        printf("overflow\n");
        return;
    }
    for (int i = Finish - 1; i != Start - 1; i = way[i])
        printf("%d ", i + 1);
    printf("%d\n", Start);
}

void Free(unsigned int **Matrix, int N) {
    for (int i = 0; i < N; i++)
        free(Matrix[i]);
    free(Matrix);
}
