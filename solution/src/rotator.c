//
// Created by Honor on 18.11.2022.
//
#include "rotator.h"

struct image rotate(struct image old_image){
    struct image new_image = create_image(old_image.height, old_image.width);

    for (uint64_t row = 0; row < old_image.height; row++){
        for (uint64_t column = 0; column < old_image.width; column++){
            set_pixel(new_image, new_image.width-row-1, column, get_pixel(old_image,column, row));
        }
    }
    return new_image;
}
