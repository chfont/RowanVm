#ifndef instr_h
#define instr_h

namespace instruction {
enum class Instruction {
    ADD,
    SUB,
    MULT,
    DIV,
    CJUMP,
    LOAD,
    LOADCONST,
    STORE,
    PRINT,
    PRINTB, //Boolean Print
    NOP,
    BAD //Illegal sequence

  };
}

#endif
