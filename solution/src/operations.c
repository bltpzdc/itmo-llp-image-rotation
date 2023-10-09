//
// Created by Sevastian on 18.11.2022.
//

#include "operations.h"

enum open_file_status open_file(FILE** const file, char const * const file_name, char const * const mode){
    *file = fopen(file_name, mode);
    if (*file) return OPEN_OK;
    return OPEN_ERROR;
}

enum close_file_status close_file(FILE* const file){
    if (fclose(file)){
        return CLOSE_ERROR;
    }
    return CLOSE_OK;
}
