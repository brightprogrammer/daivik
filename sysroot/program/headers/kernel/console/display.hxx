/**
 * @file display.hxx
 * @author Siddharth Mishra (bshock665@gmail.com)
 * @brief Console display manager. For printing and other things
 * @date 2021-05-11
 * 
 * @copyright Copyright (c) 2021 Siddharth Mishra, All Rights Reserved.
 * 
 */

#ifndef DAIVIK_KERNEL_CONSOLE_DISPLAY_HXX
#define DAIVIK_KERNEL_CONSOLE_DISPLAY_HXX 1

#include <cstddef>
#include <cstdint>
#include <kernel/console/print.hxx>
#include <kernel/graphics/framebuffer.hxx>

/// kernel namespace
namespace kernel{
    
    /// console namespace
    namespace console{

        /// display buffer in a console
        class display{
            graphics::framebuffer m_framebuffer;
            cursor m_cursor;
            font m_font;

        public:
            /**
            * @brief Construct a new display object
            * 
            * @param framebuffer : screen buffer information
            */
            inline display(const graphics::framebuffer& framebuffer) :
                m_framebuffer(framebuffer), 
                m_cursor(cursor(framebuffer.width / __FONT_WIDTH__)){}

            /**
            * @brief initialize display
            * 
            * @param framebuffer : screen buffer information
            */
            void initialize(const graphics::framebuffer& framebuffer);

            /**
             * @brief change cursor
             * 
             * @param _cursor 
             */
            void set_cursor(const cursor& _cursor);

            /**
             * @brief get current cursor
             * 
             * @return const reference to current cursor
             */
            const cursor& get_cursor() const;

            /**
            * @brief write a single character on screen
            * 
            * @param c : const reference to char
            */
            void write_char(const char& c);

            /**
            * @brief write a string on display
            * 
            * @param str : const char pointer 
            */
            void write_string(const char* str);

            /**
            * @brief write to display from data -> data+size
            * 
            * @param data : const char pointer
            * @param n : number of bytes to write to display 
            */
            void write_string(const char* data, const size_t& n);

            /**
             * @brief move cursor to next line
             * 
             */
            void next_line();

            /**
             * @brief move cursor to position after next n rows
             * 
             * @param n_rows 
             */
            void skip_rows(const size_t& n_rows);

            /**
             * @brief move cursor to next char position.
             *        can be used to skip a character (space for eg)
             * 
             */
            void next_position();

            /**
             * @brief skip to position after n_cols number of chars
             * 
             * @param n_cols : number of cols to skip
             */
            void skip_cols(const size_t& n_cols);

            /**
             * @brief move the content on display by n rows
             * 
             * @param n_rows : number of rows to shift up
             */
            void move_up(const size_t& n_rows);

        }; // display class

    } // console namespace

} // kernel namespace

#endif//DAIVIK_KERNEL_CONSOLE_DISPLAY_HXX