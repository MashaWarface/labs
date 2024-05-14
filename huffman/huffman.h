#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "queue.h"
#include "bitstream.h"

#define CODE struct code

CODE {
    wchar_t symbol;
    int length;
    unsigned long long code;
};

NODE *FillTree(QUEUE *queue);

int LastLeave(NODE *root);

void GetCodes(NODE *root, unsigned long long code, int length, CODE *codes, int *index);

void CodeInput(wchar_t symbol, CODE *codes, BIT_STREAM *stream, int codesLen);

void FreeTree(NODE *root);

void WriteTree(NODE *root, BIT_STREAM *stream);

void Encode(FILE *input, FILE *output);

NODE *ReadTree(BIT_STREAM *stream);

int Unpack(NODE *root, BIT_STREAM *stream, wchar_t *symbol);

void Decode(FILE *input, FILE *output);

#endif
