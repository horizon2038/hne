#include <core/io/bus/bus.hpp>

namespace core
{
    // nes memory_map
    //
    // +--------------------------------+
    // | address |   size |       about |
    // +--------------------------------+
    // |  0x0000 | 0x0800 |        wram |
    // +--------------------------------+
    // |  0x0800 | 0x0800 | wram_mirror |
    // +--------------------------------+
    // |  0x2000 | 0x0008 |         ppu |
    // +--------------------------------+
    // |  0x2008 | 0x0008 |  ppu_mirror |
    // +--------------------------------+
    // |  0x4000 | 0x0018 |    i/o regs |
    // +--------------------------------+
    // |  0x4018 | 0x0020 |   test mode |
    // +--------------------------------+
    // |  0x4020 | 0x1fe0 |     ext-ram |
    // +--------------------------------+
    // |  0x6000 | 0x2000 |     ext-ram |
    // +--------------------------------+
    // |  0x8000 | 0x4000 | program-rom |
    // +--------------------------------+
    // |  0xc000 | 0x4000 | program-rom |
    // +--------------------------------+

    void bus::write(address target_address, uint8_t data)
    {
        if (target_address < 0x0800)
        {
            // wram
        }

        if (0x0800 <= target_address && target_address < 0x1000)
        {
            // mirror of wram
        }

        if (0x2000 <= target_address && target_address < 0x2008)
        {
            // ppu registers
        }

        if (0x2008 <= target_address && target_address < 0x2010)
        {
            // mirror of ppu registers
        }

        if (0x4000 <= target_address && target_address < 0x4018)
        {
            // memory-mapped i/o (without apu)
        }

        if (0x4018 <= target_address && target_address < 0x4020)
        {
            // test mode
        }

        if (0x4020 <= target_address && target_address < 0x6000)
        {
            // extended ram
        }

        if (0x6000 <= target_address && target_address < 0x8000)
        {
            // extended ram
        }

        if (0x8000 <= target_address && target_address < 0xc000)
        {
            // program rom lower-half
        }

        if (0xc000 <= target_address && target_address <= 0xFFFF)
        {
            // program rom higher-half
        }
    }

    uint8_t bus::read(address target_address)
    {
    }
}
