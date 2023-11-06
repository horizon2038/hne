#include <core/cpu/cpu.hpp>

namespace core
{
    cpu::cpu()
        : _registers{}
    {
    }

    cpu::~cpu()
    {
    }

    // clock() is called from boards
    void cpu::clock()
    {
        _registers.pc++;
    }

    void cpu::nmi()
    {
    }

    void cpu::reset()
    {
    }

    void cpu::irq()
    {
    }

    void cpu::brk()
    {
    }
}
