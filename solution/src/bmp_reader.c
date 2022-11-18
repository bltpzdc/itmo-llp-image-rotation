//
// Created by Honor on 18.11.2022.
//
#include "bmp_reader.h"
static enum read_status read_header(FILE* input, struct bmp_header* header){
    return (fread(header, sizeof(struct bmp_header), 1, input)) ? READ_OK : READ_ERROR_HEADING;
}

static uint8_t get_padding(size_t width){
    uint8_t x = (4 - (width * 3) % 4 );
    return (x == 4) ? ((uint8_t) 0) : (x % 4);
}

static enum read_status read_pixels(FILE* input, struct image* image){
    const struct image temp = create_image(image->width, image->height);
    if (temp.data != NULL) {
        for (size_t i = 0; i < temp.height; i++) {
            if (fread(temp.data + (i * temp.width), sizeof(struct pixel), temp.width, input) != temp.width) {
                free(temp.data);
                return READ_ERROR_PIXELS;
            }
            if (fseek(input, get_padding(temp.width), SEEK_CUR) != 0) {
                free(temp.data);
                return READ_ERROR_PIXELS;
            }
        }
        image->data = temp.data;
        return READ_OK;
    }
    return READ_ERROR_PIXELS;
}

enum read_status read_bmp_file(FILE* input, struct image* image){
    struct bmp_header header = {0};
    if (read_header(input, &header) != READ_OK) return READ_ERROR_HEADING;
    image->width = header.biWidth;
    image->height = header.biHeight;
    return read_pixels(input, image);
}


