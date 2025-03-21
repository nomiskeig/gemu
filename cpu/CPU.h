#pragma once
#include <cstdint>
using R16Val = int16_t;
using Reg8Val = int8_t;
using AccFlagVal = uint16_t;
using StackPointer = uint16_t;
using ProgramCounter = uint16_t;
using A16 = uint16_t;
using A8 = uint8_t;
using N8 = int8_t;
using N16 = int16_t;
using E8 = int8_t;

class Disassembler;
#define INDEX_FLAG_Z 7
#define INDEX_FLAG_N 6
#define INDEX_FLAG_H 5
#define INDEX_FLAG_C 4
enum Reg16 {
    kRegBC,
    kRegDE,
    kRegHL,
};
enum Reg8 {
    kRegA,
    kRegB,
    kRegC,
    kRegD,
    kRegE,
    kRegH,
    kRegL

};
enum Flag { kFlagZ, kFlagH, kFlagC, kFlagN };
enum FlagValue { kCleared, kSet };
class CPU {
  private:
    ProgramCounter pc;
    AccFlagVal af;
    R16Val bc;
    R16Val de;
    long memory;
    R16Val hl;
    StackPointer sp;

  private:
    Disassembler *dis;

  public:
    CPU(Disassembler *dis);
    void run();
    void increasePC(int amount);
    void setPC(ProgramCounter pc);
    FlagValue get_flag(Flag flag);
    void set_flag(Flag flag);
    void clear_flag(Flag flag);
    void set_Reg8(Reg8 reg, Reg8Val value);
    R16Val get_reg_16(Reg16 reg);
    Reg8Val get_reg_8(Reg8 reg);
    void write_memory(A16 address, N8 val);
};
