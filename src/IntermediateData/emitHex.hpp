#ifndef emit_hex_h
#define emit_hex_h

#include "condition.hpp"
#include "instruction.hpp"
#include "opcodeData.hpp"
#include <iostream>
#include <map>
#include <string>
namespace EmitHex {

  const auto ConditionMap = std::map<std::string,char> {
      {"EQ", char(condition::Condition::EQ)},
      {"NEQ", char(condition::Condition::NEQ)},
      {"LE", char(condition::Condition::LE)},
      {"GE", char(condition::Condition::GE)},
      {"LT", char(condition::Condition::LT)},
      {"GT", char(condition::Condition::GT)},
  };
  const auto RegisterMap = std::map<std::string,char> {
      {"ra", char(0)},
      {"rb", char(1)},
      {"rc", char(2)},
      {"rd", char(3)},
      {"re", char(4)},
      {"rf", char(5)},
      {"rg", char(6)},
      {"rh", char(7)},
      {"ri", char(8)},
      {"rj", char(9)},
      {"rk", char(10)},
      {"rl", char(11)},
      {"rm", char(12)},
      {"rn", char(13)},
      {"ro", char(14)},
      {"rp", char(15)},
  };

class EmitHexData {
public:
  EmitHexData() = delete;

  static char EmitOpcode(std::string opcode){
    return opcodeData::Opcodes.at(opcode).encoding;
  }

  static std::string EmitInteger(std::string number){
    try {
      auto num = std::stoi(number);
      auto hex = (char *)(&num);
      return hex;
    }
    catch (...){
      auto exceptionPointer = std::current_exception();
      std::cerr << "Error while decoding " << number << std::endl;
      return nullptr;
    }
  }

  static std::string EmitCondition(const std::string& cond){
    return std::string(1, ConditionMap.at(cond));
  }

  static std::string EmitRegister(const std::string& reg){
    return std::string(1,RegisterMap.at(reg));
  }
};

}

#endif
