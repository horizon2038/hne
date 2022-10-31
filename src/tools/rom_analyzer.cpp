#include <rom/ines_header.h>
#include <rom/rom.h>
#include "rom_analyzer.h"

#include <iostream>
#include <fstream>
#include <ios>
#include <iomanip>
#include <cstdint>
#include <cstddef>

int main(int argc, char *argv[])
{
    RomAnalyzer rom_analyzer = RomAnalyzer();
    rom_analyzer.Analyze(argv[1]);
    exit(0);
}

void RomAnalyzer::Analyze(char* filename)
{
    file = std::ifstream(filename, std::ios::binary);
    file.unsetf(std::ios::skipws); //Seems like you'd have to do some formatting.
    ReadInesHeader();
    ReadRom();
    OutAnalyzedResult();
};

void RomAnalyzer::ReadInesHeader()
{
    file.read(reinterpret_cast<char*>(&ines_header), sizeof(ines_header));
};

void RomAnalyzer::ReadRom()
{
    size_t program_rom_size = sizeof(std::byte) * ines_header.program_rom_size * 16384;
    size_t charactor_rom_size = sizeof(std::byte) * ines_header.charactor_rom_size * 8192;
    rom.program_data.assign(program_rom_size, std::byte{0});
    rom.charactor_data.assign(charactor_rom_size, std::byte{0});
    file.read(reinterpret_cast<char*>(&rom.program_data[0]), program_rom_size);
    file.read(reinterpret_cast<char*>(&rom.charactor_data[0]), charactor_rom_size);
    file.close();
};

void RomAnalyzer::OutAnalyzedResult()
{ 
    std::cout << "nes: " << ines_header.nes << std::endl;
    std::cout << "program_rom_size: " << 16384 * (int)ines_header.program_rom_size << "B" << std::endl;
    std::cout << "charactor_rom_size: " << 8192 * (int)ines_header.charactor_rom_size << "B" << std::endl;

    std::cout << "======PROGRAM SECTION======" << std::endl;
    for(int i=0; i < 16384 * (int)ines_header.program_rom_size; i++)
    {   
        std::cout << std::right << std::hex << std::uppercase << std::setfill('0');
        std::cout << std::setw(2) << std::to_integer<int>(rom.program_data[i]) << "    ";
    };
    std::cout << "======CHARACTOR SECTION======" << std::endl;
    for(int i=0; i < 8192 * (int)ines_header.charactor_rom_size; i++)
    {   
        std::cout << std::right << std::hex << std::uppercase << std::setfill('0');
        std::cout << std::setw(2) << std::to_integer<int>(rom.charactor_data[i]) << "    ";
    };
}