#ifndef CPU_HPP
#define CPU_HPP

#include <stdint.h>

#include <core/cpu/registers.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    // RP2A03
    class cpu
    {
        public:
            cpu();
            ~cpu();

            registers _registers;

            void clock();

            // interrupt
            void reset();
            void nmi();
            void irq();
            void brk();

        private:
            opcode *opcodes[256];

            uint8_t fetch();
            void execute(uint8_t target_opcode);

    };
}

#endif
