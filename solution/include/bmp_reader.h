//
// Created by Honor on 18.11.2022.
//
#include <stdio.h>
#include "bmp.h"
#include "image.h"

#ifndef IMAGE_TRANSFORMER_BMP_READER_H
#define IMAGE_TRANSFORMER_BMP_READER_H
enum read_status{
    READ_OK = 0,
    READ_ERROR_HEADING,
    READ_ERROR_PIXELS
};

enum read_status read_bmp_file(FILE* input, struct image* image);
#endif //IMAGE_TRANSFORMER_BMP_READER_H
