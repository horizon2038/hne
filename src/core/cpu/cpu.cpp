#include <core/common/common.hpp>
#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>

namespace core
{
    cpu::cpu(opcode *init_opcode, io &target_bus)
        : _registers { 0 }
        , _cycles { 0 }
        , _operand_address { 0 }
        , _bus(target_bus)
    {
    }

    cpu::~cpu()
    {
    }

    void cpu::init_opcodes(opcode *init_opcode)
    {
        for (uint16_t i = 0; i < OPCODE_COUNT_MAX; i++)
        {
            register_opcode(init_opcode, i);
        }
    }

    void cpu::register_opcode(opcode *target_opcode, uint16_t opcode_number)
    {
        if (opcode_number > (OPCODE_COUNT_MAX - 1))
        {
            return;
        }
        _opcodes[opcode_number] = target_opcode;
    }

    // clock() is called from boards
    void cpu::clock()
    {
        // TODO : consider clock cycle
        _cycles--;
        if (is_cycle_running())
        {
            return;
        }

        uint8_t opcode_number = fetch();
        execute(opcode_number);
    }

    bool cpu::is_cycle_running()
    {
        return !(_cycles <= 0);
    }

    uint8_t cpu::fetch()
    {
        return _bus.read(_registers.pc++);
    }

    void cpu::execute(uint8_t target_opcode)
    {
        _opcodes[target_opcode]->execute();
    }

    // TODO : implementation of addressing_mode)
    void cpu::apply_adressing(addressing_mode target_addressing_mode)
    {
        switch (target_addressing_mode)
        {
            case addressing_mode::IMPLIED :
                {
                    break;
                }

            case addressing_mode::ACCUMLATOR :
                {
                    _operand_address = _registers.a;
                    break;
                }

            case addressing_mode::IMMEDIATE :
                {
                    _registers.a = fetch();
                    break;
                }

            case addressing_mode::ZERO_PAGE :
                {
                    uint8_t target_address = fetch();
                    _operand_address = _bus.read(target_address);
                    return;
                }

            case addressing_mode::INDEXED_ZERO_PAGE_X :
                {
                    uint8_t target_address = fetch();
                    _operand_address = _bus.read(target_address + _registers.x);
                    break;
                }

            case addressing_mode::INDEXED_ZERO_PAGE_Y :
                {
                    uint8_t target_address = fetch();
                    _operand_address = _bus.read(fetch() + _registers.y);
                    break;
                }

            case addressing_mode::ABSOLUTE :
                {
                    uint8_t lower_target_address = fetch();
                    uint8_t higher_target_address = fetch();
                    _operand_address = merge_address(
                        lower_target_address,
                        higher_target_address
                    );
                    break;
                }

            case addressing_mode::INDEXED_ABSOLUTE_X :
                {
                    break;
                }

            case addressing_mode::INDEXED_ABSOLUTE_Y :
                {
                    break;
                }

            case addressing_mode::RELATIVE :
                {
                    break;
                }

            case addressing_mode::INDIRECT :
                {
                    break;
                }

            case addressing_mode::INDEXED_INDIRECT :
                {
                    break;
                }

            case addressing_mode::INDIRECT_INDEXED :
                {
                    break;
                }

            default :
                break;
        }
    }

    void cpu::push(uint8_t data)
    {
        _bus.write((0x0100 + _registers.s), data);
        _registers.s--;
    }

    uint8_t cpu::pop()
    {
        uint8_t fetched_data = _bus.read((0x0100 + _registers.s));
        _registers.s++;
        return fetched_data;
    }

    void cpu::reset()
    {
        _registers.disable_irq = true;
        _registers.init_registers();
        _registers.pc = fetch_interrupt_handler_address(0xfffc, 0xfffd);
        _registers.disable_irq = false;
    }

    address cpu::fetch_interrupt_handler_address(
        address lower_address,
        address higher_address
    )
    {
        uint8_t lower_interrupt_handler_address = _bus.read(lower_address);
        uint8_t higher_interrupt_handler_address = _bus.read(higher_address);
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
