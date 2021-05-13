#ifndef DAIVIK_KERNEL_FONTS_FONT_HXX
#define DAIVIK_KERNEL_FONTS_FONT_HXX 1

#include <kernel/fonts/selected/wang_bios_8x16.hxx>

/// to select a font : 
/// include a preferred font from selected directory and change the width and height accordingly
/// warning : setting different width and height will result in undefined behaviour

/// define font width in pixels
#define __FONT_WIDTH__  8

/// define font height in pixels
#define __FONT_HEIGHT__  16

#endif//DAIVIK_KERNEL_FONTS_FONT_HXX