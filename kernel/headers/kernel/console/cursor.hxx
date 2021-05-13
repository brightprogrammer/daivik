#ifndef DAIVIK_KERNEL_TERMINAL_CURSOR_HXX
#define DAIVIK_KERNEL_TERMINAL_CURSOR_HXX 1

#include <cstdint>
#include <cstddef>
#include <kernel/fonts/selected_font.hxx>

namespace kernel{

    /// console namespace
    namespace console{

            /// represents a cursor in a console
            struct cursor{
            private:
                size_t m_screen_width;
                size_t m_font_width = __FONT_WIDTH__;
                size_t m_font_height = __FONT_HEIGHT__;
                
            public:
                /// cursor row in character grid
                /// not in pixels
                size_t row = 0;

                /// cursor column in character grid
                /// not in pixels
                size_t column = 0;

                /// cursor color
                uint32_t color = 0xff0000ff; // red

                /// deleted construcotr
                cursor() = delete;

                /**
                 * @brief create a new cursor
                 * 
                 * @param screen_width : width of screen in character sizes
                 */
                cursor(const size_t& screen_width) : m_screen_width(screen_width) {}

                /**
                 * @brief create a new cursor
                 * 
                 * @param screen_width_px : width of screen in pixel sizes
                 * @param font_width : width of font in pixel sizes
                 */
                cursor(const size_t& screen_width_px, const size_t& font_width) : m_screen_width(screen_width_px/font_width){}

                /**
                 * @brief move cursor no next char position
                 * 
                 */
                inline void move_to_next_position(){
                    // move to new posn
                    column += m_font_width;

                    // check if cursor is in screen
                    if(column/m_font_width >= m_screen_width){
                        row += m_font_height;
                        column = 0;
                    }
                }
            };

    } // console namespace

} // 

#endif//DAIVIK_KERNEL_TERMINAL_CURSOR_HXX