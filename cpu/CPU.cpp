#include "CPU.h"
#include "../main.h"
#include "./Disassembler.h"
#include "./Instruction.h"
#include <iostream>
#include <unistd.h>

CPU::CPU(Disassembler *dis) {
    this->pc = 0x100;
    this->dis = dis;
    this->memory = (long)malloc(0xFFFF);
    this->sp = 0xFFF8;
}

void CPU::run() {
    while (true) {
        Instruction *instr = this->dis->getNextInstruction(this->pc);
        std::cout << "Instuction is " << instr->getTextString() << "\n";
        instr->execute(this);
    }
}
void CPU::increasePC(int amount) { this->pc += amount; }

void CPU::setPC(ProgramCounter pc) { this->pc = pc; }

Reg8Val CPU::get_reg_8(Reg8 reg) {
    switch (reg) {
    case kRegA: {

        return (Reg8Val)this->af >> 0x4;
        break;
    }
    default:
        exit_with_error("Unknown reg in get_reg_8");
    }
}
static int get_flag_index(Flag flag) {
    int index;
    switch (flag) {
    case kFlagZ:
        index = INDEX_FLAG_C;
        break;

    case kFlagH:
        index = INDEX_FLAG_H;
        break;
    case kFlagC:
        index = INDEX_FLAG_C;
        break;
    case kFlagN:
        index = INDEX_FLAG_N;
        break;
    }
    return index;
}

void CPU::clear_flag(Flag flag) {
    int index = get_flag_index(flag);
    this->af &= ~(0x1 << index);
}
void CPU::set_flag(Flag flag) {
    int index = get_flag_index(flag);
    this->af |= 0x1 << index;
}

FlagValue CPU::get_flag(Flag flag) {
    int index = get_flag_index(flag);
    if (this->af | (0x1 << index)) {
        return kSet;
    }
    return kCleared;
}

void CPU::set_Reg8(Reg8 reg, N8 val) {
    switch (reg) {

    case kRegA: {
        this->af &= 0x0F;
        this->af |= val << 0x4;
        break;
    }
    default:
        exit_with_error("Got unhanlded reg in set_Reg8");
    }
}

void CPU::write_memory(A16 address, N8 val) {
    if (address >= 0xFF00 && address < 0xFF80) {
        exit_with_error("Found address access for an I/O register");
    }
}
