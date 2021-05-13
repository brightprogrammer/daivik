#ifndef DAIVIK_KERNEL_CONSOLE_TEXT_HXX
#define DAIVIK_KERNEL_CONSOLE_TEXT_HXX 1

#include <cstddef>
#include <cstdint>
#include <kernel/fonts/selected_font.hxx>

/// kernel namespace
namespace kernel {

    /// console namespace
    namespace console{

        /****************** default text settings ********************
         * width = __FONT_WIDTH__
         * height = __FONT_HEIGHT__
         * foreground_color = 0xafc7ed (light blue white)
         *************************************************************/

        /// text information to be written to console
        struct font{
            const uint8_t* buffer = font_buffer;

            /// text width in pixels
            size_t width = __FONT_WIDTH__;

            /// text height in pixels
            size_t height = __FONT_HEIGHT__;

            /// text foreground color
            uint32_t foreground_color = 0xafc7edff; // default to light blue white

            /// text background color
            uint32_t background_color = 0x00000000; // default to black
        }; // text struct

    } // console namespace

} // kernel namespace

#endif//DAIVIK_KERNEL_CONSOLE_TEXT_HXX