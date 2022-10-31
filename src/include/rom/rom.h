#pragma once

#include <vector>
#include <cstdint>

struct Rom
{
    std::vector<std::byte> program_data;
    std::vector<std::byte> charactor_data;
};