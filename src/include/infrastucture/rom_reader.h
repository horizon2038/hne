#pragma once
#include <rom/ines_header.h>
#include <rom/rom.h>

#include <vector>

class RomReader
{
    public:
        virtual struct Rom ReadRom(char* filename) = 0;
};