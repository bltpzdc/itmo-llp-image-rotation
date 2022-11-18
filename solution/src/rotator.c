//
// Created by Honor on 18.11.2022.
//
#include "rotator.h"

struct image rotate(struct image* old_image){
    uint64_t height = old_image->height;
    uint64_t width = old_image->width;

    struct image copy = create_image(height,width);

    if (copy.data != NULL) {
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                copy.data[height * j + height - i - 1] = old_image->data[width * i + j];
            }
        }
        return copy;
    }
    else return (struct image){0};
}
