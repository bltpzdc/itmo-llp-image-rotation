//
// Created by Honor on 18.11.2022.
//

#include "operations.h"

enum open_file_status open_file(FILE** file, char* file_name, char* mode){
    *file = fopen(file_name, mode);
    if (*file) return OPEN_OK;
    fprintf(stderr, "%s", "Error during file opening.");
    return OPEN_ERROR;
}

enum close_file_status close_file(FILE* file){
    if (fclose(file)){
        fprintf(stderr, "%s", "Error during file closing.");
        return CLOSE_ERROR;
    }
    return CLOSE_OK;
}
