#include <core/cpu/opcode/opcode_none.hpp>

#include <cstdio>

namespace core
{
    void opcode_none::execute()
    {
        std::printf("this opcode is not yet implemented\n");
    }
}
