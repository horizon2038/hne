#ifndef BUS_HPP
#define BUS_HPP

#include <core/io/io.hpp>
#include <core/common/common.hpp>
#include <stdint.h>

namespace core
{
    class bus final : public io
    {
      public:
        bus(io &target_working_ram,
            io &target_charactor_rom,
            io &target_program_rom,
            io &target_ppu);
        void write(address target_address, uint8_t data) override;
        uint8_t read(address target_address) override;

      private:
        io &_working_ram;
        io &_charactor_rom;
        io &_program_rom;
        io &_ppu;

        io *search_io_from_address(address target_address);
        address convert_local_io_address(address target_address);
    };
}

#endif
