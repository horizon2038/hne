#ifndef CPU_HPP
#define CPU_HPP

#include <stdint.h>

#include <core/common/common.hpp>
#include <core/cpu/registers.hpp>
#include <core/cpu/opcode/opcode.hpp>
#include <core/io/io.hpp>
#include <core/cpu/adressing.hpp>

#include <memory>

namespace core
{
    constexpr static uint16_t OPCODE_COUNT_MAX = 256;
    // RP2A03
    class cpu
    {
      public:
        cpu(std::unique_ptr<io> target_bus);
        ~cpu();

        registers _registers;

        void clock();

        uint8_t fetch();
        void execute(uint8_t target_opcode);

        uint16_t fetch_operand_address(addressing_mode);
        void apply_cycles(uint8_t cycles);

        void push(uint8_t data);
        uint8_t pop();

        // interrupt
        void register_opcode(
            std::unique_ptr<opcode> target_opcode,
            uint16_t opcode_number
        );

        void reset();
        void nmi();
        void irq();
        void brk();

        // debug
        void print_registers();

      private:
        uint8_t _cycles;
        std::unique_ptr<opcode> _opcodes[OPCODE_COUNT_MAX];
        std::unique_ptr<io> _bus;

        // init
        void init_opcodes();

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
