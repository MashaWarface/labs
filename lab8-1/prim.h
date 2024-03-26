#ifndef LAB8_1_PRIM_H
#define LAB8_1_PRIM_H

int Errors(int NodeCount, int Start, int Finish, int EdgesCount, unsigned int Length);

int find(int *list, int length, int a);

unsigned int **memMatrix(int NodeCount);

int fillEdges(unsigned int **Matrix, int NodeCount, int EdgesCount);

unsigned int **makeMatrix(int NodeCount, int EdgesCount);

int minKey(unsigned int *key, int *mstSet, int NodeCount);

void printMSTEdges(int *parent, int NodeCount);

void primMST(unsigned int **graph, int NodeCount, int EdgesCount);

#endif
