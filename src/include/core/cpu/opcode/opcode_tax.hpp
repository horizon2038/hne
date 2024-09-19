#ifndef CORE_OPCODE_TAX_HPP
#define CORE_OPCODE_TAX_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_tax final : public opcode
    {
      public:
        opcode_tax(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_tax() {};

        void execute() override
        {
            root_cpu.apply_cycles(2);

            uint8_t target_value = root_cpu.registers.a;
            root_cpu.registers.x = target_value;

            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
