#ifndef opcode_data_h
#define opcode_data_h

#include <map>
#include <string>

#include "instruction.hpp"

namespace opcodeData {

  enum class OpcodeType {
    TWO_REG,
    REG_NUM,
    NOP,
    CONDITIONAL,
    ONE_REG,
    JUMP,
    NO_REG
  };

  struct OpcodeData{
    OpcodeType type;
    char encoding;
  };

  const std::map<std::string, OpcodeData> Opcodes {
      {"ldc", OpcodeData{OpcodeType::REG_NUM, char(instruction::Instruction::LOADCONST)}},
      {"ld", OpcodeData{OpcodeType::TWO_REG, char(instruction::Instruction::LOAD)}},
      {"st", OpcodeData{OpcodeType::REG_NUM, char(instruction::Instruction::STORE)}},
      {"add", OpcodeData{OpcodeType::TWO_REG, char(instruction::Instruction::ADD)}},
      {"sub", OpcodeData{OpcodeType::TWO_REG, char(instruction::Instruction::SUB)}},
      {"div", OpcodeData{OpcodeType::TWO_REG, char(instruction::Instruction::DIV)}},
      {"mult", OpcodeData{OpcodeType::TWO_REG, char(instruction::Instruction::MULT)}},
      {"addc", OpcodeData{OpcodeType::REG_NUM, char(instruction::Instruction::ADDC)}},
      {"subc", OpcodeData{OpcodeType::REG_NUM, char(instruction::Instruction::SUBC)}},
      {"divc", OpcodeData{OpcodeType::REG_NUM, char(instruction::Instruction::DIVC)}},
      {"multc", OpcodeData{OpcodeType::REG_NUM, char(instruction::Instruction::MULTC)}},
      {"pr", OpcodeData{OpcodeType::ONE_REG, char(instruction::Instruction::PRINT)}},
      {"prb", OpcodeData{OpcodeType::ONE_REG, char(instruction::Instruction::PRINTB)}},
      {"cjump", OpcodeData{OpcodeType::CONDITIONAL,char(instruction::Instruction::CJUMP)}},
      {"nop", OpcodeData{OpcodeType::NOP,char(instruction::Instruction::NOP)}},
      {"jump", OpcodeData{OpcodeType::JUMP,char(instruction::Instruction::JUMP)}},
      {"push", OpcodeData{OpcodeType::ONE_REG, char(instruction::Instruction::PUSH)}},
      {"pop", OpcodeData{OpcodeType::ONE_REG, char(instruction::Instruction::POP)}},
      {"call", OpcodeData{OpcodeType::JUMP, char(instruction::Instruction::CALL)}},
      {"ret", OpcodeData{OpcodeType::NO_REG, char(instruction::Instruction::RET)}},
  };
}
#endif
