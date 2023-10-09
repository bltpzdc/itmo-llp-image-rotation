//
// Created by Sevastian on 18.11.2022.
//

#ifndef UNTITLED1_IMAGE_H
#define UNTITLED1_IMAGE_H

#include <malloc.h>
#include <stdint.h>


struct __attribute__((packed)) pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel *data;
};

struct image create_image(size_t width, size_t height);

#endif //UNTITLED1_IMAGE_H
