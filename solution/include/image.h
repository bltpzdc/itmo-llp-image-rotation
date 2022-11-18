//
// Created by Honor on 18.11.2022.
//

#ifndef UNTITLED1_IMAGE_H
#define UNTITLED1_IMAGE_H

#include <malloc.h>
#include <stdint.h>


struct __attribute__((packed)) pixel{
    uint8_t b, g, r;
};

struct image{
    uint64_t width, height;
    struct pixel* pixels;
};

struct image create_image(uint64_t width, uint64_t height);
void destroy_image(struct image image);
struct pixel get_pixel(struct image image, uint64_t row, uint64_t column);
void set_pixel(struct image image, uint64_t row, uint64_t column, struct pixel pixel);

#endif //UNTITLED1_IMAGE_H
