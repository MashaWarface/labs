#include "bitstream.h"

#define BYTE_SIZE 8
#define TWO_BYTE_SIZE 16

BIT_STREAM *InitBitStream(FILE *file) {
    BIT_STREAM *stream = malloc(sizeof(BIT_STREAM));

    if (!stream)
        exit(EXIT_FAILURE);

    stream->file = file;
    stream->data = 0;
    stream->pos = 0;

    return stream;
}

void WriteBit(int bit, BIT_STREAM *stream) {
    if (stream->pos == BYTE_SIZE) {
        fwrite(&(stream->data), sizeof(char), 1, stream->file);
        stream->pos = 0;
        stream->data = 0;
    }

    stream->data = bit | (stream->data << 1);
    stream->pos++;
}

void WriteSymbol(wchar_t symbol, BIT_STREAM *stream) {
    for (int i = TWO_BYTE_SIZE - 1; i >= 0; i--) {
        int bit = (symbol >> i) & 1;
        WriteBit(bit, stream);
    }
}

int ReadBit(int *bit, BIT_STREAM *stream) {
    if (stream->pos == 0) {
        if (fread(&stream->data, sizeof(char), 1, stream->file) != 1)
            return 0;
        stream->pos = BYTE_SIZE;
    }

    stream->pos -= 1;
    *bit = (stream->data >> stream->pos) & 1;

    return 1;
}

int ReadSymbol(wchar_t *symbol, BIT_STREAM *stream) {
    *symbol = 0;

    for (int i = 0; i < TWO_BYTE_SIZE; i++) {
        *symbol = *symbol << 1;
        int bit;
        if (ReadBit(&bit, stream) == 0)
            return 0;
        *symbol = *symbol | bit;
    }

    return 1;
}

void FreeBitStream(BIT_STREAM *stream) {
    stream->data = stream->data << (BYTE_SIZE - stream->pos);
    fwrite(&(stream->data), sizeof(char), 1, stream->file);
}
