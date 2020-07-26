#ifndef vm_h
#define vm_h

#include <string>
#include <array>
#include "instruction.hpp"
#include "condition.hpp"

namespace vm {

    class VirtualMachine {
    public:
        VirtualMachine(std::string hexData);
        void execute();
    private:
        //Memory is constrained to 1024 bytes
        std::array<char,1024> memory;

        //16 4 byte registers
        std::array<int, 16> registers;

        //Program holds the hex string representing the program
        std::string program;

        uint32_t programPointer;

        static Instruction::Instruction decode(char byte);
        static Condition::Condition decodeCondition(char byte);
        int16_t getShort();
        int32_t getInt();
    };
}
#endif
