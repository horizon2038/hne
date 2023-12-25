#ifndef IO_STAB_HPP
#define IO_STAB_HPP

#include <core/io/io.hpp>

namespace core
{
    class io_stab : public io
    {
      public:
        uint8_t read(address target_address)
        {
            return 0;
        }

        void write(address target_address)
        {
        }
    };
}
#endif
