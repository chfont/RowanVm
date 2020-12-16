#ifndef vm_h
#define vm_h

#include "IntermediateData/condition.hpp"
#include "IntermediateData/instruction.hpp"
#include <array>
#include <vector>
#include <string>

namespace vm {

    class VirtualMachine {
    public:
        VirtualMachine(std::string hexData, const std::map<std::string, uint64_t>&);
        void execute();
        uint64_t getMemSize(){ return memory.size();}
        uint64_t getStackSize(){ return stack.size();}
    private:
        //Memory is constrained to 1024 bytes
        std::vector<char> memory;
        std::vector<char> stack;

        //16 4 byte registers
        std::array<int, 16> registers;

        //Program holds the hex string representing the program
        std::string program;

        uint32_t programPointer;
        uint64_t stack_index;

        static instruction::Instruction decode(char byte);
        static condition::Condition decodeCondition(char byte);
        int32_t getInt();
    };
}
#endif
