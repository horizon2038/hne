#ifndef CPU_HPP
#define CPU_HPP

#include <stdint.h>

#include <core/common/common.hpp>
#include <core/cpu/registers.hpp>
#include <core/cpu/opcode/opcode.hpp>
#include <core/io/io.hpp>
#include <core/cpu/adressing.hpp>

namespace core
{
    constexpr static uint16_t OPCODE_COUNT_MAX = 256;
    // RP2A03
    class cpu
    {
      public:
        cpu(opcode *init_opcode, io &taregt_bus);
        ~cpu();

        registers _registers;
        address _operand_address;

        void clock();

        uint8_t fetch();
        void execute(uint8_t target_opcode);

        void apply_adressing(addressing_mode);

        void push(uint8_t data);
        uint8_t pop();

        // interrupt
        void register_opcode(opcode *target_opcode, uint16_t opcode_number);

        void reset();
        void nmi();
        void irq();
        void brk();

        // debug
        void print_registers();

      private:
        uint8_t _cycles;
        opcode *_opcodes[OPCODE_COUNT_MAX];
        io &_bus;

        // init
        void init_opcodes(opcode *init_opcode);

        bool is_cycle_running();

        uint16_t fetch_interrupt_handler_address(
            address lower_address,
            address higher_address
        );
        void save_interrupt_frame();
        void restore_interrupt_frame() {};
    };
}

#endif
