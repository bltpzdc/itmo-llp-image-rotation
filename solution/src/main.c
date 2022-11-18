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
        fprintf(stderr, "Can not open input file.");
        return 1;
    }

    fprintf(stdout, "Input file opened.");
    struct image old_image = {0};

    if (read_bmp_file(input, &old_image) != READ_OK){
        fprintf(stderr, "cant read file");
        free(old_image.data);
        fclose(input);
        return 1;
    }

    if (fclose(input) != 0){
        printf("failed");
        free(old_image.data);
        return 1;
    }

    printf("closed file");

    FILE* output = fopen(argv[2], "wb");

    struct image new_image = rotate(&old_image);

    if (write_bmp_file(output, new_image) != WRITE_OK){
        fprintf(stderr, "cant write");
        free(new_image.data);
        fclose(input);
        fclose(output);
        return 1;
    }

    if (fclose(output) != 0 ){
        fprintf(stderr, "cant close");
        free(old_image.data);
        free(new_image.data);
        return 1;
    }

    free(old_image.data);
    free(new_image.data);



    return 0;
}
