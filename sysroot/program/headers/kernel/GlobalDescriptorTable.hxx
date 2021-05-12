#ifndef __GlobalDescriptorTable_H
#define __GlobalDescriptorTable_H 1

#include <stdint.h>
#include <stddef.h>

/// segment descriptor layout for global descriptor table
class SegmentDescriptor{
    uint16_t limit_low;         // 0th and 1st byte
    uint16_t base_low;          // 2nd and 3rd byte
    uint8_t base_medium;        // 4th byte
    uint8_t type;               // 5th byte
    uint8_t flags_limit_high;   // 6th byte
    uint8_t base_high;          // 7th byte
public:
    SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
    uint32_t Base();
    uint32_t Limit();
} __attribute__((packed));

/// global descriptor table
class GlobalDescriptorTable{
    // first descriptor must be used as a null descriptor
    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector; // for es, ss, fs
    SegmentDescriptor codeSegmentSelector; // for cs
    SegmentDescriptor dataSegmentSelector; // for ds
public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();
}__attribute__((packed));

#endif//__GlobalDescriptorTable_H