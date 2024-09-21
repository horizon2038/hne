#ifndef CORE_OPCODE_ASL_HPP
#define CORE_OPCODE_ASL_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_asl final : public opcode
    {
      public:
        opcode_asl(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_asl() {};

        void execute() override
        {
            auto    fetched_address = root_cpu.fetch_operand_address(mode);
            uint8_t target_value {};

            using enum addressing_mode;
            switch (mode)
            {
                case ACCUMLATOR :
                    root_cpu.apply_cycles(2);
                    root_cpu.registers.carry = (root_cpu.registers.a >> 7) & 1;
                    target_value             = root_cpu.registers.a << 1;
                    root_cpu.registers.a     = target_value;
                    root_cpu.update_negative(target_value);
                    root_cpu.update_zero(target_value);
                    return;

                case ZERO_PAGE :
                    root_cpu.apply_cycles(6);
                    break;

                case INDEXED_ZERO_PAGE_X :
                    root_cpu.apply_cycles(7);
                    break;

                case ABSOLUTE :
                    root_cpu.apply_cycles(5);
                    break;

                case INDEXED_ABSOLUTE_X :
                    root_cpu.apply_cycles(6);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            target_value             = root_cpu.bus->read(fetched_address);
            root_cpu.registers.carry = (target_value >> 7) & 1;

            // flag
            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif