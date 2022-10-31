#include <stdio.h>
#include "ines_header.h"

void analyze_rom(const char *rom)
{
        FILE *fp;
        struct ines_header ines_header;

        fp = fopen(rom, "rb");
                
        if(fp == NULL)
        {
                printf("can't open file.");
        }

        fread(&ines_header, sizeof(ines_header), 1, fp);

        printf("NES: %s\n", ines_header.nes);
        printf("Program Size: %d KB\n", (int)ines_header.program_rom_size * 16);
        printf("Charactor Size: %d KB\n", (int)ines_header.charactor_rom_size * 8);
        
        fclose(fp);
}

int main(int argc, char *argv[])
{
        analyze_rom(argv[1]);
        return 0;
}
