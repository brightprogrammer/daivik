#include <cstdint>
#include <kernel/console/print.hxx>


// kernel namespace
namespace kernel{

    // console namespace
    namespace console{

        // write a simple char on screen
        void putchar(const uint8_t& c, const font& _font, const cursor& _cursor, const graphics::framebuffer _framebuffer){
            // get glyph corresponding to given char
            const uint8_t* glyph = ( _font.buffer + c * _font.height );

            // get video memory address
            uint32_t* video_memory = reinterpret_cast<uint32_t*>(_framebuffer.address);

            // iterate through rows
            for(size_t r = 0; r < _font.height; r++){
                // get pixel map
                uint8_t map = glyph[r+1];

                // masking must start with most significant bit
                // else the written text will be mirror image of the desired font
                uint8_t mask = 1 << ( _font.width - 1 );

                // iterate through bits (pixels)
                for(size_t c = 0; c < _font.width; c++){
                    // light up pixels for corresponding bytes
                    video_memory[ (( _cursor.row + r ) * _framebuffer.width) + (_cursor.column + c) ] = map & mask ? _font.foreground_color : _font.background_color;
                    
                    // set mask to get next pixel (bit)
                    mask >>= 1;
                }
            }
        } // putchar

    } // console namespace

} // kernel namespace