#include <core/io/io.hpp>

#include <core/cpu/opcode/opcode.hpp>
#include <core/cpu/opcode/opcode_none.hpp>

#include <core/cpu/cpu.hpp>
#include <core/io/memory/rom.hpp>

int main(int argc, char *argv[])
{
    core::rom rom { argv[1] };
}
