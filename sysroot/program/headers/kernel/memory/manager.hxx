#ifndef DAIVIK_KERNEL_MEMORY_MANAGER_HXX
#define DAIVIK_KERNEL_MEMORY_MANAGER_HXX 1

#include <cstddef>
#include <cstdint>

/// kernel namespace
namespace kernel{

    /// memmory namespace
    namespace memory{

        /**
         * @brief set starting n values in data array to given value
         * 
         * @param data pointer
         * @param value to set to
         * @param n number of values to set
         */
        inline void set(void* data, const uint8_t& value, const size_t& n);

        /**
         * @brief copies first n bytes from source to dest
         * 
         * @param dest 
         * @param source 
         * @param n 
         */
        inline void copy(void* dest, const void* source, const size_t& n);

    }; // memory namespace

} // kernel namespace

#include "manager_impl.hxx"

#endif//DAIVIK_KERNEL_MEMORY_MANAGER_HXX