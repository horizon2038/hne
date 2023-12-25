#ifndef BOARD_HPP
#define BOARD_HPP

#include <core/cpu/cpu.hpp>
#include <core/io/io.hpp>
#include <core/io/bus/bus.hpp>
#include <core/io/memory/ram.hpp>
#include <core/io/memory/rom.hpp>

namespace core
{
    class board
    {
      public:
        board();
        ~board();
        void init();
    };
}

#endif
