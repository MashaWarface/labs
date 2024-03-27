#ifndef LAB8_1_PRIM_H
#define LAB8_1_PRIM_H

int Errors(int NodeCount, int Start, int Finish, int EdgesCount, unsigned int Length);

int find(int *list, int length, int a);

unsigned int **memMatrix(int NodeCount);

int fillEdges(unsigned int **Matrix, int NodeCount, int EdgesCount);

unsigned int **makeMatrix(int NodeCount, int EdgesCount);

int minDistance(unsigned int *dist, int *mstSet, int NodeCount);

void printEdges(int *way, int NodeCount);

void destroy(unsigned int **Matrix, int NodeCount);

void Prim(unsigned int **Matrix, int NodeCount, int EdgesCount);

#endif
