//
// Created by Honor on 18.11.2022.
//
#include "bmp_reader.h"
static enum read_status read_header(FILE* input, struct bmp_header* header){
    if (fread(header, sizeof(struct bmp_header), 1, input)) return READ_OK;
    return READ_ERROR_HEADING;
}

static uint8_t get_padding(uint64_t width){
    return (4 - (3 * width % 4) % 4);
}

static enum read_status read_pixels(FILE* input, struct image* image){
    const struct image ti = create_image(image->width, image->height);
    for (size_t i = 0; i < ti.height; i++) {
        if (fread(ti.pixels + (i * ti.width), sizeof(struct pixel), ti.width, input) != ti.width) {
            free(ti.pixels);
            return READ_ERROR_PIXELS;
        }
        if (fseek(input, get_padding(ti.width), SEEK_CUR) != 0) {
            free(ti.pixels);
            return READ_ERROR_PIXELS;
        }
    }
    image->pixels = ti.pixels;
    return READ_OK;
}

enum read_status read_bmp_file(FILE* input, struct image* image){
    struct bmp_header header = {0};
    if (read_header(input, &header) != READ_OK) return READ_ERROR_HEADING;
    image->width = header.biWidth;
    image->height = header.biHeight;
    return read_pixels(input, image);
}


