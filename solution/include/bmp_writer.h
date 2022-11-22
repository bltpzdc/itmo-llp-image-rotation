//
// Created by Honor on 18.11.2022.
//

#ifndef IMAGE_TRANSFORMER_BMP_WRITER_H
#define IMAGE_TRANSFORMER_BMP_WRITER_H
#include "bmp.h"
#include "image.h"
#include <stdio.h>

enum write_status{
    WRITE_OK = 0,
    WRITE_ERROR_HEADING,
    WRITE_ERROR_PIXELS
};

enum write_status write_bmp_file(FILE* const output, struct image* const image);
#endif //IMAGE_TRANSFORMER_BMP_WRITER_H
