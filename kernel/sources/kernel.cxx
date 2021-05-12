#include "kernel/fonts/fonts.hxx"
#include "kernel/terminal/terminal.hxx"
#include <kernel/stivale2.h>
#include <cstddef>
#include <cstdint>
#include <kernel/GlobalDescriptorTable.hxx>
#include <kernel/terminal/write.hxx>
#include <kernel/graphics/framebuffer.hxx>

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
    struct stivale2_struct_tag_framebuffer* framebuffer_tag;
    
    // get pointer to framebuffer tag returned from a linked list of tags
    framebuffer_tag = reinterpret_cast<stivale2_struct_tag_framebuffer*>(stivale_get_tag(stivale_struct, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID));
    
    // if tag is not present then halt system
    if(!framebuffer_tag){
        halt();
    }

    // set framebuffer information
    static kernel::graphics::framebuffer framebuffer;
    framebuffer.address = framebuffer_tag->framebuffer_addr;
    framebuffer.bits_per_pixel = framebuffer_tag->framebuffer_bpp;
    framebuffer.pitch = framebuffer_tag->framebuffer_pitch;
    framebuffer.width = framebuffer_tag->framebuffer_width;
    framebuffer.height = framebuffer_tag->framebuffer_height;
    framebuffer.blue_mask_shift = framebuffer_tag->blue_mask_shift;
    framebuffer.blue_mask_size = framebuffer_tag->blue_mask_size;
    framebuffer.red_mask_shift = framebuffer_tag->red_mask_shift;
    framebuffer.red_mask_size = framebuffer_tag->red_mask_size;
    framebuffer.green_mask_shift = framebuffer_tag->green_mask_shift;
    framebuffer.green_mask_size = framebuffer_tag->green_mask_size;
    framebuffer.memory_model = framebuffer_tag->memory_model;
    

    // create global descriptor table
    GlobalDescriptorTable gdt;

    size_t x = FONT_WIDTH, y = 10;
    for(size_t c = 0; c < 256; c++){
        kernel::putchar(c, y, x, 0xdeadbeef, 0x00000000, framebuffer);
        x += 8;
        if(x >= framebuffer.width - FONT_WIDTH){
            y+=16;
            x=FONT_WIDTH;
        }
    }

    // at the end we have to halt anyway
    halt();
}