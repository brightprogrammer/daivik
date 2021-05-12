#ifndef DAIVIK_KERNEL_TERMINAL_WRITE_HXX
#define DAIVIK_KERNEL_TERMINAL_WRITE_HXX 1

#include <cstdint>
#include <cstddef>
#include <kernel/graphics/framebuffer.hxx>
#include <kernel/fonts/fonts.hxx>

// kernel namespace
namespace kernel{

    /**
     * @brief write a simple char on scree
     * 
     * @param c character id
     * @param row cursor row
     * @param col cursor column
     * @param fg_color foreground color
     * @param bg_color background color
     * @param framebuffer const reference to framebuffer
     */
    void putchar(const uint8_t& c, const size_t& row, const size_t& col,
                const uint32_t& fg_color, const uint32_t& bg_color, const graphics::framebuffer framebuffer);
} // kernel namespace

#endif//DAIVIK_KERNEL_TERMINAL_WRITE_HXX