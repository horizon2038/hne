#ifndef IO_STAB_HPP
#define IO_STAB_HPP

#include <core/io/io.hpp>

namespace core
{
    class io_stab : public io
    {
      public:
        virtual ~io_stab() {};

        uint8_t read(address target_address) override
        {
            return 0;
        }

        void write(address target_address, uint8_t data) override
        {
        }
    };
}
#endif
