#ifndef HUFFMAN_BITSTREAM_H
#define HUFFMAN_BITSTREAM_H

#include "queue.h"

#define BIT_STREAM struct bitStream

BIT_STREAM {
    FILE *file;
    int pos;
    wchar_t data;
};

BIT_STREAM *InitBitStream(FILE *file);

void WriteBit(int bit, BIT_STREAM *stream);

void WriteSymbol(wchar_t symbol, BIT_STREAM *stream);

int ReadBit(int *bit, BIT_STREAM *stream);

int ReadSymbol(wchar_t *symbol, BIT_STREAM *stream);

void FreeBitStream(BIT_STREAM *stream);

#endif
