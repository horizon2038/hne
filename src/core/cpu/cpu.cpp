#include <core/common/common.hpp>
#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <memory>

#include <core/cpu/opcode/opcode_none.hpp>

#include <stdio.h>

namespace core
{
    cpu::cpu(std::unique_ptr<io> target_bus)
        : _registers {}
        , _cycles { 6 } // initial cycles (6 : default)
        , _bus { std::move(target_bus) }
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
            _opcodes[i] = std::make_unique<opcode_none>(*this);
        }
    }

    void cpu::register_opcode(
        std::unique_ptr<opcode> target_opcode,
        uint16_t opcode_number
    )
    {
        if (opcode_number > (OPCODE_COUNT_MAX - 1))
        {
            return;
        }
        _opcodes[opcode_number] = std::move(target_opcode);
    }

    // clock() is called from boards
    void cpu::clock()
    {
        printf("current pc : 0x%04x\n", this->_registers.pc);
        _cycles--;
        printf("cycles : %8d\n", _cycles);
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
        return (_cycles > 0);
    }

    uint8_t cpu::fetch()
    {
        return _bus->read(_registers.pc++);
    }

    void cpu::execute(uint8_t target_opcode)
    {
        _opcodes[target_opcode]->execute();
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
                    auto target_address = fetch() + _registers.x;
                    return target_address & 0xFF;
                }

            case addressing_mode::INDEXED_ZERO_PAGE_Y :
                {
                    auto target_address = fetch() + _registers.y;
                    return target_address & 0xFF;
                }

            case addressing_mode::ABSOLUTE :
                {
                    auto lower_target_address = fetch();
                    auto higher_target_address = fetch();
                    auto target_address = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    return target_address & 0xFFFF;
                }

            case addressing_mode::INDEXED_ABSOLUTE_X :
                {
                    auto lower_target_address = fetch();
                    auto higher_target_address = fetch();
                    auto target_address = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    return (target_address + _registers.x) & 0xFFFF;
                }

            case addressing_mode::INDEXED_ABSOLUTE_Y :
                {
                    auto lower_target_address = fetch();
                    auto higher_target_address = fetch();
                    auto target_address = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    return (target_address + _registers.y) & 0xFFFF;
                }

            case addressing_mode::RELATIVE :
                {
                    auto target_address
                        = _registers.pc + static_cast<int8_t>(fetch());
                    return target_address & 0xFF;
                }

            case addressing_mode::INDIRECT :
                {
                    auto lower_address = fetch();
                    auto higher_address = fetch();
                    auto pre_target_address
                        = merge_address(lower_address, higher_address);
                    auto lower_target_address = _bus->read(pre_target_address);
                    auto higher_target_address
                        = _bus->read(pre_target_address + 1);
                    auto target_address = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    return target_address & 0xFFFF;
                }

            case addressing_mode::INDEXED_INDIRECT :
                {
                    auto pre_target_address = fetch() + _registers.x;
                    pre_target_address &= 0xFF;
                    auto lower_target_address = _bus->read(pre_target_address);
                    auto higher_target_address
                        = _bus->read(pre_target_address + 1);
                    auto target_address = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    return target_address & 0xFFFF;
                }

            case addressing_mode::INDIRECT_INDEXED :
                {
                    auto pre_target_address = fetch();
                    auto lower_target_address = _bus->read(pre_target_address);
                    auto higher_target_address
                        = _bus->read(pre_target_address + 1);
                    auto target_address = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    auto operand = _bus->read(target_address + _registers.y);
                    return operand & 0xFFFF;
                }

            default :
                break;
        }
    }

    void cpu::apply_cycles(uint8_t cycles)
    {
        this->_cycles = cycles;
    }

    void cpu::push(uint8_t data)
    {
        _bus->write((0x0100 + _registers.s), data);
        _registers.s--;
    }

    uint8_t cpu::pop()
    {
        uint8_t fetched_data = _bus->read((0x0100 + _registers.s));
        _registers.s++;
        return fetched_data;
    }

    void cpu::reset()
    {
        _registers.disable_irq = true;
        _registers.init_registers();
        _registers.pc = fetch_interrupt_handler_address(0xfffc, 0xfffd);
        // _registers.pc = 0x8000;
        printf("interrpt_handler_address : 0x%04x\n", this->_registers.pc);
        _registers.disable_irq = false;
    }

    address cpu::fetch_interrupt_handler_address(
        address lower_address,
        address higher_address
    )
    {
        uint8_t lower_interrupt_handler_address = _bus->read(lower_address);
        uint8_t higher_interrupt_handler_address = _bus->read(higher_address);
        address interrupt_handler_address = merge_address(
            lower_interrupt_handler_address,
            higher_interrupt_handler_address
        );
        return interrupt_handler_address;
    }

    void cpu::nmi()
    {
        _registers.disable_irq = true;
        _registers.break_mode = false;
        save_interrupt_frame();
        _registers.pc = fetch_interrupt_handler_address(0xfffa, 0xfffb);
        _registers.disable_irq = false;
    }

    void cpu::save_interrupt_frame()
    {
        // masking and set bit-conversion.
        uint8_t lower_program_counter = (_registers.pc >> 0) & 0xFF;
        uint8_t higher_program_counter = (_registers.pc >> 8) & 0xFF;

        push(higher_program_counter);
        push(lower_program_counter);
        push(_registers.p);
    }

    void cpu::irq()
    {
        if (_registers.disable_irq)
        {
            return;
        }
        _registers.disable_irq = true;
        _registers.break_mode = false;
        save_interrupt_frame();
        _registers.pc = fetch_interrupt_handler_address(0xfffe, 0xffff);
        _registers.disable_irq = false;
    }

    void cpu::brk()
    {
        if (_registers.disable_irq)
        {
            return;
        }
        _registers.disable_irq = true;
        _registers.break_mode = true;
        save_interrupt_frame();
        _registers.pc = fetch_interrupt_handler_address(0xfffe, 0xffff);
        _registers.disable_irq = false;
    }
}
