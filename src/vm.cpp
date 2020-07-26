#include "vm.hpp"
#include "condition.hpp"
#include <cstring>
#include <iostream>

namespace vm {
VirtualMachine::VirtualMachine(std::string hexData) {
  program = hexData;
  registers = std::array<int, 16>{0};
  memory = std::array<char, 1024>{0};
  programPointer = 0;
}

void VirtualMachine::execute() {
  while (programPointer < program.length()) {
    auto instr = decode(program[programPointer++]);
    switch (instr) {
    case Instruction::ADD: {
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      registers[a] += registers[b];
      continue;
    }
    case Instruction::SUB: {
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      registers[a] -= registers[b];
      continue;
    }
    case Instruction::MULT: {
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      registers[a] *= registers[b];
      continue;
    }
    case Instruction::DIV: {
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      registers[a] /= registers[b];
      continue;
    }
    case Instruction::CJUMP: {
      auto cond = decodeCondition(program[programPointer++]);
      auto cond_location = programPointer--;
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      auto dest = getInt();
      switch (cond) {
      case Condition::EQ: {
        if (registers[a] == registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case Condition::NEQ: {
        if (registers[a] != registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case Condition::LT: {
        if (registers[a] < registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case Condition::LE: {
        if (registers[a] <= registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case Condition::GT: {
        if (registers[a] > registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case Condition::GE: {
        if (registers[a] >= registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      default:
        std::cout << "ERROR: Condition invalid at byte " << cond_location
                  << std::endl;
        return;
      }
    }
    case Instruction::LOAD: {
      auto a = program[programPointer++];
      auto integer = getInt();
      registers[a] = memory[integer];
      continue;
    }
    case Instruction::STORE: {
      auto a = program[programPointer++];
      auto integer = getInt();
      memcpy(memory.begin() + integer,
             reinterpret_cast<char *>(&(registers[a])), 4);
      continue;
    }
    case Instruction::PRINT: {
      auto a = program[programPointer++];
      std::cout << registers[a] << std::endl;
      continue;
    }
    case Instruction::PRINTB: {
      auto a = program[programPointer++];
      std::cout << ((registers[a] > 0) ? true : false) << std::endl;
      continue;
    }
    case Instruction::LOADCONST: {
      auto a = program[programPointer++];
      auto integer = getInt();
      registers[a] = integer;
    }
    case Instruction::NOP: {
      continue;
    }
    default:
      std::cout << "ERROR: Invalid op code at " << programPointer - 1
                << std::endl;
      return;
    }
  }
}

Instruction::Instruction VirtualMachine::decode(char byte) {
  switch (byte) {
  case 0:
    return Instruction::ADD;
  case 1:
    return Instruction::SUB;
  case 2:
    return Instruction::MULT;
  case 3:
    return Instruction::DIV;
  case 4:
    return Instruction::CJUMP;
  case 5:
    return Instruction::LOAD;
  case 6:
    return Instruction::STORE;
  case 7:
    return Instruction::PRINT;
  case 8:
    return Instruction::PRINTB;
  case 9:
    return Instruction::NOP;
  case 10:
    return Instruction::LOADCONST;
  default:
    return Instruction::BAD;
  }
}

int32_t VirtualMachine::getInt() {
  int32_t a = 0;
  for (int i = 0; i < 4; i++) {
    a += program[programPointer++] << (i * 8);
  }
  return a;
}

Condition::Condition VirtualMachine::decodeCondition(char byte) {
  switch (byte) {
  case 0:
    return Condition::EQ;
  case 1:
    return Condition::NEQ;
  case 2:
    return Condition::LT;
  case 3:
    return Condition::GT;
  case 4:
    return Condition::LE;
  case 5:
    return Condition::GE;
  default:
    return Condition::BAD;
  }
}

} // namespace vm
