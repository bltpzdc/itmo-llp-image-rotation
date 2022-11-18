//
// Created by Honor on 18.11.2022.
//
#include "bmp.h"
#include "bmp_reader.h"
#include "bmp_writer.h"
#include "image.h"
#include "rotator.h"

int main(int argc, char** argv){
    if (argc != 3){
        fprintf(stderr, "%s", "Invalid number of arguments.");
        return 1;
    }

    FILE* input = fopen(argv[1], "rb");

    if (!input){
        fprintf(stderr, "cant open file");
        return 1;
    }

    struct image old_image = {0};

    if (read_bmp_file(input, &old_image)){
        fprintf(stderr, "cant read file");
        free(old_image.pixels);
        fclose(input);
        return 1;
    }

    if (fclose(input) != 0){
        printf("failed");
        free(old_image.pixels);
        return 1;
    }

    printf("closed file");

    FILE* output = fopen(argv[2], "wb");

    struct image new_image = rotate(old_image);

    if (write_bmp_file(output, new_image) != WRITE_OK){
        fprintf(stderr, "cant write");
        free(new_image.pixels);
        fclose(input);
        fclose(output);
        return 1;
    }

    if (fclose(output) != 0 ){
        fprintf(stderr, "cant close");
        free(old_image.pixels);
        free(new_image.pixels);
        return 1;
    }

    free(old_image.pixels);
    free(new_image.pixels);



    return 0;
}
