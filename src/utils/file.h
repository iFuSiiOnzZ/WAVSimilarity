#pragma once

/*
    Project includes
*/

/*
    Lib includes
*/

/*
    C/C++ includes
*/

typedef struct file_in_memory_t
{
    void *Memory;
    size_t Size;
} file_in_memory;

file_in_memory_t fnc_load_file_in_memory(const char * FileName);
void fnc_release_file_from_memory(file_in_memory_t *FileInMemory);
