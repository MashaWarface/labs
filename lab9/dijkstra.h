#ifndef GRAPHILL_DIJKSTRA_H
#define GRAPHILL_DIJKSTRA_H

int Errors(int NodeCount, int Start, int Finish, int EdgeCount, unsigned int Weight);

unsigned int **MakeMatrix(int NodeCount, int Start, int Finish, int EdgeCount);

int minDistance(int NodeCount, int *sptSet, unsigned int *dist);

void dijkstra(unsigned int **weights, int NodeCount, int Start, int Finish);

void printResults(int *sptSet, unsigned int *dist, int *way, int Finish, int Start, int NodeCount);

void Free(unsigned int **Matrix, int N);

#endif
