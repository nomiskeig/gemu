#pragma once
#include "../main.h"
#include "./CPU.h"
#include <string>
#define get_bit(val, index) (val & 0x1 << index)
enum ArgType {
    kN8,
    kN16,

};
enum LDAction {
    kN8ToR8,
    kAToA16
};
class Instruction {

  protected:
    std::string text_string;
    int cycles;

  public:
    std::string getTextString();
    virtual void execute(CPU *cpu) = 0;
};

class NOP : public Instruction {

  public:
    void execute(CPU *cpu) override;
    NOP();
};
class JP : public Instruction {

  private:
    ProgramCounter pc;

  public:
    void execute(CPU *cpu) override;
    JP(ProgramCounter pc);
};

class CP : public Instruction {
  private:
    ArgType type;
    N8 n8;

  public:
    void execute(CPU *cpu) override;
    CP(N8 n8);
};

class JR : public Instruction {
  private:
    Flag flag;
    E8 offset;

  public:
    void execute(CPU *cpu) override;
    JR(Flag flag, E8 offset);
};

class LD : public Instruction {
  private:
    Reg8 reg8;
    N8 valN8;
    LDAction action;
    A16 address;

  public:
    void execute(CPU *cpu) override;
    LD(LDAction action, Reg8 reg, N8 value);
    LD(LDAction, A16  address);
};
