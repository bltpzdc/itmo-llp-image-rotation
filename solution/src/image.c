//
// Created by Honor on 18.11.2022.
//
#include "image.h"

struct image create_image(uint64_t width, uint64_t height){
    struct image image = {
            .width = width,
            .height = height,
            .pixels = malloc(sizeof(struct pixel)*width*height)
    };
    return image;
}

void destroy_image(struct image image){
    free(image.pixels);
}

struct pixel get_pixel(struct image image, uint64_t row, uint64_t column){
    return image.pixels[image.width*row + column];
}

void set_pixel(struct image image, uint64_t row, uint64_t column, struct pixel pixel){
    image.pixels[image.width*row + column] = pixel;
}
