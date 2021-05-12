#include <cstdint>
#include <kernel/fonts/fonts.hxx>
#include <kernel/terminal/write.hxx>
#include <kernel/graphics/framebuffer.hxx>

// kernel namespace
namespace kernel{

    // write a simple char on screen
    void putchar(const uint8_t& c, const size_t& row, const size_t& col,
                const uint32_t& fg_color, const uint32_t& bg_color, const graphics::framebuffer framebuffer){
        // get glyph corresponding to given char
        const uint8_t* glyph = (font_buffer + c*FONT_HEIGHT);

        // get video memory address
        uint32_t* video_memory = reinterpret_cast<uint32_t*>(framebuffer.address);

        // iterate through rows
        for(size_t r = 0; r < FONT_HEIGHT; r++){
            // get pixel map
            uint8_t map = glyph[r+1];

            // mask to get bit
            uint8_t mask = 1 << (FONT_WIDTH - 1);

            // iterate through bits (pixels)
            for(size_t c = 0; c < FONT_WIDTH; c++){
                // light up pixels for corresponding bytes
                video_memory[(row+r)*framebuffer.width + col+c] = map & mask ? fg_color : bg_color;

                mask >>= 1;
            }
        }
    }

} // kernel namespace