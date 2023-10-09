//
// Created by Sevastian on 18.11.2022.
//
#include "bmp_writer.h"
#define HEADER_TYPE 19778
#define PLANES 1
#define SIZE 40
#define ZERO 0
#define BITS 24
#define COMPRESSION 24


static uint8_t get_padding(size_t width){
    uint8_t x = (4 - (width * 3) % 4 );
    return (x == 4) ? ((uint8_t) 0) : x;
}
static struct bmp_header create_output_header(struct image* const image){
    size_t image_size = (sizeof(struct pixel) * image->width + get_padding(image->width)) * image->height;
    return (struct bmp_header) {
            .bfType = HEADER_TYPE,
            .bfileSize = sizeof(struct bmp_header) + image_size,
            .bfReserved = ZERO,
            .bOffBits = sizeof(struct bmp_header),
            .biSize = SIZE,
            .biWidth = image->width,
            .biHeight = image->height,
            .biPlanes = PLANES,
            .biBitCount = BITS,
            .biCompression = COMPRESSION,
            .biSizeImage = image_size,
            .biXPelsPerMeter = ZERO,
            .biYPelsPerMeter = ZERO,
            .biClrUsed = ZERO,
            .biClrImportant = ZERO
    };
}

static enum write_status write_header(FILE* const output, struct bmp_header* const header) {
    return (fwrite(header, sizeof(struct bmp_header), 1, output) == 1) ? WRITE_OK : WRITE_ERROR_HEADING;
}

static enum write_status write_pixels(FILE* const file, const struct image* const image) {
    for (size_t i = 0; i < image->height; i++) {
        if (fwrite(image->data + i * image->width, sizeof(struct pixel), image->width, file) != image->width) return WRITE_ERROR_PIXELS;
        if (fseek(file, get_padding(image->width), SEEK_CUR) != 0) return WRITE_ERROR_PIXELS;
    }
    return WRITE_OK;
}
enum write_status write_bmp_file(FILE* const output, struct image* const image){
    struct bmp_header header = create_output_header(image);
    if (write_header(output, &header) != WRITE_OK) return WRITE_ERROR_HEADING;
    return write_pixels(output, image);
}


