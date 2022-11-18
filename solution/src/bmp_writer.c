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

enum write_status write_bmp_file(FILE* output, struct image image){
    uint8_t padding = (4 - (3 * image.width % 4) % 4);
    uint32_t image_size = (sizeof(struct pixel) * image.width + padding * image.height);
    struct bmp_header header = {
            .bfType = BMP_HEADER_TYPE,
            .bfileSize = sizeof(struct bmp_header) + image_size,
            .bfReserved = BMP_HEADER_RESERVED,
            .bOffBits = sizeof(struct bmp_header),
            .biSize = BMP_HEADER_INFO_SIZE,
            .biWidth = image.width,
            .biHeight = image.height,
            .biPlanes = BMP_HEADER_PLANES,
            .biBitCount = BMP_BIT_COUNT,
            .biCompression = BMP_COMPRESSION,
            .biSizeImage = image_size,
            .biXPelsPerMeter = BMP_PER_METER,
            .biYPelsPerMeter = BMP_PER_METER,
            .biClrUsed = BMP_USED,
            .biClrImportant = BMP_IMPORTANT
    };

    enum write_status status = (fwrite(&header, sizeof (struct bmp_header), 1, output) == 1);
    if (status == WRITE_OK){
        for (uint64_t i = 0; i < image.height; i++){
            if (fwrite(image.pixels + i*image.width, sizeof(struct pixel), image.width, output) != image.width){
                return WRITE_ERROR_PIXELS;
            }
            if (fseek(output, padding, SEEK_CUR) != 0){
                return WRITE_ERROR_PIXELS;
            }
        }
        return WRITE_OK;
    }
    else {
        return WRITE_ERROR_HEADING;
    }
}
