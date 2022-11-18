//
// Created by Honor on 18.11.2022.
//
#include "bmp_writer.h"
#define BMP_HEADER_TYPE 19778
#define BMP_HEADER_PLANES 1
#define BMP_HEADER_INFO_SIZE 40
#define BMP_HEADER_RESERVED 0
#define BMP_BIT_COUNT 24
#define BMP_COMPRESSION 24
#define BMP_PER_METER 0
#define BMP_USED 0
#define BMP_IMPORTANT 0

static uint8_t get_padding(size_t width){
    uint8_t x = (4 - (width * 3) % 4 );
    return (x == 4) ? ((uint8_t) 0) : (x % 4);
}
static struct bmp_header create_output_header(struct image* image){
    size_t image_size = (sizeof(struct pixel) * image->width + get_padding(image->width)) * image->height;
    return (struct bmp_header) {
            .bfType = BMP_HEADER_TYPE,
            .bfileSize = sizeof(struct bmp_header) + image_size,
            .bfReserved = BMP_HEADER_RESERVED,
            .bOffBits = sizeof(struct bmp_header),
            .biSize = BMP_HEADER_INFO_SIZE,
            .biWidth = image->width,
            .biHeight = image->height,
            .biPlanes = BMP_HEADER_PLANES,
            .biBitCount = BMP_BIT_COUNT,
            .biCompression = BMP_COMPRESSION,
            .biSizeImage = image_size,
            .biXPelsPerMeter = BMP_PER_METER,
            .biYPelsPerMeter = BMP_PER_METER,
            .biClrUsed = BMP_USED,
            .biClrImportant = BMP_IMPORTANT
    };
}

static enum write_status write_header(FILE* output, struct bmp_header* header) {
    return (fwrite(header, sizeof(struct bmp_header), 1, output) == 1) ? WRITE_OK : WRITE_ERROR_HEADING;
}

static enum write_status write_pixels(FILE* file, const struct image* image) {
    for (size_t i = 0; i < image->height; i++) {
        if (fwrite(image->data + i * image->width, sizeof(struct pixel), image->width, file) != image->width) return WRITE_ERROR_PIXELS;
        if (fseek(file, get_padding(image->width), SEEK_CUR) != 0) return WRITE_ERROR_PIXELS;
    }
    return WRITE_OK;
}
enum write_status write_bmp_file(FILE* output, struct image* image){
    struct bmp_header header = create_output_header(image);
    if (write_header(output, &header) != WRITE_OK) return WRITE_ERROR_HEADING;
    return write_pixels(output, image);
}


