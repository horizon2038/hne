#ifndef BUS_HPP
#define BUS_HPP

#include <stdint.h>

namespace core
{
    class bus
    {
        void write_memory(uint16_t address, uint8_t data);
        uint8_t read_memory(uint16_t address);
    };
}

#endif
