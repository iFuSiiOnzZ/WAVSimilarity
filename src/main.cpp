/*
    Project includes
*/
#include "similarity/cosine.h"
#include "utils/file.h"
#include "utils/wave.h"

/*
    Lib includes
*/

/*
    C/C++ includes
*/

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    file_in_memory_t FileContent_01 = fnc_load_file_in_memory(argv[1]);
    file_in_memory_t FileContent_02 = fnc_load_file_in_memory(argv[2]);

    if(!FileContent_01.Size || !FileContent_02.Size)
    {
        printf("File couldn't be loaded into memory\n");
        return EXIT_FAILURE;
    }

    wav_data_t WavData_01 = fnc_get_wav_data(FileContent_01.Memory, FileContent_01.Size);
    wav_data_t WavData_02 = fnc_get_wav_data(FileContent_02.Memory, FileContent_02.Size);

    std::vector<int> Samples_01, Samples_02;
    fnc_get_samples(WavData_01, Samples_01);
    fnc_get_samples(WavData_02, Samples_02);

    float r =  fnc_get_similarity(Samples_01, Samples_02);
    printf("WAV Similarity: %f%%\n", r);

    fnc_release_file_from_memory(&FileContent_01);
    fnc_release_file_from_memory(&FileContent_02);
    return EXIT_SUCCESS;
}
