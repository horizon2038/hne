#include <core/cpu/cpu.hpp>

namespace core
{
    cpu::cpu(io &target_bus)
        : _registers{}
        , _cycles{0}
        , _bus(target_bus)
    {
    }

    cpu::~cpu()
    {
    }

    // clock() is called from boards
    void cpu::clock()
    {
        // TODO : consider clock cycle
        _cycles--;
        if (!is_cycle_finished())
        {
            return;
        }

        _registers.pc++;
        uint8_t opcode_number = fetch(_registers.pc);
        execute(opcode_number);
    }

    bool cpu::is_cycle_finished()
    {
        return (_cycles <= 0);
    }

    uint8_t cpu::fetch(address target_address)
    {
        return _bus.read(target_address);
    }

    void cpu::execute(uint8_t target_opcode)
    {
        _opcodes[target_opcode]->execute();
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

    address cpu::fetch_interrupt_handler_address(address lower_address, address higher_address)
    {
        uint8_t lower_interrupt_handler_address = fetch(lower_address);
        uint8_t higher_interrupt_handler_address = fetch(higher_address);
        address interrupt_handler_address = merge_address(lower_interrupt_handler_address, higher_interrupt_handler_address);
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
        push(_registers.pc);
        push(_registers.s);
    }

    void cpu::irq()
    {
        _registers.disable_irq = true;
        _registers.break_mode = false;
        if (_registers.disable_irq)
        {
            return;
        }
        save_interrupt_frame();
        _registers.pc = fetch_interrupt_handler_address(0xfffe, 0xffff);
        _registers.disable_irq = false;
    }

    void cpu::brk()
    {
        _registers.disable_irq = true;
        _registers.break_mode = true;
        if (_registers.disable_irq)
        {
            return;
        }
        save_interrupt_frame();
        _registers.pc = fetch_interrupt_handler_address(0xfffe, 0xffff);
        _registers.disable_irq = false;
    }
}
