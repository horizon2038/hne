#include <core/cpu/cpu.hpp>

namespace core
{
    cpu::cpu(io &target_bus)
        : _registers{}
        , _bus(target_bus)
    {
    }

    cpu::~cpu()
    {
    }

    void cpu::reset()
    {
        _registers.init_registers();
        _registers.pc = fetch_interrupt_handler_address(0xfffc, 0xfffd);
    }

    address cpu::fetch_interrupt_handler_address(address lower_address, address higher_address)
    {
        uint8_t lower_interrupt_handler_address = fetch(0xfffc);
        uint8_t higher_interrupt_handler_address = fetch(0xfffd);
        address interrupt_handler_address = merge_address(lower_interrupt_handler_address, higher_interrupt_handler_address);
        return interrupt_handler_address;
    }

    uint8_t cpu::fetch(address target_address)
    {
        return _bus.read(target_address);
    }

    address cpu::merge_address(uint8_t lower_address, uint8_t higher_address)
    {
        return lower_address | (higher_address << 8);
    }

    // clock() is called from boards
    void cpu::clock()
    {
        _registers.pc++;
        uint8_t opcode_number = fetch(_registers.pc);
        execute(opcode_number);
        
    }

    void cpu::execute(uint8_t target_opcode)
    {
        opcodes[target_opcode]->execute();
    }

    void cpu::nmi()
    {
        _registers.pc = fetch_interrupt_handler_address(0xfffa, 0xfffb);
    }

    void cpu::irq()
    {
        _registers.pc = fetch_interrupt_handler_address(0xfffe, 0xffff);
    }

    void cpu::brk()
    {
        _registers.pc = fetch_interrupt_handler_address(0xfffe, 0xffff);
    }
}
