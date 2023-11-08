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
            void write(address target_address, uint8_t data) override;
            uint8_t read(address target_address) override;

        private:
            io &_working_ram;
            io &_rom;
            io &_ppu;
    };
}

#endif
