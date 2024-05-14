#ifndef HUFFMAN_QUEUE_H
#define HUFFMAN_QUEUE_H

#include "stdlib.h"
#include "stdio.h"

#define NODE struct node
#define QUEUE struct queue

NODE {
    wchar_t symbol;
    int freq;
    NODE *left;
    NODE *right;
};

QUEUE {
    int size;
    NODE **heap;
};


QUEUE *InitQueue();

NODE *InitNode(wchar_t symbol, int freq, NODE *left, NODE *right);

void NewSize(QUEUE *queue, int size);

void Enqueue(QUEUE *queue, NODE *node);

QUEUE *FillQueue(FILE *input);

#endif
