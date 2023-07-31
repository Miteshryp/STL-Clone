#pragma once
#include <cstdlib>
#include <string>

#include "containers/utils/types.hpp"

namespace pixel {

using namespace pixel::types;

    /**
     * @brief A template specialisation must be written by the 
     * user to use the hash function for custom types.
     * 
     * @tparam T 
     * @return size_t 
     */
    template<typename T>
    size_t hash();


    /**
     * @brief Hash function int specialisation
     * 
     * @tparam  
     * @return size_t 
     */
    template<>
    size_t hash<int32> () {
        // @todo: implement
    }

    template<>
    size_t hash<int64> () {
        // @todo: implement
    }

    template<>
    size_t hash<uint32> () {
        // @todo: implement
    }

    template<>
    size_t hash<uint64> () {
        // @todo: implement
    }

    template<>
    size_t hash<float32> () {
        // @todo: implement
    }

    template<>
    size_t hash<float64> () {
        // @todo: implement
    }


    template<>
    size_t hash<char> () {
        // @todo: implement
    }



    template<>
    size_t hash<std::string> () {
        // @todo: implement
    }


}