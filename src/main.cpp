#include "core/cpu/adressing.hpp"
#include <core/io/io.hpp>

#include <core/cpu/opcode/opcode.hpp>
#include <core/cpu/opcode/opcode_none.hpp>

#include <core/cpu/cpu.hpp>
#include <core/io/bus/bus.hpp>
#include <core/io/io.hpp>
#include <core/io/io_stab.hpp>
#include <core/io/memory/ram.hpp>
#include <core/io/memory/rom.hpp>
#include <memory>
#include <unistd.h>

// opcodes
#include <core/cpu/opcode/opcode_lda.hpp>
#include <core/cpu/opcode/opcode_ldx.hpp>
#include <core/cpu/opcode/opcode_ldy.hpp>

#include <core/cpu/opcode/opcode_sta.hpp>
#include <core/cpu/opcode/opcode_stx.hpp>
#include <core/cpu/opcode/opcode_sty.hpp>

#include <core/cpu/opcode/opcode_tax.hpp>
#include <core/cpu/opcode/opcode_tay.hpp>

#include <core/cpu/opcode/opcode_tsx.hpp>
#include <core/cpu/opcode/opcode_txa.hpp>
#include <core/cpu/opcode/opcode_txs.hpp>
#include <core/cpu/opcode/opcode_tya.hpp>

#include <core/cpu/opcode/opcode_brk.hpp>
#include <core/cpu/opcode/opcode_nop.hpp>

void init_opcodes(core::cpu &target_cpu)
{
    using enum core::addressing_mode;

    // LDA
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(IMMEDIATE, target_cpu),
        0xA9
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(ZERO_PAGE, target_cpu),
        0xA5
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xB5
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(ABSOLUTE, target_cpu),
        0xAD
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDEXED_ABSOLUTE_X, target_cpu),
        0xBD
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xB9
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDEXED_INDIRECT, target_cpu),
        0xA1
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDIRECT_INDEXED, target_cpu),
        0xB1
    );

    // LDX
    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(IMMEDIATE, target_cpu),
        0xA2
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(ZERO_PAGE, target_cpu),
        0xA6
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(INDEXED_ZERO_PAGE_Y, target_cpu),
        0xB6
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(ABSOLUTE, target_cpu),
        0xAE
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xBE
    );

    // LDY
    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(IMMEDIATE, target_cpu),
        0xA0
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(ZERO_PAGE, target_cpu),
        0xA4
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xB4
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(ABSOLUTE, target_cpu),
        0xAC
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(INDEXED_ABSOLUTE_X, target_cpu),
        0xBC
    );

    // STA
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(ZERO_PAGE, target_cpu),
        0x85
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x95
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(ABSOLUTE, target_cpu),
        0x8D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDEXED_ABSOLUTE_X, target_cpu),
        0x9D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x99
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDEXED_INDIRECT, target_cpu),
        0x81
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDIRECT_INDEXED, target_cpu),
        0x91
    );

    // STX
    target_cpu.register_opcode(
        std::make_unique<core::opcode_stx>(ZERO_PAGE, target_cpu),
        0x86
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_stx>(INDEXED_ZERO_PAGE_Y, target_cpu),
        0x96
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_stx>(ABSOLUTE, target_cpu),
        0x8E
    );

    // STY
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sty>(ZERO_PAGE, target_cpu),
        0x84
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sty>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x94
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sty>(ABSOLUTE, target_cpu),
        0x8C
    );

    // TAX
    target_cpu.register_opcode(std::make_unique<core::opcode_tax>(target_cpu), 0xAA);

    // TAY
    target_cpu.register_opcode(std::make_unique<core::opcode_tay>(target_cpu), 0xA8);

    // TSX
    target_cpu.register_opcode(std::make_unique<core::opcode_tsx>(target_cpu), 0xBA);

    // TXA
    target_cpu.register_opcode(std::make_unique<core::opcode_txa>(target_cpu), 0x8A);

    // TXS
    target_cpu.register_opcode(std::make_unique<core::opcode_txs>(target_cpu), 0x9A);

    // TYA
    target_cpu.register_opcode(std::make_unique<core::opcode_tya>(target_cpu), 0x98);

    // BRK
    target_cpu.register_opcode(std::make_unique<core::opcode_brk>(target_cpu), 0x00);

    // NOP
    target_cpu.register_opcode(std::make_unique<core::opcode_nop>(target_cpu), 0xEA);
}

int main(int argc, char *argv[])
{
    auto ram = std::make_unique<core::working_ram>();
    auto rom = std::make_unique<core::rom>(argv[1]);
    auto ppu = std::make_unique<core::io_stab>();
    auto bus = std::make_unique<core::bus>(
        std::move(ram),
        std::move(rom->charactor),
        std::move(rom->program),
        std::move(ppu)
    );

    auto cpu = std::make_unique<core::cpu>(std::move(bus));
    init_opcodes(*cpu.get());

    cpu->reset();
    for (;;)
    {
        cpu->clock();
        usleep(10000);
    }
}
