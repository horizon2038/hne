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

    void cpu::reset()
    {
        _registers.pc = 0xfffc;

        _registers.a = 0;
        _registers.x = 0;
        _registers.y = 0;
        _registers.s = 0;

        _registers.p = 0;
        _registers.reserved = 1;

    }

    // clock() is called from boards
    void cpu::clock()
    {
        _registers.pc++;
    }

    void cpu::nmi()
    {
    }

    void cpu::irq()
    {
    }

    void cpu::brk()
    {
    }
}
