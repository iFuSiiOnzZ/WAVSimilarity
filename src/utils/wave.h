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
#include <vector>

///////////////////////////////////////////////////////////////////////////////

typedef struct wav_header_t
{
    // NOTE(Andrei): RIFF Chunk Descriptor
    unsigned char       ChunkID      [4];
    unsigned int        ChunkSize       ;
    unsigned char       Format       [4];

    // NOTE(Andrei): fmt subchunk
    unsigned char       Subchunk1ID  [4];
    unsigned int        Subchunk1Size   ;
    unsigned short      AudioFormat     ;
    unsigned short      NumChannels     ;
    unsigned int        SampleRate      ;
    unsigned int        ByteRate        ;
    unsigned short      BlockAlign      ;
    unsigned short      BitsPerSample   ;
} wav_header_t;

typedef struct wav_chunk_t
{
    // NOTE(Andrei): data subchunk
    unsigned char       ID           [4];
    unsigned int        Size            ;
} wav_chunk_t;

typedef struct wav_data_t
{
    wav_header_t *Header;
    wav_chunk_t *Chunk;
    void *Samples;
} wav_data_t;

// Given a file name, load the content of the file into the memory.
//
// INPUT:
//      const wav_data_t &WavData           wav data structure information
//      std::vector<int> &SamplesOutput     [output] wav samples
//
// OUTPUT:
//      none
//
void fnc_get_samples(const wav_data_t &WavData, std::vector<int> &SamplesOutput);

// Gets the information of the wav file, header, chunks and samples.
//
// INPUT:
//      void * Memory                       memory where the wav file is loaded
//      size_t sz                           size in bytes of wav file
//
// OUTPUT:
//      wav_data_t                          structure that contains a the file size
//                                          and a pointer in memory where the file
//                                          has been loaded
//
wav_data_t fnc_get_wav_data(void * Memory, size_t sz);

// Prints the header information on standard output.
//
// INPUT:
//      const wav_header_t *WavHeader       WAV header information
//
// OUTPUT:
//      none
//
void fnc_print_wav_header(const wav_header_t *WavHeader);

// Prints the chunk information on standard output.
//
// INPUT:
//      const wav_chunk_t *Chunk            Wav chunk information
//
// OUTPUT:
//      none
//
void fnc_print_wav_chunk(const wav_chunk_t *Chunk);
