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

    enum class addressing_mode
    {
        impl,
        accumlator,
        immediate,
        absolute,
        zero_page,
        indexed_zero_page,
        indexed_absolute,
        relative,
        indexed_indirect,
        indirect_indexed,
        absolite_indirect
    };
}

#endif
