#ifndef CORE_OPCODE_BRK_HPP
#define CORE_OPCODE_BRK_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>
#include <iostream>

namespace core
{
    class opcode_brk final : public opcode
    {
      public:
        opcode_brk(cpu &target_cpu) : root_cpu { target_cpu }
        {
        }

        ~opcode_brk() {};

        void execute() override
        {
            root_cpu.apply_cycles(7);
            root_cpu.brk();
        }

      private:
        cpu &root_cpu;
    };
}

#endif
