//
// Created by Honor on 18.11.2022.
//
#include <stdio.h>

#ifndef UNTITLED1_OPERATIONS_H
#define UNTITLED1_OPERATIONS_H

enum open_file_status{
    OPEN_OK = 0,
    OPEN_ERROR
};

enum close_file_status{
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum open_file_status open_file(FILE** file, char* file_name, char* mode);
enum close_file_status close_file(FILE* file);

#endif //UNTITLED1_OPERATIONS_H
