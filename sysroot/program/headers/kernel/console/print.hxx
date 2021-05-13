#ifndef DAIVIK_KERNEL_CONSOLE_PRINT_HXX
#define DAIVIK_KERNEL_CONSOLE_PRINT_HXX 1

#include <cstdint>
#include <cstddef>
#include <kernel/graphics/framebuffer.hxx>
#include <kernel/console/cursor.hxx>
#include <kernel/console/font.hxx>

// kernel namespace
namespace kernel{

    // console namespace
    namespace console{

        /**
        * @brief write a simple char on scree
        * 
        * @param c character id
        * @param _font : const reference to a font, gives information about color etc.
        * @param _cursor : const reference to a cursor, gives information about position etc.
        * @param _framebuffer const reference to a framebuffer, gives information about screen framebuffer, address, depth etc.
        */
        void putchar(const uint8_t& c, const font& _font, const cursor& _cursor, const graphics::framebuffer _framebuffer);

    } // console namespace

} // kernel namespace

#endif//DAIVIK_KERNEL_CONSOLE_PRINT_HXX