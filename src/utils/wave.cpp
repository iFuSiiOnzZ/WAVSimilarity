/*
    Project includes
*/

#include "Wave.h"

/*
    Lib includes
*/

/*
    C/C++ includes
*/
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////

template <typename SampleType> static void fnc_get_samples_tmp(void *Samples, long long NumSamples, std::vector<int> &SamplesOutput)
{
    SampleType *WavSamples = (SampleType *) Samples;

    for (long long i = 0; i < NumSamples; ++i)
    {
        SamplesOutput[i] = (int)WavSamples[i];
    }
}

///////////////////////////////////////////////////////////////////////////////

void fnc_print_wav_header(const wav_header_t *WavHeader)
{
    // NOTE(Andrei): RIFF Chunk Descriptor
    printf("ChunkID  : %.4s\n"  , WavHeader->ChunkID  );
    printf("ChunkSize: %d\n"    , WavHeader->ChunkSize);
    printf("Format   : %.4s\n\n", WavHeader->Format   );

    // NOTE(Andrei): fmt subchunk
    printf("Subchunk1ID   : %.4s\n", WavHeader->Subchunk1ID   );
    printf("Subchunk1Size : %d\n"  , WavHeader->Subchunk1Size );
    printf("AudioFormat   : %d\n"  , WavHeader->AudioFormat   );
    printf("NumChannels   : %d\n"  , WavHeader->NumChannels   );
    printf("SampleRate    : %d\n"  , WavHeader->SampleRate    );
    printf("ByteRate      : %d\n"  , WavHeader->ByteRate      );
    printf("BlockAlign    : %d\n"  , WavHeader->BlockAlign    );
    printf("BitsPerSample : %d\n\n", WavHeader->BitsPerSample );
}

void fnc_print_wav_chunk(const wav_chunk_t *Chunk)
{
    // NOTE(Andrei): data subchunk
    printf("ChunkID  : %.4s\n", Chunk->ID       );
    printf("ChunkSize: %d\n\n", Chunk->Size     );
}

wav_data_t fnc_get_wav_data(void * Memory, size_t sz)
{
    wav_data_t WavData = { 0 };

    if(!sz || !Memory)
    {
        return WavData;
    }

    wav_header_t *WavHeader = (wav_header_t *)Memory;

    if(WavHeader->ChunkID[0] != 'R' && WavHeader->ChunkID[1] != 'I' && WavHeader->ChunkID[2] != 'F' && WavHeader->ChunkID[0] != 'F')
    {
        return WavData;
    }

    if(WavHeader->Format[0] != 'W' && WavHeader->Format[1] != 'A' && WavHeader->Format[2] != 'V' && WavHeader->Format[0] != 'E')
    {
        return WavData;
    }

    wav_chunk_t *WavChunk = (wav_chunk_t  *)((char *)Memory + sizeof(wav_header_t));

    while (WavChunk->ID[0] != 'd' && WavChunk->ID[1] != 'a' && WavChunk->ID[2] != 't' && WavChunk->ID[3] != 'a')
    {
        WavChunk = (wav_chunk_t *)((char *)WavChunk + sizeof(wav_chunk_t) + WavChunk->Size);
    }

    if(WavChunk->ID[0] == 'd' && WavChunk->ID[1] == 'a' && WavChunk->ID[2] == 't' && WavChunk->ID[3] == 'a')
    {
        void *Samples = (void *)((char *)WavHeader + sizeof(wav_chunk_t));
        WavData.Chunk = WavChunk; WavData.Samples = Samples; WavData.Header = WavHeader;
    }

    return WavData;
}

void fnc_get_samples(const wav_data_t &WavData, std::vector<int> &SamplesOutput)
{
    long long NumSamples = (8 * WavData.Chunk->Size) / (WavData.Header->BitsPerSample  * WavData.Header->NumChannels);
    SamplesOutput.resize(NumSamples);

    if(WavData.Header->BitsPerSample  == 16)
    {
        fnc_get_samples_tmp<short>(WavData.Samples, NumSamples, SamplesOutput);
    }
    else if(WavData.Header->BitsPerSample  == 8)
    {
        fnc_get_samples_tmp<char>(WavData.Samples, NumSamples, SamplesOutput);
    }
}
