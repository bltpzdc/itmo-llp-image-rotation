//
// Created by Honor on 18.11.2022.
//
#include "bmp_writer.h"

#define TYPE 0x4d42
#define OFFSET sizeof(struct bmp_header)
#define HEADER_SIZE 40
#define PLANES 1
#define BIT 24
#define COMPRESSION 0
#define COLORS 0
#define HORIZONTAL 2835
#define VERTICAL 2835

enum write_status write_bmp_file(FILE* output, struct image image){
    struct bmp_header header = {
            .bfType = TYPE,
            .bfReserved = 0,
            .bOffBits = OFFSET,
            .biSize = HEADER_SIZE,
            .biPlanes = PLANES,
            .biBitCount = BIT,
            .biCompression = COMPRESSION,
            .biXPelsPerMeter = HORIZONTAL,
            .biYPelsPerMeter = VERTICAL,
            .biClrUsed = COLORS,
            .biClrImportant = 0
    };


    header.biWidth = image.width;
    header.biHeight = image.height;
    header.biSizeImage = image.width*image.height* sizeof(struct pixel);
    header.bfileSize = header.biSizeImage + sizeof(struct bmp_header);

    size_t wrRes = fwrite(&header, sizeof(struct bmp_header), 1, output);
    if (wrRes != 1) return WRITE_ERROR_HEADING;

    uint64_t width = image.width;
    uint64_t height = image.height;
    uint8_t padding = (width*height* sizeof(struct pixel))%4;
    if (padding) padding = 4 - padding;

    for (uint64_t i = 0; i < image.height; i++){
        wrRes = fwrite(image.pixels+i*image.width, sizeof(struct pixel), image.width, output);
        if (wrRes != image.width) return WRITE_ERROR_PIXELS;

        if (fseek(output, padding, SEEK_CUR) == -1) return WRITE_ERROR_PIXELS;
    }
    return WRITE_OK;
}
