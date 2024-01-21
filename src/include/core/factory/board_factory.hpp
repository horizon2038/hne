#ifndef BOARD_FACTORY_HPP
#define BOARD_FACTORY_HPP

#include <core/board/board.hpp>

#include <memory>

namespace core
{
    class board_factory
    {
      public:
        std::unique_ptr<board> make();
    };
}

#endif
