#ifndef ADRESSING_HPP
#define ADRESSING_HPP

namespace core
{
    enum class addressing_mode
    {
        IMPLIED,
        ACCUMLATOR,
        IMMEDIATE,
        ZERO_PAGE,
        INDEXED_ZERO_PAGE_X,
        INDEXED_ZERO_PAGE_Y,
        ABSOLUTE,
        // additional cycles (page crossing)
        INDEXED_ABSOLUTE_X,
        // additional cycles (page crossing)
        INDEXED_ABSOLUTE_Y,
        RELATIVE,
        INDIRECT,
        INDEXED_INDIRECT, // X
        // additional cycles (page crossing)
        INDIRECT_INDEXED, // Y
    };
}
#endif
