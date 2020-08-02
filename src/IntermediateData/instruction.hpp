#ifndef instr_h
#define instr_h

namespace instruction {
enum class Instruction {
    ADD = 0,
    SUB = 1,
    MULT = 2,
    DIV = 3,
    CJUMP = 4,
    LOAD = 5,
    STORE = 6,
    PRINT = 7,
    PRINTB = 8, //Boolean Print
    NOP =9,
    LOADCONST = 10,
    BAD //Illegal sequence

  };
}

#endif
