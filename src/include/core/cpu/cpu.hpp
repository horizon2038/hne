#ifndef CPU_HPP
#define CPU_HPP

#include <stdint.h>

#include <core/common/common.hpp>
#include <core/cpu/registers.hpp>
#include <core/cpu/opcode/opcode.hpp>
#include <core/io/io.hpp>

namespace core
{
    // RP2A03
    class cpu
    {
        public:
            cpu(io &taregt_bus);
            ~cpu();

            registers _registers;

            void clock();

            // interrupt
            void reset();
            void nmi();
            void irq();
            void brk();

            // debug
            void print_registers();

        private:
            opcode *opcodes[256];
            io &_bus;

            uint16_t fetch_interrupt_handler_address(address lower_address, address higher_address);
            uint8_t fetch(address target_address);
            address merge_address(uint8_t lower_address, uint8_t higher_address);
            void execute(uint8_t target_opcode);

    };
}

#endif
