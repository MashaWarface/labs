cmake_minimum_required(VERSION 3.26)
project(huffman C)

set(CMAKE_C_STANDARD 23)

add_executable(huffman main.c
        huffman.c
        huffman.h
        main.c
        queue.c
        queue.h
        bitstream.c
        bitstream.h)
