#ifndef CORE_OPCODE_TSX_HPP
#define CORE_OPCODE_TSX_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_tsx final : public opcode
    {
      public:
        opcode_tsx(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_tsx() {};

        void execute() override
        {
            root_cpu.apply_cycles(2);

            uint8_t target_value = root_cpu.registers.s;
            root_cpu.registers.x = target_value;

            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
