#include <core/io/io.hpp>

#include <core/cpu/opcode/opcode.hpp>
#include <core/cpu/opcode/opcode_none.hpp>

#include <core/cpu/cpu.hpp>
#include <core/io/io.hpp>
#include <core/io/io_stab.hpp>
#include <core/io/bus/bus.hpp>
#include <core/io/memory/ram.hpp>
#include <core/io/memory/rom.hpp>
#include <memory>
#include <unistd.h>

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
    cpu->reset();
    for (auto i = 0; i < 1000; i++)
    {
        cpu->clock();
        usleep(100000);
    }
}
