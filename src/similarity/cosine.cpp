/*
    Project includes
*/
#include "cosine.h"

/*
    Lib includes
*/

/*
    C/C++ includes
*/
#include <algorithm>

/*
    Defines
*/

#ifndef ASSERT
    #define ASSERT(x, msg) do{ if(!(x)){*(int *)0 = 0;} }while(0)
#endif

///////////////////////////////////////////////////////////////////////////////

// Inserts an element into a vector sorted vector.
//
// INPUT:
//      std::vector<T>  &vector                vector where to insert the element
//      const T         &element               element to insert
//
// OUTPUT:
//      nothing
//
template <typename T> static void fnc_insert_sorted(std::vector<T> &vector, const T &element)
{
    std::vector<T>::const_iterator it = std::upper_bound(vector.begin(), vector.end(), element);
    vector.insert(it, element);
}

// Searches if an element exists into the vector. The vector has to be sorted
// as is using binary search.
//
// INPUT:
//      std::vector<T> &vector                  vector where where to search
//      const T        &element                 element to serach
//
// OUTPUT:
//      bool                                    true if found, false otherwise
//
template <typename T> static bool fnc_has_element(const std::vector<T> &vector, const T &element)
{
    return std::binary_search(vector.begin(), vector.end(), element);
}

// The function generates as output the union of the two input vector.
// The oputput will contain the values of the first and second vector
// without repetitions.
//
// INPUT:
//      const std::vector<T> &v1        first input vector
//      const std::vector<T> &v2        second input vector
//
// OUTPUT:
//      std::vector<T>                  the union of the two input vectos
//
template <typename T> std::vector<T> fnc_unique_combination_of(const std::vector<T> &v1, const std::vector<T> &v2)
{
    std::vector<T> retData;
    retData.reserve((v1.size() + v2.size()) / 4);

    for(size_t i = 0; i < v1.size(); ++i)
    {
        if(fnc_has_element(retData, v1[i])) continue;
        fnc_insert_sorted(retData, v1[i]);
    }

    for(size_t i = 0; i < v2.size(); ++i)
    {
        if(fnc_has_element(retData, v2[i])) continue;
        fnc_insert_sorted(retData, v2[i]);
    }

    return retData;
}

// Searches if an element exists into the vector. The vector has to be sorted
// as is using binary search.
//
// INPUT:
//      const T              &element       element to search in the vector
//      const std::vector<T> &data          vector where to search the element
//      size_t &out_data                    index where the element has been found
//
// OUTPUT:
//      bool                                true if found, false otherwise
//
template <typename T> bool fnc_binary_search_find_index(const T &element, const std::vector<T> &data, size_t &index)
{
    std::vector<T>::const_iterator it = std::lower_bound(data.begin(), data.end(), element);
    if (it == data.end() || *it != element) return false;

    index = std::distance(data.begin(), it);
    return true;
}

// Searches how many times the second input can be found in the first input.
// The output is stored into the third parameter. Second input has to be
// sorted as the function is making use of binary search.
//
// INPUT:
//      const std::vector<int> &v1          first input vector
//      const std::vector<int> &v2          second input vector (sorted vector)
//            std::vector<int> &out_data    output data
//
// OUTPUT:
//      nothing
//
static void fnc_calculate_frequency(const std::vector<int> &v1, const std::vector<int> &v2, std::vector<int> &out_data)
{
    for(size_t i = 0, index = 0; i < v1.size(); ++i)
    {
        if(fnc_binary_search_find_index(v1[i], v2, index))
        {
            ++out_data[index];
        }
    }
}

// Given two vectors, calculates the cosine between the two vectors. If one vector is
// is shorter than than the other one, it will take the size of the shortest vector
// for calculating the cosine.
//
// INPUT:
//      const std::vector<InputType> &v1    first vector
//      const std::vector<InputType> &v2    second vector
//
// OUTPUT:
//      OutputType                          the cosine betweeen the two vectors
//
template <typename InputType, typename OutputType> static OutputType fnc_calculate_cosine(const std::vector<InputType> &v1, const std::vector<InputType> &v2)
{
    ASSERT(v1.size() == v2.size(), "Size of both vectors has to be the same");
    OutputType NormV1 = 0.0f, NormV2 = 0.0f, DotProduct = 0.0f;

    for(size_t i = 0; i < v1.size(); ++i)
    {
        DotProduct  += (OutputType)v1[i] * (OutputType)v2[i];
        NormV1      += (OutputType)v1[i] * (OutputType)v1[i];
        NormV2      += (OutputType)v2[i] * (OutputType)v2[i];
    }

    OutputType sqrtNorm = std::sqrt(NormV1 * NormV2);
    OutputType retData = DotProduct / sqrtNorm;

    return retData;
}

// Description of the function in .h file
//
float fnc_get_similarity(const std::vector<int> &v1, const std::vector<int> &v2)
{
    std::vector<int> UnionOfTheInput = fnc_unique_combination_of(v1, v2);
    std::vector<int> a(UnionOfTheInput.size(), 0), b(UnionOfTheInput.size(), 0);

    ASSERT(a.size() == UnionOfTheInput.size(), "Size of 'a' not equal to the size of the union");
    ASSERT(b.size() == UnionOfTheInput.size(), "Size of 'b' not equal to the size of the union");

    fnc_calculate_frequency(v1, UnionOfTheInput, a);
    fnc_calculate_frequency(v2, UnionOfTheInput, b);

    return fnc_calculate_cosine<int, float>(a, b);
}
