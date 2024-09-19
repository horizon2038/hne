#ifndef CORE_OPCODE_TAY_HPP
#define CORE_OPCODE_TAY_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_tay final : public opcode
    {
      public:
        opcode_tay(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_tay() {};

        void execute() override
        {
            root_cpu.apply_cycles(2);

            uint8_t target_value = root_cpu.registers.a;
            root_cpu.registers.y = target_value;

            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
