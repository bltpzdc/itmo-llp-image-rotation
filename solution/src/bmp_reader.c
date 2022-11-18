//
// Created by Honor on 18.11.2022.
//
#include "bmp_reader.h"

enum read_status read_bmp_file(FILE* input, struct image* image){
    struct bmp_header header = {0};
    size_t head_read_flag = fread(&header, sizeof(struct bmp_header), 1, input);
    if (head_read_flag != 1) return READ_ERROR_HEADING;
    uint64_t width = header.biWidth;
    uint64_t height = header.biHeight;
    uint8_t padding = (width*height*sizeof(struct pixel))%4;
    if (padding) padding = 4 - padding;
    create_image(width, height);
    for (uint64_t i = 0; i < height; i++){
        if (!fread(image->pixels + i*width, width* sizeof(struct pixel), 1, input)) return READ_ERROR_PIXELS;

        if (fseek(input, padding, SEEK_CUR) == -1) return READ_ERROR_PIXELS;
    }

    return READ_OK;
}
