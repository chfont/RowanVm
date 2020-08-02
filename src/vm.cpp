#include "vm.hpp"
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
    case instruction::Instruction::ADD: {
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      registers[a] += registers[b];
      continue;
    }
    case instruction::Instruction::SUB: {
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      registers[a] -= registers[b];
      continue;
    }
    case instruction::Instruction::MULT: {
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      registers[a] *= registers[b];
      continue;
    }
    case instruction::Instruction::DIV: {
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      registers[a] /= registers[b];
      continue;
    }
    case instruction::Instruction::CJUMP: {
      auto cond = decodeCondition(program[programPointer++]);
      auto cond_location = programPointer--;
      auto a = program[programPointer++];
      auto b = program[programPointer++];
      auto dest = getInt();
      switch (cond) {
      case condition::Condition::EQ: {
        if (registers[a] == registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::NEQ: {
        if (registers[a] != registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::LT: {
        if (registers[a] < registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::LE: {
        if (registers[a] <= registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::GT: {
        if (registers[a] > registers[b]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::GE: {
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
    case instruction::Instruction::LOAD: {
      auto a = program[programPointer++];
      auto integer = getInt();
      registers[a] = memory[integer];
      continue;
    }
    case instruction::Instruction::STORE: {
      auto a = program[programPointer++];
      auto integer = getInt();
      memcpy(memory.begin() + integer,
             reinterpret_cast<char *>(&(registers[a])), 4);
      continue;
    }
    case instruction::Instruction::PRINT: {
      auto a = program[programPointer++];
      std::cout << registers[a] << std::endl;
      continue;
    }
    case instruction::Instruction::PRINTB: {
      auto a = program[programPointer++];
      std::cout << ((registers[a] > 0) ? "true" : "false") << std::endl;
      continue;
    }
    case instruction::Instruction::LOADCONST: {
      auto a = program[programPointer++];
      auto integer = getInt();
      registers[a] = integer;
    }
    case instruction::Instruction::NOP: {
      continue;
    }
    default:
      std::cout << "ERROR: Invalid op code at " << programPointer - 1
                << std::endl;
      return;
    }
  }
}

instruction::Instruction VirtualMachine::decode(char byte) {
  switch (byte) {
  case 0:
    return instruction::Instruction::ADD;
  case 1:
    return instruction::Instruction::SUB;
  case 2:
    return instruction::Instruction::MULT;
  case 3:
    return instruction::Instruction::DIV;
  case 4:
    return instruction::Instruction::CJUMP;
  case 5:
    return instruction::Instruction::LOAD;
  case 6:
    return instruction::Instruction::STORE;
  case 7:
    return instruction::Instruction::PRINT;
  case 8:
    return instruction::Instruction::PRINTB;
  case 9:
    return instruction::Instruction::NOP;
  case 10:
    return instruction::Instruction::LOADCONST;
  default:
    return instruction::Instruction::BAD;
  }
}

int32_t VirtualMachine::getInt() {
  int32_t a = 0;
  for (int i = 0; i < 4; i++) {
    a += program[programPointer++] << (i * 8);
  }
  return a;
}

condition::Condition VirtualMachine::decodeCondition(char byte) {
  switch (byte) {
  case 0:
    return condition::Condition::EQ;
  case 1:
    return condition::Condition::NEQ;
  case 2:
    return condition::Condition::LT;
  case 3:
    return condition::Condition::GT;
  case 4:
    return condition::Condition::LE;
  case 5:
    return condition::Condition::GE;
  default:
    return condition::Condition::BAD;
  }
}

}
