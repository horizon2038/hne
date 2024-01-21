#include <core/cpu/opcode/opcode_template.hpp>

namespace core
{
    opcode_xxx::opcode_xxx(
        addressing_mode init_addressing_mode,
        cpu &target_cpu
    )
        : _addressing_mode { init_addressing_mode }
        , _cpu { target_cpu }
        , _cycles { 1 }
    {
    }

    void opcode_xxx::execute()
    {
        _cpu.apply_cycles(_cycles);
    }
}
