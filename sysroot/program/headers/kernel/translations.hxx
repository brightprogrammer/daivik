/**
 * @file translations.hxx
 * @author Siddharth Mishra (bshock665@gmail.com)
 * @brief constains functions to translate one struct or object another
 * @date 2021-05-12
 * 
 * @copyright Copyright (c) 2021 Siddharth Mishra. All Rights Reserved.
 * 
 */

#ifndef DAIVIK_KERNEL_TRANSLATIONS_HXX
#define DAIVIK_KERNEL_TRANSLATIONS_HXX 1

#include <kernel/stivale2.h>
#include <kernel/graphics/framebuffer.hxx>

namespace kernel{
    inline void copy_framebuffer_from_stivale(graphics::framebuffer& framebuffer, const stivale2_struct_tag_framebuffer* framebuffer_tag){
        framebuffer.address             = framebuffer_tag->framebuffer_addr;
        framebuffer.bits_per_pixel      = framebuffer_tag->framebuffer_bpp;
        framebuffer.pitch               = framebuffer_tag->framebuffer_pitch;
        framebuffer.width               = framebuffer_tag->framebuffer_width;
        framebuffer.height              = framebuffer_tag->framebuffer_height;
        framebuffer.blue_mask_shift     = framebuffer_tag->blue_mask_shift;
        framebuffer.blue_mask_size      = framebuffer_tag->blue_mask_size;
        framebuffer.red_mask_shift      = framebuffer_tag->red_mask_shift;
        framebuffer.red_mask_size       = framebuffer_tag->red_mask_size;
        framebuffer.green_mask_shift    = framebuffer_tag->green_mask_shift;
        framebuffer.green_mask_size     = framebuffer_tag->green_mask_size;
        framebuffer.memory_model        = framebuffer_tag->memory_model;
    }
}

#endif