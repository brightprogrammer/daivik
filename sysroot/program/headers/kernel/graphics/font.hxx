#ifndef DAIVIK_KERNEL_GRAPHICS_FONT_HXX
#define DAIVIK_KERNEL_GRAPHICS_FONT_HXX 1

#include <cstdint>
#include <cstddef>

#define UNSIGNED_SHORT_MAX 65535 // 2^16 - 1

// get psf start from linked object file
extern char _binary_zap_ext_light16_psf_start;
extern char _binary_zap_ext_light16_psf_end;

// use shorter names
const char _binary_font_psf_start = _binary_zap_ext_light16_psf_start;
const char _binary_font_psf_end   = _binary_zap_ext_light16_psf_end;

// kernel namespace
namespace kernel{

    // graphics namespace
    namespace graphics{

        // psf font header
        typedef struct{
            uint32_t magic;
            uint32_t version;
            uint32_t header_size;
            uint32_t flags;
            uint32_t glyph_count;
            uint32_t bytes_per_glyph;
            uint32_t width;
            uint32_t height;
        } psf_font;

    } // graphics namespace

} // namespace kernel

#endif//DAIVIK_KERNEL_GRAPHICS_FONT_HXX