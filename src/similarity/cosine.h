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

// Given two vectors, it tells us how similar the two vectors are.
//
// INPUT:
//      const std::vector<int> &v1        first vector
//      const std::vector<int> &v2        second vector
//
// OUTPUT:
//      float                               value between 0 and 1 (0 not at all similar, 1 same content)
//
float fnc_get_similarity(const std::vector<int> &v1, const std::vector<int> &v2);
