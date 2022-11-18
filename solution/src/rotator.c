//
// Created by Honor on 18.11.2022.
//
#include "rotator.h"

struct image rotate(struct image* old_image){
    struct image new_image = create_image(old_image->height,old_image->width);
    for (size_t i = 0; i < old_image->height; i++) {
        for (size_t j = 0; j < old_image->width; j++) {
            new_image.data[old_image->height * j + old_image->height - i - 1] = old_image->data[old_image->width * i + j];
        }
    }
    return new_image;
}
