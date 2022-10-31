#include <cstdint>

class CPU
{
    uint8_t a; //accumulator
    uint8_t x; //index
    uint8_t y; //index
    uint8_t s; //stack
    uint8_t p; //status
    uint16_t pc; //program counter

    public:
        CPU();
        void Fetch();
 
};