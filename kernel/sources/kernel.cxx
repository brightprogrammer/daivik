#include <kernel/stivale2.h>
#include <cstddef>
#include <cstdint>
#include <kernel/global_descriptor_table.hxx>
#include <kernel/console/terminal.hxx>
#include <kernel/translations.hxx>

// give this pointer to stivale
// so that stivale can use this as stack
static uint8_t stack[4096];

// framebuffer header tag
static struct stivale2_header_tag_framebuffer framebuffer_header_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = 0
    },
    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0
};

// give headers to stivale
// this will put the below information in stivale2hdr section
__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_header = {
    .entry_point = 0,
    .stack = (uintptr_t)stack + sizeof(stack),
    .flags = 0,
    .tags = (uintptr_t)&framebuffer_header_tag
};

// helper function to get header tag of given id in a linked list
void* stivale_get_tag(struct stivale2_struct *stivale_struct, uint64_t id) {
    struct stivale2_tag *current_tag = reinterpret_cast<stivale2_tag*>(stivale_struct->tags);
    for(;;){
        if(current_tag == NULL) return NULL;
        if(current_tag->identifier == id) return current_tag;
        current_tag = reinterpret_cast<stivale2_tag*>(current_tag->next);
    }
}

// halts the processor when called
void halt(){
    for(;;){
        asm("hlt");
    }
}

// kernel entry point
extern "C" void kernel_main(struct stivale2_struct *stivale_struct){
    // framebuffer tag stores information about framebuffer
    struct stivale2_struct_tag_framebuffer* framebuffer_tag;
    
    // get pointer to framebuffer tag returned from a linked list of tags
    framebuffer_tag = reinterpret_cast<stivale2_struct_tag_framebuffer*>(stivale_get_tag(stivale_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID));

    // if tag is not present then halt system
    if(!framebuffer_tag){
        halt();
    }

    // set framebuffer information
    static kernel::graphics::framebuffer framebuffer;
    kernel::copy_framebuffer_from_stivale(framebuffer, framebuffer_tag);
    
    // create global descriptor table
    global_descriptor_table gdt;

    // create a new terminal
    kernel::console::terminal terminal(framebuffer);
    terminal.write_string("hello user, I am daivik -.-");
    terminal.next_line();
    terminal.write_string("Hey, I just skipped the cursor to next line!");
    terminal.skip_rows(5);
    terminal.write_string("I skipped 5 lines this time");
    terminal.next_line();
    terminal.skip_cols(5);
    terminal.write_string("This time, I skipped 5 spaces before printing this!");
    terminal.move_up(3);

    // at the end we have to halt anyways
    halt();
}