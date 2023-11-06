#ifndef RAM_HPP
#define RAM_HPP

#include <stdint.h>

namespace core
{
    class ram
    {
        uint8_t wram[0x800];
    };
}

#endif
