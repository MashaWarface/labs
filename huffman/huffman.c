#include "huffman.h"
#include "stdlib.h"

NODE *FillTree(QUEUE *queue) {
    while (queue->size > 1) {
        NODE *left = queue->heap[--queue->size];
        NODE *right = queue->heap[--queue->size];
        NODE *node = InitNode(0, left->freq + right->freq, left, right);
        Enqueue(queue, node);
    }

    return queue->heap[0];
}

int LastLeave(NODE *root) {
    return !root->left;
}

void GetCodes(NODE *root, unsigned long long code, int length, CODE *codes, int *index) {
    if (LastLeave(root)) {
        codes[*index].symbol = root->symbol;
        codes[*index].length = length;
        codes[*index].code = code;
        (*index)++;
        return;
    }

    GetCodes(root->left, code << 1, length + 1, codes, index);
    GetCodes(root->right, (code << 1) | 1, length + 1, codes, index);
}


void CodeInput(wchar_t symbol, CODE *codes, BIT_STREAM *stream, int codesLen) {
    int i;

    for (i = 0; i < codesLen; i++)
        if (codes[i].symbol == symbol)
            break;

    for (int j = codes[i].length - 1; j >= 0; j--) {
        int bit = (codes[i].code >> j) & 1;
        WriteBit(bit, stream);
    }
}


void FreeTree(NODE *root) {
    if (root == NULL) {
        return;
    }

    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

void WriteTree(NODE *root, BIT_STREAM *stream) {
    if (LastLeave(root)) {
        WriteBit(1, stream);
        WriteSymbol(root->symbol, stream);
        return;
    }

    WriteBit(0, stream);
    WriteTree(root->left, stream);
    WriteTree(root->right, stream);
}

void Encode(FILE *input, FILE *output) {
    QUEUE *queue = FillQueue(input);
    BIT_STREAM *stream = InitBitStream(output);
    CODE *codes = malloc(queue->size * sizeof(CODE));
    NODE *root = FillTree(queue);
    int index = 0;

    fwrite(&(root->freq), sizeof(int), 1, stream->file);
    WriteTree(root, stream);

    GetCodes(root, 0, 0, codes, &index);

    fseek(input, 0, SEEK_END);
    long numBytes = ftell(input);
    rewind(input);

    wchar_t symbol;

    for (int i = 0; i < (numBytes / sizeof(wchar_t)); i++) {
        symbol = fgetwc(input);
        CodeInput(symbol, codes, stream, index);
    }

    FreeBitStream(stream);
    free(codes);
    free(queue->heap);
    free(queue);
    free(stream);
    FreeTree(root);
}


NODE *ReadTree(BIT_STREAM *stream) {
    int bit;

    if (ReadBit(&bit, stream) == 0)
        return NULL;

    if (bit == 1) {
        wchar_t symbol;
        if (ReadSymbol(&symbol, stream) == 0)
            return NULL;
        return InitNode(symbol, 0, NULL, NULL);
    }

    NODE *left = ReadTree(stream);
    NODE *right = ReadTree(stream);

    return InitNode(0, 0, left, right);
}

int Unpack(NODE *root, BIT_STREAM *stream, wchar_t *symbol) {
    NODE *current = root;
    int bit;

    while (!LastLeave(current)) {
        if (ReadBit(&bit, stream) == 0)
            return 0;
        if (bit == 0)
            current = current->left;
        else
            current = current->right;
    }

    *symbol = current->symbol;

    return 1;
}

void Decode(FILE *input, FILE *output) {
    BIT_STREAM *stream = InitBitStream(input);
    int length;
    fread(&length, sizeof(int), 1, stream->file);
    NODE *root = ReadTree(stream);

    for (int i = 0; i < length; i++) {
        wchar_t symbol;
        if (Unpack(root, stream, &symbol) == 0) {
            fclose(stream->file);
            free(stream);
            return;
        }
        fwrite(&symbol, sizeof(wchar_t), 1, output);
    }

    FreeTree(root);
    free(stream);
}
