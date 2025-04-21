#pragma once
#include <cstdint>
#include <string>
#include "./Interrupts.h"
#include "./Graphics.h"
#include "./Timer.h"
#include "./Audio.h"
using R16Val = int16_t;
using Reg8Val = int8_t;
using Reg16Val = int16_t;
using AccFlagVal = uint16_t;
using StackPointer = uint16_t;
using ProgramCounter = uint16_t;
using A16 = uint16_t;
using A8 = uint8_t;
using N8 = int8_t;
using N16 = int16_t;
using E8 = int8_t;
#define CYCLES_PER_FRAME 70224



class Disassembler;
#define INDEX_FLAG_Z 7
#define INDEX_FLAG_N 6
#define INDEX_FLAG_H 5
#define INDEX_FLAG_C 4
enum Reg16 {
    kRegBC,
    kRegDE,
    kRegHL,
    kRegSP,
    kRegAF
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
std::string reg8_to_str(Reg8 reg);
std::string reg16_to_str(Reg16 reg);
enum IME {
    kIMEDisabled, kIMEEnabled
};
enum Flag { kFlagZ, kFlagH, kFlagC, kFlagN };
std::string flagToName(Flag flag);
enum FlagValue { kCleared, kSet };
class CPU {
  private:
    ProgramCounter pc;
    AccFlagVal af;
    R16Val bc;
    R16Val de;
    char* memory;
    char* highMem;
    R16Val hl;
    StackPointer sp;
    IME ime;

  private:
    Disassembler *dis;
    Interrupts *interrupts;
    Graphics* graphics;
    Timer* timer;
    Audio * audio;

  public:
    CPU(Disassembler *dis);
    void tick();
    void increasePC(int amount);
    void modifySP(int amount);
    StackPointer getSP();
    void print();
    
    void disableInterrupts();
    void clearAllFlags();
    void setPC(ProgramCounter pc);
    FlagValue get_flag(Flag flag);
    void set_flag(Flag flag);
    void clear_flag(Flag flag);
    void set_Reg8(Reg8 reg, Reg8Val value);
    void set_reg16(Reg16 reg, Reg16Val value);
    R16Val get_reg_16(Reg16 reg);
    Reg8Val get_reg_8(Reg8 reg);
    void write_memory(A16 address, N8 val);
    N8 read_memory(A16 address);

};
