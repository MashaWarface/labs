#include "huffman.h"

int main(int argc, char **argv) {
    if (argc != 4) return 0;

    FILE *input = fopen(argv[2], "rb");
    FILE *output = fopen(argv[3], "wb");

    if (*argv[1] == 'c') {
        Encode(input, output);
    }

    if (*argv[1] == 'd') {
        Decode(input, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}
