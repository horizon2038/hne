#include <core/io/memory/rom.hpp>

#include <cstddef>
#include <fstream>
#include <memory>
#include <utility>

namespace core
{
    primitive_rom::primitive_rom(
        std::unique_ptr<std::vector<uint8_t>> target_rom_data
    )
        : rom_data(std::move(target_rom_data))
    {
    }

    uint8_t primitive_rom::read(address target_address)
    {
        return rom_data->data()[target_address];
    }

    // "Read Only"
    void primitive_rom::write(address target_address, uint8_t data) {};

    rom::rom(const char *file_path)
    {
        auto rom_binary = open_rom_file(file_path);
        this->header = read_ines_header(rom_binary);
        setup_rom(rom_binary);
    }

    std::ifstream rom::open_rom_file(const char *path)
    {
        std::ifstream file(path, std::ios::binary);
        return std::move(file);
    }

    ines_header rom::read_ines_header(std::ifstream &file)
    {
        ines_header header;
        file.read(reinterpret_cast<char *>(&header), sizeof(ines_header));
        return header;
    }

    void rom::setup_rom(std::ifstream &file)
    {
        auto program_rom_offset = sizeof(ines_header);
        program_rom_offset += this->header.trainer_exists ? 0 : 512;

        auto program_rom_size = 16384 * this->header.program_rom_count;

        auto charactor_rom_offset = program_rom_offset + program_rom_size;
        auto charactor_rom_size = 8192 * this->header.charactor_rom_count;

        auto program_rom_data = create_vector_from_file(
            file,
            program_rom_offset,
            program_rom_size
        );

        auto charactor_rom_data = create_vector_from_file(
            file,
            charactor_rom_offset,
            charactor_rom_size
        );

        this->program
            = std::make_unique<primitive_rom>(std::move(program_rom_data));

        this->charactor
            = std::make_unique<primitive_rom>(std::move(charactor_rom_data));
    }

    void create_program_rom(std::ifstream &file)
    {
    }

    std::unique_ptr<std::vector<uint8_t>> rom::create_vector_from_file(
        std::ifstream &file,
        std::streamoff offset,
        size_t size
    )
    {
        auto data = std::make_unique<std::vector<uint8_t>>(size);

        file.seekg(offset, std::ios::beg);
        file.read(reinterpret_cast<char *>(data->data()), size);

        return data;
    }
}
