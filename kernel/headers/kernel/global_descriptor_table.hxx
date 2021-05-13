#ifndef DAIVIK_KERNEL_GLOBAL_DESCRIPTOR_TABLE_HXX
#define DAIVIK_KERNEL_GLOBAL_DESCRIPTOR_TABLE_HXX 1

#include <stdint.h>
#include <stddef.h>

/// segment descriptor layout for global descriptor table
class segment_descriptor{
    uint16_t limit_low;         // 0th and 1st byte
    uint16_t base_low;          // 2nd and 3rd byte
    uint8_t base_medium;        // 4th byte
    uint8_t type;               // 5th byte
    uint8_t flags_limit_high;   // 6th byte
    uint8_t base_high;          // 7th byte
public:
    segment_descriptor(uint32_t base, uint32_t limit, uint8_t type);
    uint32_t base();
    uint32_t limit();
} __attribute__((packed));

/// global descriptor table
class global_descriptor_table{
    // first descriptor must be used as a null descriptor
    segment_descriptor m_null_segment_selector;
    segment_descriptor m_unused_segment_selector; // for es, ss, fs
    segment_descriptor m_code_segment_selector; // for cs
    segment_descriptor m_data_segment_selector; // for ds
public:
    global_descriptor_table();
    ~global_descriptor_table();

    uint16_t data_segment_selector();
    uint16_t code_segment_selector();
}__attribute__((packed));

#endif//DAIVIK_KERNEL_GLOBAL_DESCRIPTOR_TABLE_HXX