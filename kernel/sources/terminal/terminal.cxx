#include <kernel/terminal/terminal.hxx>

// kernel namespace
namespace kernel{
  
    // create a new terminal
    terminal::terminal(uint16_t* terminal_buffer) : terminal_buffer(terminal_buffer){
        terminal_row = 0;
        terminal_column = 0;
    }

} // kernel namespace