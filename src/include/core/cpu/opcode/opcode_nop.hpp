#ifndef CORE_OPCODE_NOP_HPP
#define CORE_OPCODE_NOP_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_nop final : public opcode
    {
      public:
        opcode_nop(cpu &target_cpu) : root_cpu { target_cpu }
        {
        }

        ~opcode_nop() {};

        void execute() override
        {
            root_cpu.apply_cycles(2);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
