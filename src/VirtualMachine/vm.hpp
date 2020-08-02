#ifndef vm_h
#define vm_h

#include "IntermediateData/condition.hpp"
#include "IntermediateData/instruction.hpp"
#include <array>
#include <string>

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

        static instruction::Instruction decode(char byte);
        static condition::Condition decodeCondition(char byte);
        int32_t getInt();
    };
}
#endif
