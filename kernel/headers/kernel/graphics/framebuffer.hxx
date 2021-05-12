#ifndef DAIVIK_KERNEL_GRAPHICS_FRAMEBUFFER_HXX
#define DAIVIK_KERNEL_GRAPHICS_FRAMEBUFFER_HXX 1

#include <cstdint>
#include <cstddef>

// kernel namespace
namespace kernel{

    // graphics namespace
    namespace graphics{

        // contains framebuffer information
        struct framebuffer{
            uint64_t address;
            uint16_t width;
            uint16_t height;
            uint16_t pitch;
            uint16_t bits_per_pixel;
            uint8_t  memory_model;
            uint8_t  red_mask_size;
            uint8_t  red_mask_shift;
            uint8_t  green_mask_size;
            uint8_t  green_mask_shift;
            uint8_t  blue_mask_size;
            uint8_t  blue_mask_shift;
        };
    
    } // graphics namespace

} // graphics namespace

#endif//DAIVIK_KERNEL_GRAPHICS_FRAMEBUFFER_HXX