#include <core/io/memory/ram.hpp>

namespace core
{
    uint8_t working_ram::read(address target_address)
    {
        return _ram[target_address];
    }

    void working_ram::write(address target_address, uint8_t data)
    {
        _ram[target_address] = data;
    }
}
