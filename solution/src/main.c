//
// Created by Honor on 18.11.2022.
//
#include "bmp.h"
#include "bmp_reader.h"
#include "bmp_writer.h"
#include "image.h"
#include "operations.h"
#include "rotator.h"

int main(int argc, char** argv){
    if (argc != 3){
        fprintf(stderr, "%s", "Invalid number of arguments.");
        return 1;
    }

    FILE* input = NULL;

    enum open_file_status openFileStatus = open_file(&input, argv[1], "rb");
    if (openFileStatus == OPEN_OK) fprintf(stdout, "Input file opened.");
    else {
        fprintf(stderr, "Can not open input file.");
        return 1;
    }

    struct image old_image = {0};
    if (read_bmp_file(input, &old_image) != READ_OK){
        fprintf(stderr, "Can not read input file.");
        free(old_image.data);
        fclose(input);
        return 1;
    }
    fprintf(stdout, "Input file read.");

    if (fclose(input) != 0){
        printf("Can not close input file.");
        free(old_image.data);
        return 1;
    }
    fprintf(stdout, "Input file closed.");

    FILE* output = NULL;

    openFileStatus = open_file(&output, argv[2], "wb");
    if (openFileStatus == OPEN_OK) fprintf(stdout, "Output file opened.");
    else {
        fprintf(stderr, "Can not open output file.");
        return 1;
    }

    struct image new_image = rotate(&old_image);
    free(old_image.data);
    if (write_bmp_file(output, &new_image) != WRITE_OK){
        fprintf(stderr, "Can not write into output file.");
        free(new_image.data);
        fclose(output);
        return 1;
    }
    fprintf(stdout, "New image written to output file.");
    free(new_image.data);

    if (fclose(output) != 0 ){
        fprintf(stderr, "Can not close output file.");
        return 1;
    }
    return 0;
}
