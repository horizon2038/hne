#include <core/common/common.hpp>
#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <memory>

#include <core/cpu/opcode/opcode_none.hpp>

#include <stdio.h>

namespace core
{
    cpu::cpu(std::unique_ptr<io> target_bus)
        : registers {}
        , bus { std::move(target_bus) }
        , cycles { 6 } // initial cycles (6 : default)
    {
        init_opcodes();
    }

    cpu::~cpu()
    {
    }

    void cpu::init_opcodes()
    {
        for (uint16_t i = 0; i < OPCODE_COUNT_MAX; i++)
        {
            register_opcode(std::make_unique<opcode_none>(*this), i);
        }
    }

    void cpu::register_opcode(
        std::unique_ptr<opcode> target_opcode,
        uint16_t                opcode_number
    )
    {
        if (opcode_number > (OPCODE_COUNT_MAX - 1))
        {
            return;
        }
        opcodes[opcode_number] = std::move(target_opcode);
    }

    // clock() is called from boards
    void cpu::clock()
    {
        printf("current pc : 0x%04x\n", this->registers.pc);
        cycles--;
        // printf("cycles : %8d\n", cycles);
        if (is_cycle_running())
        {
            return;
        }

        uint8_t opcode_number = fetch();
        printf("opcode : 0x%02x\n", opcode_number);
        execute(opcode_number);
    }

    bool cpu::is_cycle_running()
    {
        return (cycles > 0);
    }

    uint8_t cpu::fetch()
    {
        return bus->read(registers.pc++);
    }

    void cpu::execute(uint8_t target_opcode)
    {
        opcodes[target_opcode]->execute();
    }

    uint16_t cpu::fetch_operand_address(addressing_mode target_addressing_mode)
    {
        switch (target_addressing_mode)
        {
            case addressing_mode::IMPLIED :
                {
                    return 0;
                }

            case addressing_mode::ACCUMLATOR :
                {
                    return 0;
                }

            case addressing_mode::IMMEDIATE :
                {
                    // exception : return "data", not address
                    return fetch();
                }

            case addressing_mode::ZERO_PAGE :
                {
                    auto target_address = fetch();
                    return target_address & 0xFF;
                }

            case addressing_mode::INDEXED_ZERO_PAGE_X :
                {
                    auto target_address = fetch() + registers.x;
                    return target_address & 0xFF;
                }

            case addressing_mode::INDEXED_ZERO_PAGE_Y :
                {
                    auto target_address = fetch() + registers.y;
                    return target_address & 0xFF;
                }

            case addressing_mode::ABSOLUTE :
                {
                    auto lower_target_address  = fetch();
                    auto higher_target_address = fetch();
                    auto target_address        = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    return target_address & 0xFFFF;
                }

            case addressing_mode::INDEXED_ABSOLUTE_X :
                {
                    auto lower_target_address  = fetch();
                    auto higher_target_address = fetch();
                    auto base_address          = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    auto target_address = base_address + registers.x;

                    // if page boundaries are to be crossed,
                    // a cycle must be added.
                    if ((base_address & 0xFF00) != (target_address & 0xFF00))
                    {
                        apply_cycles(1);
                    }

                    return target_address;
                }

            case addressing_mode::INDEXED_ABSOLUTE_Y :
                {
                    auto lower_target_address  = fetch();
                    auto higher_target_address = fetch();
                    auto base_address          = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    auto target_address = base_address + registers.y;

                    // if page boundaries are to be crossed,
                    // a cycle must be added.
                    if ((base_address & 0xFF00) != (target_address & 0xFF00))
                    {
                        apply_cycles(1);
                    }

                    return target_address;
                }

            case addressing_mode::RELATIVE :
                {
                    int8_t  offset = static_cast<int8_t>(fetch());
                    int16_t target_address
                        = registers.pc + static_cast<int16_t>(registers.pc)
                        + static_cast<int16_t>(offset);
                    return target_address & 0xFFFF;
                }

            case addressing_mode::INDIRECT :
                {
                    auto lower_address  = fetch();
                    auto higher_address = fetch();
                    auto pre_target_address
                        = merge_address(lower_address, higher_address);
                    auto lower_target_address = bus->read(pre_target_address);
                    auto higher_target_address = bus->read(pre_target_address + 1);
                    auto target_address = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    return target_address & 0xFFFF;
                }

                // TODO: add zero-page loop & page crossing
            case addressing_mode::INDEXED_INDIRECT :
                {
                    uint8_t base = fetch();
                    // zero-page loop
                    uint16_t pre_target_address = (base + registers.x) & 0xFF;
                    uint8_t  final_low          = bus->read(pre_target_address);
                    // zero-page loop
                    uint8_t final_high = bus->read((pre_target_address + 1) & 0xFF);
                    auto target_address = merge_address(final_low, final_high);

                    return target_address;
                }

                // TODO: add zero-page loop & page crossing
            case addressing_mode::INDIRECT_INDEXED :
                {
                    uint8_t base = fetch();
                    // zero-page loop
                    uint16_t pre_target_address = merge_address(
                        bus->read(base),
                        bus->read((base + 1) & 0xFF)
                    );
                    auto target_address = pre_target_address + registers.y;

                    if ((pre_target_address & 0xFF00) != (target_address & 0xFF00))
                    {
                        apply_cycles(1);
                    }

                    return target_address;
                }

            default :
                break;
        }
    }

    void cpu::apply_cycles(uint8_t cycles)
    {
        this->cycles = cycles;
    }

    void cpu::update_negative(uint8_t target_register)
    {
        // bit 7 : *sign* bit
        registers.negative = (target_register >> 7) & 1;
    }

    void cpu::update_zero(uint8_t target_register)
    {
        registers.zero = (target_register == 0);
    }

    void cpu::push(uint8_t data)
    {
        bus->write((0x0100 + registers.s), data);
        registers.s--;
    }

    uint8_t cpu::pop()
    {
        uint8_t fetched_data = bus->read((0x0100 + registers.s));
        registers.s++;
        return fetched_data;
    }

    void cpu::reset()
    {
        registers.disable_irq = true;
        registers.init_registers();
        registers.pc = fetch_interrupt_handler_address(0xfffc, 0xfffd);
        // registers.pc = 0x8000;
        printf("interrpt_handler_address : 0x%04x\n", this->registers.pc);
        registers.disable_irq = false;
    }

    address cpu::fetch_interrupt_handler_address(
        address lower_address,
        address higher_address
    )
    {
        uint8_t lower_interrupt_handler_address  = bus->read(lower_address);
        uint8_t higher_interrupt_handler_address = bus->read(higher_address);
        address interrupt_handler_address        = merge_address(
            lower_interrupt_handler_address,
            higher_interrupt_handler_address
        );
        return interrupt_handler_address;
    }

    void cpu::nmi()
    {
        registers.disable_irq = true;
        registers.break_mode  = false;
        save_interrupt_frame();
        registers.pc          = fetch_interrupt_handler_address(0xfffa, 0xfffb);
        registers.disable_irq = false;
    }

    void cpu::save_interrupt_frame()
    {
        // masking and set bit-conversion.
        uint8_t lower_program_counter  = (registers.pc >> 0) & 0xFF;
        uint8_t higher_program_counter = (registers.pc >> 8) & 0xFF;

        push(higher_program_counter);
        push(lower_program_counter);
        push(registers.p);
    }

    void cpu::irq()
    {
        if (registers.disable_irq)
        {
            return;
        }
        registers.disable_irq = true;
        registers.break_mode  = false;
        save_interrupt_frame();
        registers.pc          = fetch_interrupt_handler_address(0xfffe, 0xffff);
        registers.disable_irq = false;
    }

    void cpu::brk()
    {
        if (registers.disable_irq)
        {
            return;
        }
        registers.disable_irq = true;
        registers.break_mode  = true;
        save_interrupt_frame();
        registers.pc          = fetch_interrupt_handler_address(0xfffe, 0xffff);
        registers.disable_irq = false;
    }
}
