#ifndef DAIVIK_KERNEL_TERMINAL_HXX
#define DAIVIK_KERNEL_TERMINAL_HXX 1

#include <cstddef>
#include <cstdint>

// kernel namespace
namespace kernel{

    /**
     * @brief represents a terminal
     * 
     */
    class terminal{
        size_t terminal_row;
        size_t terminal_column;
        uint8_t terminal_color;
        uint16_t* terminal_buffer;
    public:
        /**
         * @brief Construct a new Terminal object (default)
         * 
         */
        terminal() = default;

        /**
         * @brief Construct a new Terminal object
         * 
         * @param terminal_buffer : pointer to screen buffer
         */
        terminal(uint16_t* terminal_buffer);

        /**
         * @brief initialize terminal
         * 
         */
        void initialize(const uint16_t& terminal_buffer);

        /**
         * @brief write a single character on screen
         * 
         * @param c : const reference to char
         */
        void writeChar(const char& c);

        /**
         * @brief write a string on terminal
         * 
         * @param str : const char pointer 
         */
        void writeString(const char* str);

        /**
         * @brief write to terminal from data -> data+size
         * 
         * @param data : const char pointer
         * @param size : const reference to size_t 
         */
        void write(const char* data, const size_t& size);

    }; // terminal class

} // kernel namespace

#endif//DAIVIK_KERNEL_TERMINAL_WRITE_HXX