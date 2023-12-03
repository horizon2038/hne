#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <stdint.h>

namespace core
{
    struct registers
    {
        // accumlator
        uint8_t a;

        // index register
        uint8_t x;
        uint8_t y;

        //program counter
        uint16_t pc;

        // stack pointer
        // 0x0100 + stack pointer = wram address
        uint8_t s;

        // status register
        union
        {
            uint8_t p;

            // warning
            // bit-field is processor-dependent
            struct
            {
                uint8_t negative : 1;
                uint8_t overflow : 1;
                uint8_t reserved : 1;
                uint8_t break_mode : 1;
                uint8_t decimal_mode : 1;
                uint8_t disable_irq : 1;
                uint8_t zero : 1;
                uint8_t carry : 1;
            };
        };

        void init_registers()
        {
            pc = 0;

            a = 0;
            x = 0;
            y = 0;
            s = 0;

            p = 0;
            reserved = 1;

        }
    };
}
#endif

