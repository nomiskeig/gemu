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
    kN16ToR16,
    kAToA16,
    kA16ToA,
    kR16AddrToA,
    kAddr16ToA,
    kRegToReg,
    kRegToHL,
    kHLToReg,
    kHLToAInc,
    kAToHLInc,
    kAToHLDec,
    kAToReg16Addr
};
class Instruction {

  protected:
    std::string text_string;
    int cycles;

  public:
    std::string getTextString();
    virtual int execute(CPU *cpu) = 0;
};

class NOP : public Instruction {

  public:
    int execute(CPU *cpu) override;
    NOP();
};
enum JPAction { kJPPC, kJPHL };
class JP : public Instruction {

  private:
    ProgramCounter pc;
    JPAction action;

  public:
    int execute(CPU *cpu) override;
    JP(ProgramCounter pc);
    JP();
};

class CP : public Instruction {
  private:
    ArgType type;
    N8 n8;

  public:
    int execute(CPU *cpu) override;
    CP(N8 n8);
};
enum JRAction { kJRCond, kJRUncond };

enum JRCondType {
    kJRCondNormal,
    kJRCondNot,
};

class JR : public Instruction {
  private:
    Flag flag;
    E8 offset;
    JRCondType type;
    JRAction action;

  public:
    int execute(CPU *cpu) override;
    JR(Flag flag, JRCondType type, E8 offset);
    JR(E8 offset);
};

class LD : public Instruction {
  private:
    Reg8 reg8;
    Reg16 reg16;
    Reg8 source;
    Reg8 dest;
    N8 valN8;
    N16 valN16;
    LDAction action;
    A16 address;

  public:
    int execute(CPU *cpu) override;
    LD(LDAction action, Reg8 reg, N8 value);
    LD(LDAction action, Reg16 reg, N16 value);
    LD(LDAction action, Reg8 source, Reg8 dest);
    LD(LDAction action, A16 address);
    LD(LDAction action, Reg8 reg);
    LD(LDAction action, Reg16 reg);
    LD(LDAction action);
};

class CALL : public Instruction {
  private:
    A16 address;
    A16 retAddress;

  public:
    int execute(CPU *cpu) override;
    CALL(A16 address, A16 retAddress);
};
enum StackAction { kStackRegister, kStackAddress };
class PUSH : public Instruction {
  private:
    StackAction action;
    A16 address;
    Reg16 reg16;

  public:
    int execute(CPU *cpu) override;
    PUSH(A16 address);
    PUSH(Reg16 reg);
};
class POP : public Instruction {
  private:
    Reg16 reg16;

  public:
    int execute(CPU *cpu) override;
    POP(Reg16 reg);
};
enum XORAction { kXORReg, kXORHL, kXORN8 };
class XOR : public Instruction {
  private:
    XORAction action;
    Reg8 reg;

  public:
    int execute(CPU *cpu) override;
    XOR(Reg8 reg);
};

enum ORAction {
    kORAReg,
};
class OR : public Instruction {
  private:
    ORAction action;
    Reg8 reg;

  public:
    int execute(CPU *cpu) override;
    OR(Reg8 reg);
};
enum ANDAction {
    kANDAN8,
};
class AND : public Instruction {
  private:
    ANDAction action;
    N8 val;

  public:
    int execute(CPU *cpu) override;
    AND(N8 val);
};
class DI : public Instruction {
  private:
  public:
    int execute(CPU *cpu) override;
    DI();
};
enum LDHAction { kLDHAToAddress, kLDHAddressToA };
class LDH : public Instruction {
  private:
    A8 address;
    LDHAction action;

  public:
    int execute(CPU *cpu) override;
    LDH(LDHAction action, A8 address);
};

enum RETAction { kRETCond, kRetUncond };
enum RETCondType {
    kRETCondNormal,
    kRETCondNot,
};

class RET : public Instruction {
  private:
    Flag flag;
    RETAction action;
    RETCondType type;

  public:
    int execute(CPU *cpu) override;
    RET(Flag flag, RETCondType type);
    RET();
};
enum DECAction { kDECR8, kDECR16 };
class DEC : public Instruction {
  private:
    Reg16 reg16;
    Reg8 reg8;
    DECAction action;

  public:
    int execute(CPU *cpu) override;
    DEC(Reg16 reg16);
    DEC(Reg8 reg8);
};
enum INCAction { kINCR8, kINCR16 };
class INC : public Instruction {
  private:
    Reg16 reg16;
    Reg8 reg8;
    INCAction action;

  public:
    int execute(CPU *cpu) override;
    INC(Reg16 reg16);
    INC(Reg8 reg8);
};
class SRL : public Instruction {
  private:
    Reg8 reg;

  public:
    int execute(CPU *cpu) override;
    SRL(Reg8 reg);
};
enum ADDAction { kADDRegToHL, kADDRegToA, kADDN8ToA };
class ADD : public Instruction {
  private:
    Reg16 reg16;
    Reg8 reg8;
    N8 n8;
    ADDAction action;

  public:
    int execute(CPU *cpu) override;
    ADD(Reg16 reg16);
    ADD(Reg8 reg8);
    ADD(N8 n8);
};
class RR : public Instruction {
  private:
    Reg8 reg;

  public:
    int execute(CPU *cpu) override;
    RR(Reg8 reg);
};
class STOP : public Instruction {
  private:
    N8 val;

  public:
    int execute(CPU *cpu) override;
    STOP(N8 val);
};
enum ADCAction { kADCRegToA, kADCN8ToA };
class ADC : public Instruction {
  private:
    Reg8 reg8;
    N8 n8;
    ADCAction action;

  public:
    int execute(CPU *cpu) override;
    ADC(Reg8 reg);
    ADC(N8 n8);
};
class RLCA : public Instruction {
  public:
    int execute(CPU *cpu) override;
};
enum SUBAction { kSUBN8ToA };
class SUB : public Instruction {
  private:
    SUBAction action;
    N8 n8;

  public:
    SUB(N8 n8);
    int execute(CPU *cpu) override;
};
class RRA : public Instruction {
  public:
    int execute(CPU *cpu) override;
    RRA();
};
