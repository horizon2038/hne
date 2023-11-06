#ifndef OPCODE_NONE_HPP
#define OPCODE_NONE_HPP

#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_none final : public opcode
    {
        void execute() override;
    };
}

#endif
