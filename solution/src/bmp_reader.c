//
// Created by Honor on 18.11.2022.
//
#include "bmp_reader.h"

enum read_status read_bmp_file(FILE* input, struct image* image){
    struct bmp_header header = {0};
    if (fread(&header, sizeof(struct bmp_header), 1, input) != READ_OK) return READ_ERROR_HEADING;
    image->width = header.biWidth;
    image->height = header.biHeight;
    uint8_t padding = (4 - (3 * image->width % 4) % 4);
    const struct image temp = create_image(image->width, image->height);
    for (uint64_t i = 0; i < temp.height; i++){
        if (fread(temp.pixels + i*temp.width, sizeof(struct pixel), temp.width, input) != temp.width){
            free(temp.pixels);
            return READ_ERROR_PIXELS;
        }

        if (fseek(input, padding, SEEK_CUR) != 0) {
            free(temp.pixels);
            return READ_ERROR_PIXELS;
        }
    }

    return READ_OK;
}

