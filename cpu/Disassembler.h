#pragma once

#include "Instruction.h"
#include <cstdint>
#define read_16(addr) (*(uint16_t*)(addr))
#define read_8(addr) (*(char*)(addr))
using ProgramPointer = uint64_t;
using Byte = unsigned char;

class Disassembler {
  private:
    ProgramPointer program_pointer;

  public:
    Disassembler(ProgramPointer pointer);
    Instruction *getNextInstruction(uint16_t program_counter,char* memory);
};
