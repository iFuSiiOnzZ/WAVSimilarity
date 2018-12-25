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

///////////////////////////////////////////////////////////////////////////////

typedef struct file_in_memory_t
{
    void *Memory;
    size_t Size;
} file_in_memory;


// Given a file name, load the content of the file into the memory.
//
// INPUT:
//      const char * FileName               file name (path to the file)
//
// OUTPUT:
//      file_in_memory_t                    structure that contains a the file size
//                                          and a pointer in memory where the file
//                                          has been loaded
//
file_in_memory_t fnc_load_file_in_memory(const char * FileName);

// Given two vectors, it tells us how similar the two vectors are.
//
// INPUT:
//      file_in_memory_t *FileInMemory      structure that contains file information
//
// OUTPUT:
//      none
//
void fnc_release_file_from_memory(file_in_memory_t *FileInMemory);
