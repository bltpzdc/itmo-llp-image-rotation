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
    FILE* output = NULL;
    enum open_file_status openStatus = open_file(&input, argv[1], "rb");
    if (openStatus != OPEN_OK) return 1;
    openStatus = open_file(&output, argv[2], "wb");
    if (openStatus != OPEN_OK) return 1;

    struct image old_image = {0};
    struct image new_image = {0};

    enum read_status readStatus = read_bmp_file(input, &new_image);
    if (readStatus != READ_OK) fprintf(stderr, "%s", "Error during reading file.");
    new_image = rotate(old_image);

    enum write_status writeStatus = write_bmp_file(output, new_image);
    if (writeStatus != WRITE_OK) fprintf(stderr, "%s", "Error during writing into file.");

    destroy_image(old_image);
    destroy_image(new_image);

    enum close_file_status closeFileStatus = close_file(input);
    if (closeFileStatus != CLOSE_OK) fprintf(stderr, "%s", "Error during closing file.");
    closeFileStatus = close_file(output);
    if (closeFileStatus != CLOSE_OK) fprintf(stderr, "%s", "Error during closing file.");

    return 0;
}
