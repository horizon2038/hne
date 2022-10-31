#pragma once
#include <rom/ines_header.h>
#include <vector>
#include <cstdint>

struct Rom
{
    struct InesHeader ines_header;
    std::vector<std::byte> program_data;
    std::vector<std::byte> charactor_data;
};