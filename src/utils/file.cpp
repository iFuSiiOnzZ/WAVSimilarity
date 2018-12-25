#include "file.h"

/*
    Project includes
*/

/*
    Lib includes
*/

/*
    C/C++ includes
*/
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

file_in_memory_t fnc_load_file_in_memory(const char * FileName)
{
    file_in_memory_t f = { 0 };
    struct stat st = { 0 };
    FILE *pFile = NULL;

    if (!stat((const char *)FileName, &st) && !fopen_s(&pFile, (const char *)FileName, "rb"))
    {
        f.Size = st.st_size;
        f.Memory = malloc(f.Size);

        fread(f.Memory, f.Size, 1, pFile);
        fclose(pFile);
    }

    return f;
}

void fnc_release_file_from_memory(file_in_memory_t *FileInMemory)
{
    if (FileInMemory->Memory)
    {
        FileInMemory->Size = 0;
        free(FileInMemory->Memory);
        FileInMemory->Memory = nullptr;
    }
}
