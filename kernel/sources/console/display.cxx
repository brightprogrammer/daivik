#include <kernel/memory/manager.hxx>
#include <kernel/console/display.hxx>

// kernel namespace
namespace kernel{

    // console namespace
    namespace console{

            // initialize display
            void display::initialize(const graphics::framebuffer& framebuffer){
                m_framebuffer = graphics::framebuffer(framebuffer);
                m_cursor = cursor(framebuffer.width / __FONT_WIDTH__);
            }

            // change cursor
            void display::set_cursor(const cursor& _cursor){
                m_cursor = _cursor;
            }

            // get current cursor
            const cursor& display::get_cursor() const{
                return m_cursor;
            }

            // write a single character to display
            void display::write_char(const char& c){
                putchar(c, m_font, m_cursor, m_framebuffer);
                m_cursor.move_to_next_position();
            }

            // write a null terminated string to display
            void display::write_string(const char* str){
                // write till str[i] is valid
                for(size_t i = 0; str[i]; i++){
                    write_char(str[i]);
                }
            }

            // write a segment of string to display : firsr n bytes
            void display::write_string(const char* data, const size_t& n){
                for(size_t i = 0; i < n; i++){
                    write_char(data[i]);
                }
            }

            // move cursor to new line
            void display::next_line(){
                m_cursor.row += m_font.height;
                m_cursor.column = 0;
            }

            // move cursor to position after n rows
            void display::skip_rows(const size_t &n_rows){
                m_cursor.row += m_font.height * n_rows;
                m_cursor.column = 0;
            }

            // move cursor to next character
            void display::next_position(){
                m_cursor.move_to_next_position();
            }

            void display::skip_cols(const size_t &n_cols){
                for(size_t i = 0; i < n_cols; i++) m_cursor.move_to_next_position();
            }

            // move the content in display up by n rows
            void display::move_up(const size_t& n_rows){
                size_t n_total_pixels = m_cursor.row * m_font.height * m_framebuffer.width * sizeof(uint32_t);
                size_t n_discarded_pixels = (n_rows) * m_font.height * m_framebuffer.width * sizeof(uint32_t);
                size_t n_kept_pixels = (n_total_pixels - n_discarded_pixels);

                // points to start of screen
                uint32_t* dest = reinterpret_cast<uint32_t*>(m_framebuffer.address);
                
                // points to screen after n rows
                uint32_t* src = reinterpret_cast<uint32_t*>(m_framebuffer.address + n_discarded_pixels);
                
                // copy data
                memory::copy(dest, src, n_kept_pixels);
            }

            // write a 

    } // console namespace

} //kernel namespace