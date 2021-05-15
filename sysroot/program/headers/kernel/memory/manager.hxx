/**
 * @file manager.hxx
 * @author Siddharth Mishra (bshock665@gmail.com)
 * @brief Memory manager functions/classes/helpers for kernel
 * @date 2021-05-13
 * 
 * @copyright Copyright (c) 2021 Siddharth Mishra, All Rights Reserved.
 * 
 */

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
        void set(void* data, const uint8_t& value, const size_t& n);

        /**
         * @brief copies first n bytes from source to dest
         * 
         * @param dest 
         * @param source 
         * @param n 
         */
        void copy(void* dest, const void* source, const size_t& n);

    }; // memory namespace

} // kernel namespace

#endif//DAIVIK_KERNEL_MEMORY_MANAGER_HXX