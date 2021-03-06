#include "vm.hpp"
#include <cstring>
#include <iostream>
#include <utility>

namespace vm {
VirtualMachine::VirtualMachine(std::string hexData, const std::map<std::string, uint64_t>& attributes) {
  program = std::move(hexData);
  registers = std::array<int, 16>{0};
  memory = std::vector<char>();
  stack = std::vector<char>();
  stack_index = 0;
  programPointer = 0;
  for(auto& attr : attributes){
    if (attr.first == "mem_size"){
      memory.resize(attr.second * 4, 0);
    } else if (attr.first == "stack_size"){
      stack.resize(attr.second * 4, 0);
    }
  }
  if(memory.empty()){
    memory.resize(4096,0);
  }
  if(stack.empty()){
    stack.resize(512, 0);
  }
}

void VirtualMachine::execute() {
  while (programPointer < program.length()) {
    auto instr = decode(program[programPointer++]);
    switch (instr) {
    case instruction::Instruction::ADD: {
      auto regOne = program[programPointer++];
      auto regTwo = program[programPointer++];
      registers[regOne] += registers[regTwo];
      continue;
    }
    case instruction::Instruction::SUB: {
      auto regOne = program[programPointer++];
      auto regTwo = program[programPointer++];
      registers[regOne] -= registers[regTwo];
      continue;
    }
    case instruction::Instruction::MULT: {
      auto regOne = program[programPointer++];
      auto regTwo = program[programPointer++];
      registers[regOne] *= registers[regTwo];
      continue;
    }
    case instruction::Instruction::DIV: {
      auto regOne = program[programPointer++];
      auto regTwo = program[programPointer++];
      registers[regOne] /= registers[regTwo];
      continue;
    }
    case instruction::Instruction::CJUMP: {
      auto cond = decodeCondition(program[programPointer++]);
      auto cond_location = programPointer-1;
      auto regOne = program[programPointer++];
      auto regTwo = program[programPointer++];
      auto dest = getInt();
      switch (cond) {
      case condition::Condition::EQ: {
        if (registers[regOne] == registers[regTwo]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::NEQ: {
        if (registers[regOne] != registers[regTwo]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::LT: {
        if (registers[regOne] < registers[regTwo]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::LE: {
        if (registers[regOne] <= registers[regTwo]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::GT: {
        if (registers[regOne] > registers[regTwo]) {
          programPointer = dest;
        }
        continue;
      }
      case condition::Condition::GE: {
        if (registers[regOne] >= registers[regTwo]) {
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
      auto reg = program[programPointer++];
      auto integer = getInt();
      memcpy(&(registers[reg]), &(memory[integer]), 4);
      continue;
    }
    case instruction::Instruction::STORE: {
      auto reg = program[programPointer++];
      auto integer = getInt();
      memcpy(&(memory[integer]),
             reinterpret_cast<char *>(&(registers[reg])), 4);
      continue;
    }
    case instruction::Instruction::PRINT: {
      auto reg = program[programPointer++];
      std::cout << registers[reg] << std::endl;
      continue;
    }
    case instruction::Instruction::PRINTB: {
      auto reg = program[programPointer++];
      std::cout << ((registers[reg] > 0) ? "true" : "false") << std::endl;
      continue;
    }
    case instruction::Instruction::LOADCONST: {
      auto reg = program[programPointer++];
      auto integer = getInt();
      registers[reg] = integer;
      continue;
    }
    case instruction::Instruction::ADDC: {
      auto reg = program[programPointer++];
      auto integer = getInt();
      registers[reg] += integer;
      continue;
    }
    case instruction::Instruction::SUBC: {
      auto reg = program[programPointer++];
      auto integer = getInt();
      registers[reg] -= integer;
      continue;
    }
    case instruction::Instruction::DIVC: {
      auto reg = program[programPointer++];
      auto integer = getInt();
      registers[reg] /= integer;
      continue;
    }
    case instruction::Instruction::MULTC: {
      auto reg = program[programPointer++];
      auto integer = getInt();
      registers[reg] *= integer;
      continue;
    }
    case instruction::Instruction::JUMP: {
      programPointer = getInt();
      continue;
    }
    case instruction::Instruction::NOP: {
      continue;
    }
    case instruction::Instruction::PUSH: {
      auto reg = program[programPointer++];
      pushWord(registers[reg]);
      continue;
    }
    case instruction::Instruction::POP: {
      auto reg = program[programPointer++];
      registers[reg] = popWord();
      continue;
    }
    case instruction::Instruction::CALL: {
      pushWord(programPointer+4);
      programPointer = getInt();
      continue;
    }
    case instruction::Instruction::RET: {
      programPointer = popWord();
      continue;
    }
    default:
      std::cout << "ERROR: Invalid op code at " << programPointer - 1
                << std::endl;
      return;
    }
  }
}

void VirtualMachine::pushWord(int32_t word){
  memcpy(&(stack[stack_index]), reinterpret_cast<char *>( & (word)), 4 );
  stack_index += 4;
}

int32_t VirtualMachine::popWord(){
  int32_t res;
  stack_index -=4;
  memcpy(reinterpret_cast<char *>( &res), &(stack[stack_index]), 4);
  return res;
}

instruction::Instruction VirtualMachine::decode(char byte) {
  if (byte < char(instruction::Instruction::BAD)){
    return instruction::Instruction(byte);
  }
  return instruction::Instruction::BAD;
}

int32_t VirtualMachine::getInt() {
  int32_t integer = 0;
  for (int i = 0; i < 4; i++) {
    integer += (reinterpret_cast<unsigned char &>(program[programPointer++]) << (i * 8));
  }
  return integer;
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
