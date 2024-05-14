#include "queue.h"

QUEUE *InitQueue() {
    QUEUE *queue = malloc(sizeof(QUEUE));

    if (!queue)
        exit(EXIT_FAILURE);

    queue->size = 0;
    queue->heap = NULL;

    return queue;
}

NODE *InitNode(wchar_t symbol, int freq, NODE *left, NODE *right) {
    NODE *node = malloc(sizeof(NODE));

    if (!node)
        exit(EXIT_FAILURE);

    node->symbol = symbol;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

void NewSize(QUEUE *queue, int size) {
    queue->heap = realloc(queue->heap, size * sizeof(NODE *));

    if (!queue->heap && size > 0)
        exit(EXIT_FAILURE);

    queue->size = size;
}

void Enqueue(QUEUE *queue, NODE *node) {
    NewSize(queue, queue->size + 1);
    int index = queue->size - 1;

    while (index > 0 && node->freq >= queue->heap[index - 1]->freq) {
        queue->heap[index] = queue->heap[index - 1];
        index--;
    }

    queue->heap[index] = node;
}

QUEUE *FillQueue(FILE *input) {
    wchar_t symbol;
    QUEUE *queue = InitQueue();

    fseek(input, 0, SEEK_END);
    long numBytes = ftell(input);
    rewind(input);

    for (int j = 0; j < (numBytes / sizeof(wchar_t)); j++) {
        symbol = fgetwc(input);
        int inQueue = 0;
        for (int i = 0; i < queue->size; i++) {
            if (queue->heap[i]->symbol == symbol) {
                queue->heap[i]->freq++;
                while (i > 0 && queue->heap[i]->freq >= queue->heap[i - 1]->freq) {
                    NODE *temp = queue->heap[i];
                    queue->heap[i] = queue->heap[i - 1];
                    queue->heap[i - 1] = temp;
                    i--;
                }
                inQueue = 1;
                break;
            }
        }
        if (!inQueue)
            Enqueue(queue, InitNode(symbol, 1, NULL, NULL));
    }

    rewind(input);
    return queue;
}