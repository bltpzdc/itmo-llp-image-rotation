//
// Created by Sevastian on 18.11.2022.
//

#ifndef UNTITLED1_BMP_FILE_H
#define UNTITLED1_BMP_FILE_H

#include <stdint.h>

struct __attribute__((packed)) bmp_header
{
    uint16_t bfType; // BM 0x4D42
    uint32_t bfileSize; // header + n_pixels * sizeof(struct pixel)
    uint32_t bfReserved; // 0
    uint32_t bOffBits; // 54
    uint32_t biSize; // 40
    uint32_t biWidth; // w
    uint32_t biHeight; // h
    uint16_t biPlanes; // 1
    uint16_t biBitCount; // 24
    uint32_t biCompression; // 0
    uint32_t biSizeImage; // n_pixels * sizeof(struct pixel)
    uint32_t biXPelsPerMeter; // 0
    uint32_t biYPelsPerMeter; // 0
    uint32_t biClrUsed; // 0
    uint32_t biClrImportant; // 0
};
#endif //UNTITLED1_BMP_FILE_H
