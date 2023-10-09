//
// Created by Sevastian on 18.11.2022.
//
#include "image.h"

struct image create_image(size_t width, size_t height){
    struct image img = {
            .width = width,
            .height = height,
            .data = malloc(width * height * sizeof (struct pixel))
    };

    return img;
}

