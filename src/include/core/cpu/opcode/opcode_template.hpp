#ifndef OPCODE_XXX
#define OPCODE_XXX

#include <__filesystem/perm_options.h>
#include <core/cpu/opcode/opcode.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/adressing.hpp>

namespace core
{
    class opcode_xxx final : public opcode
    {
      public:
        opcode_xxx(addressing_mode init_addressing_mode, cpu &target_cpu);
        ~opcode_xxx() {};

        void execute() override;

      private:
        addressing_mode _addressing_mode;
        cpu &_cpu;
        uint8_t _cycles;
    };
}

#endif
