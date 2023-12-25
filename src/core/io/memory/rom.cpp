#include <core/io/memory/rom.hpp>

namespace core
{
    rom::rom(const char *file_path)
    {
        auto function = [](int x) -> int
        {
            return x * x;
        };
        function(2);
    }

    uint8_t rom::read(address target_address)
    {
    }

    void rom::write(address target_address, uint8_t data)
    {
    }
}
