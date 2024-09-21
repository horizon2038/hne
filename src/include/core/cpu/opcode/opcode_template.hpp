#ifndef CORE_OPCODE_XXX_HPP
#define CORE_OPCODE_XXX_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_xxx final : public opcode
    {
      public:
        opcode_xxx(addressing_mode init_addressing_mode, cpu &target_cpu);
        ~opcode_xxx() {};

        void execute() override;

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
