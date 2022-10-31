#pragma once

#include <rom/ines_header.h>
#include <rom/rom.h>
#include <fstream>

class RomAnalyzer
{
    private:
        struct InesHeader ines_header;
        struct Rom rom;
        std::ifstream file;

        void ReadInesHeader();
        void ReadRom();

    public:
        void Analyze(char* filename);
        void OutAnalyzedResult();
};