#ifndef OPCODE_HPP
#define OPCODE_HPP

namespace core
{
    // common opcode interface
    class opcode
    {
        public:
            virtual void execute() = 0;
    };
}

#endif
