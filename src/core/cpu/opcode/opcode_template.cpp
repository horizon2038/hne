#include <core/cpu/opcode/opcode_template.hpp>

namespace core
{
    opcode_xxx::opcode_xxx(addressing_mode init_addressing_mode, cpu &target_cpu)
        : mode { init_addressing_mode }
        , root_cpu { target_cpu }
    {
    }

    void opcode_xxx::execute()
    {
        root_cpu.apply_cycles(0);
    }
}
