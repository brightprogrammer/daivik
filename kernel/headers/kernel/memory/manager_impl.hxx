#ifndef DAIVIK_KERNEL_MEMORY_MANAGER_IMPL_HXX
#define DAIVIK_KERNEL_MEMORY_MANAGER_IMPL_HXX 1

#include <cstddef>
#include <cstdint>

// kernel namespace
namespace kernel{

    // memory namespace
    namespace memory{

        // // set data from data to data+n the given value
        // template<typename data_type>
        // inline void set(data_type* data, const data_type& value, const size_t& n){
        //     for(size_t i = 0; i < n; i++) data[i] = value;
        // } // set template function

        // set first n bytes of data to value
        inline void set(void* data, const uint8_t& value, const size_t& n){
            uint8_t* _data_ = reinterpret_cast<uint8_t*>(data);
            for(size_t i = 0; i < n; i++) *(_data_+i) = value;
        } // set function

        // // copy given n values from src data to dest data
        // template<typename data_type>
        // inline void copy(data_type* dest, const data_type* src, const size_t& n){
        //     for(size_t i = 0; i < n; i++) dest[i] = src[i];
        // } // copy template function

        // copy first n bytes given src data to dest data 
        inline void copy(void* dest, const void* src, const size_t& n){
            uint8_t* _dest_ = reinterpret_cast<uint8_t*>(dest);
            const uint8_t* _src_ = reinterpret_cast<const uint8_t*>(src);
            for(size_t i = 0; i < n; i++) _dest_[i] = _src_[i];
        } // copy function
    
    } // memory namespace

} // kernel namespace

#endif//DAIVIK_KERNEL_MEMORY_MANAGER_IMPL_HXX