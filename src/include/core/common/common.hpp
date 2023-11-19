#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdint.h>

namespace core
{
    using address = uint16_t;

    inline static address merge_address(uint8_t lower_address, uint8_t higher_address)
    {
        return lower_address | (higher_address << 8);
    }

}

#endif
