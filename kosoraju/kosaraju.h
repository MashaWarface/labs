#ifndef KOSARAJU_H
#define KOSARAJU_H

#include "stack.h"
#include "graph.h"

LIST *Invert(LIST *Graph, int NodeCount);

void DFS(LIST *Graph, STACK *Vertices, int *Visited, int Vertex);

void FullDFS(LIST *Graph, STACK *Vertices, int *Visited, int NodeCount);

void Kosaraju(LIST *Graph, LIST *InvertGraph, int *Visited, int NodeCount);

#endif
