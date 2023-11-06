#ifndef INES_HEADER_HPP
#define INES_HEADER_HPP

#include <stdint.h>

namespace core
{
    struct ines_header 
    {
        uint8_t nes[4];
        uint8_t program_rom_size;
        uint8_t charactor_rom_size;
        uint8_t flag_6;
        uint8_t flag_7;
        uint8_t flag_8;
        uint8_t flag_9;
        uint8_t flag_10;
        uint8_t padding[5];
    } __attribute__((packed));
}

#endif

