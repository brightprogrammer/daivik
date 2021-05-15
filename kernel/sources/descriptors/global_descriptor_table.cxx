#include <cstdint>
#include <cstring>
#include <kernel/descriptors/global_descriptor_table.hxx>
#include <string.h>

// kernel namespace
namespace kernel{

    global_descriptor_table::global_descriptor_table() :
    m_null_segment_selector(0, 0, 0),
    m_unused_segment_selector(0, 0, 0),
    m_code_segment_selector(0, 64*1024*1024, 0x9a),
    m_data_segment_selector(0, 64*1024*1024, 0x92)
    {
        // first 4 bytes is address, next 16 bytes are empty, and upper 16 bytes is size
        uint32_t gdt_info[2];
        gdt_info[0] = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this));
        gdt_info[1] = sizeof(global_descriptor_table) << 16;

        // pass gdt info to cpu
        auto gdt_addr = gdt_info+2;
        asm volatile("lgdt %0": :"m"(gdt_addr));
    }

    global_descriptor_table::~global_descriptor_table(){

    }

    uint16_t global_descriptor_table::data_segment_selector(){
        return (reinterpret_cast<uintptr_t>(&m_data_segment_selector) - reinterpret_cast<uintptr_t>(this));
    }

    uint16_t global_descriptor_table::code_segment_selector(){
        return (reinterpret_cast<uintptr_t>(&m_data_segment_selector) - reinterpret_cast<uintptr_t>(this));
    }

    segment_descriptor::segment_descriptor(uint32_t base, uint32_t limit, uint8_t flags){
        uint8_t* target = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this));

        // if limit is less than 2^16 (0xFFFF) then set flags_limit_high = 64
        if(limit < 66536) target[6] = 0x40;

        // if limit is is greater than 2^16 (0xFFFF)
        else{
            // if limit lies in range 0x0FFF -> 0xEFFF
            if((limit & 0xFFF) != 0xFFF) limit = (limit >> 12) - 1; // limit = 0x{hex}FFF -> close to 0xFFFF
            
            // if limit lies in range 0x0000 -> 0x0EFF
            else limit = (limit >> 12); // limit < 0x0FFF

            target[6] = 0xC0;
        }

        /*                                   [ DESCRIPTOR LAYOUT ]
            There is no specific reason for this to be in this manner
            This is in this way because it was modified in each arch and backwards compatibility was needed 
        ***********************************************************************************************
        |             |            |             |              |              |        |             |
        |  Limit 0:15 |  Base 0:15 |  Base 16:23 |  Access Byte |  Limit 16:19 |  Flags |  Base 24:31 |
        |0          15|16        31|32         39|40          47|48          51|52    55|56         63|
        ***********************************************************************************************
        */

        /*                                           [ ACCESS BYTE ]
        ************************************************************************************************************************************
        | Access | Read/Write | Direction/Conforming | Executable | Descriptor Type | Privilege Level (2 bits) ; bit0 ; bit1 | Present Bit |
        ************************************************************************************************************************************
        > Access               : just set to 0, CPU automatically sets this to 1 when segment is accessed
        > Read/Write           : if this is code selector then this will set readability, else if this is data selector then this will set writeability
        > Direction/Conforming : if this is code selector then this will act as conforming bit, else if this is data segment then this will act as direction bit
            + ----> Direction Bit :
            + ----+---> will set which direction the data grows. 0 means up and 1 means down. 
            + ----+---> If data grows up then base address is greater than offset otherwise offset is greater than base
            + ----+----> up is most suitable for heap and down for a stack
            + ----> Conforming Bit :
            + ----+----> If equal to 1, code in this segment can be executed from an equal or lower privilege level. 
            + ----+----> For example, code in ring 3 can far-jump to conforming code in a ring 2 segment. 
            + ----+----> The privl-bits represent the highest privilege level that is allowed to execute 
            + ----+----> the segment. For example, code in ring 0 cannot far-jump to a conforming code segment
            + ----+----> with privl==0x2, while code in ring 2 and 3 can. Note that the privilege level remains
            + ----+----> the same, ie. a far-jump form ring 3 to a privl==2-segment remains in ring 3 after the jump.
            + ----+----> If equal to 0, code in this segment can only be executed from the ring set in privl. 
        > Executable           : if 1 then this is a code selector (instructions/data can be executed : only read/execute permission, no writing) else this is a data segment (only read/write permissions no execution)
        > Descriptor Type      : equal to 1 for data segments, 0 for system segments (https://wiki.osdev.org/Task_State_Segment)
        > Privilege Level      : contains ring level (0 -> 3)
        > Preset Bit           : must be 1 for all valid selectors
        */

        /*          [ Flags Bit ]
        **************************************
        | Granularity Bit | Size Bit | 0 | 0 |
        **************************************
        > Granularity Bit : if equal to 0 then limit is in 1 byte blocks else the limit is in 4kb blocks
        > Size Bit        : if equal to 0 then selector defines 16 bit protected mode, else if equal to 1 then 32 bit protected mode. We can have both 32 bit and 16 bit selectors at once
        */

        // set limit                                        ---range--
        // store first 16 bits of limit
        target[0] = limit & 0xFF;                           // 00 - 07
        target[1] = (limit >> 8) & 0xFF;                    // 08 - 15

        // store the 16-23 bits possible values are : 0x40->0x4F and 0xC0->0xCF
        // this will or the value of target[6] with 5th nibble of limit
        // if limit = 0xCAFEBABE then limit is updated as limit |= 0xE & 0xF => limit = 0x4E or 0xCE
        target[6] |= (limit >> 16) & 0xF;                   // 48 - 53
        
        // set first 32 bits of base : meaning whole base
        target[2] =  base        & 0xFF;                    // 16 - 23
        target[3] = (base >> 8)  & 0xFF;                    // 24 - 31
        target[4] = (base >> 16) & 0xFF;                    // 32 - 39
        target[7] = (base >> 24) & 0xFF;                    // 56 - 63

        // set flags
        // flags is just access byte
        target[5] = flags;                                  // 40 - 47
    }
    
    uint32_t segment_descriptor::base(){
        uint8_t* target = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this));
        uint32_t result = target[7];
        result = (result << 8) + target[4];
        result = (result << 8) + target[3];
        result = (result << 8) + target[2];

        return result;
    }

    uint32_t segment_descriptor::limit(){
        uint8_t* target = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this));
        uint32_t result = target[6] & 0xF;
        result = (result << 8) + target[1];
        result = (result << 8) + target[0];

        if((target[6] & 0xC0) == 0xC0)
            result = (result << 12) & 0xFFF;
        
        return result;
    }

} // kernel namespace