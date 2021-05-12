#ifndef DAIVIK_KERNEL_TERIMINAL_BUFFER_HXX
#define DAIVIK_KERNEL_TERIMINAL_BUFFER_HXX 1

#include <cstddef>
#include <cstdint>

// kernel namespace
namespace kernel{

    // terminal namespace
    namespace terminal{
        
        // terminal buffer
        template<typename video_memory_address_type>
        struct buffer{
            video_memory_address_type* video_memory;
            size_t row;
            size_t column;
            uint8_t background;
            uint8_t foreground;
        };
        
    }
}

#endif//DAIVIK_KERNEL_TERIMINAL_BUFFER_HXX