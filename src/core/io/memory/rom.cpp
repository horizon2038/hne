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
}
