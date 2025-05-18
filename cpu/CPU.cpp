#include "CPU.h"
#include "../config.h"
#include "../main.h"
#include "./Disassembler.h"
#include "./Instruction.h"
#include <iostream>
#include <unistd.h>

CPU::CPU(Disassembler *dis) {
    this->dis = dis;
    this->interrupts = new Interrupts();
    this->graphics = new Graphics();
    this->timer = new Timer();
    this->audio = new Audio();
    this->memory = (char *)malloc(0xFFFF);
    this->highMem = (char *)malloc(0xFFFF - 0xFF80);
    this->remainingTicksForInstruction = 0;
    this->currentInstruction = NULL;

    this->af = 0x100;
    this->bc = 0xFF13;
    this->de = 0x00C1;
    this->hl = 0x8403;
    this->pc = 0x100;
    this->sp = 0xFFFE;
}

void CPU::tick() {
    if (this->remainingTicksForInstruction == 0) {
        this->currentInstruction = this->dis->getNextInstruction(this->pc);
        std::cout << "Instuction is "
                  << this->currentInstruction->getTextString() << "\n";
        this->remainingTicksForInstruction =
            this->currentInstruction->execute(this);
        ProgramCounter old = this->pc;
        GEMU_PRINT_INSTURUCTIONS("Instruction is %s",
                                 this->currentInstruction->getTextString().c_str());
        if (old == this->pc) {
            exit_with_error("Forgot to increase pc");
        }
        this->print();
    }
    this->remainingTicksForInstruction -= 1;
}
void CPU::disableInterrupts() { this->ime = kIMEDisabled; }
void CPU::increasePC(int amount) { this->pc += amount; }

void CPU::setPC(ProgramCounter pc) { this->pc = pc; }

Reg8Val CPU::get_reg_8(Reg8 reg) {
    switch (reg) {

    case kRegA: {

        return this->af >> 0x8;
        break;
    }
    case kRegB: {
        return this->bc >> 0x8;
        break;
    }
    case kRegC: {

        return this->bc & 0xFF;
        break;
    }
    case kRegD: {
        return this->de >> 0x8;
    }
    case kRegE: {
        return this->de & 0xFF;
    }
    case kRegH: {
        return this->hl >> 0x8;
    }
    case kRegL: {
        return this->hl & 0xFF;
    }
    default:
        exit_with_error("Unknown reg in get_reg_8");
    }
}

Reg16Val CPU::get_reg_16(Reg16 reg) {
    switch (reg) {
    case kRegAF: {
        return this->af;
    }
    case kRegBC: {
        return this->bc;
    }
    case kRegHL: {
        return this->hl;
    }
    case kRegSP: {
        return this->sp;
    }

    case kRegDE: {
        return this->de;
    }

    default:
        exit_with_error("Unknown reg in get_reg_16");
    }
}
static int get_flag_index(Flag flag) {
    int index;
    switch (flag) {
    case kFlagZ:
        index = INDEX_FLAG_Z;
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

void CPU::clearAllFlags() {
    this->clear_flag(kFlagN);
    this->clear_flag(kFlagZ);
    this->clear_flag(kFlagC);
    this->clear_flag(kFlagH);
}
FlagValue CPU::get_flag(Flag flag) {
    int index = get_flag_index(flag);
    if (this->af & (0x1 << index)) {
        return kSet;
    }

    return kCleared;
}
std::string reg8_to_str(Reg8 reg) {
    switch (reg) {

    case kRegA:
        return "A";
    case kRegB:
        return "B";
    case kRegC:
        return "C";
    case kRegD:
        return "D";
    case kRegE:
        return "E";
    case kRegH:
        return "H";
    case kRegL:
        return "L";
        break;
    }
}
std::string reg16_to_str(Reg16 reg) {
    switch (reg) {

    case kRegBC:
        return "BC";
    case kRegDE:
        return "DE";
    case kRegHL:
        return "HL";
    case kRegSP:
        return "SP";
    case kRegAF:
        return "AF";
        break;
    }
}
std::string flagToName(Flag flag) {
    switch (flag) {

    case kFlagZ:
        return "Z";
    case kFlagH:
        return "H";
    case kFlagC:
        return "C";
    case kFlagN:
        return "N";
        break;
    }
}
void CPU::set_Reg8(Reg8 reg, N8 val) {
    switch (reg) {

    case kRegA: {
        printf("setting reg A to val %hhx\n", val);
        this->af &= 0x0FF;
        this->af |= val << 0x8;
        break;
    }

    case kRegB: {
        this->bc &= 0x00FF;
        this->bc |= val << 0x8;
        break;
    }
    case kRegC: {
        this->bc &= 0xFF00;
        this->bc |= val;
        break;
    }

    case kRegD: {
        this->de &= 0x00FF;
        this->de |= val << 0x08;
        break;
    }
    case kRegE: {
        this->de &= 0xFF00;
        this->de |= val;
        break;
    }
    case kRegH: {
        this->hl &= 0x0FF;
        this->hl |= val << 0x08;
        break;
    }
    case kRegL: {
        this->hl &= 0xFF00;
        this->hl |= val;
        break;
    }
    default:
        exit_with_error("Got unhanlded reg in set_Reg8");
    }
}
void CPU::set_reg16(Reg16 reg, N16 val) {
    switch (reg) {

    case kRegAF: {
        this->af = val;
        break;
    }
    case kRegBC: {
        this->bc = val;
        break;
    }
    case kRegDE: {
        this->de = val;
        break;
    }
    case kRegHL: {
        this->hl = val;
        break;
    }
    case kRegSP: {
        this->sp = val;
        break;
    }
    default:
        exit_with_error("Got unhandled reg in set_reg16");
    }
}
N8 CPU::read_memory(A16 address) {
    if (address >= 0x0 && address < 0xFF00) {
        return *(this->memory + address);
    }
    if (address >= 0xFF80 && address < 0xFFFF) {

        return *(this->highMem + address);
    }
    if (address == 0xFFFF) {
        return this->interrupts->getIE();
    }

    printf("reading memory at 0x%x\n", address);
    exit_with_error("Could not read the memory");
}

void CPU::write_memory(A16 address, N8 val) {
    if (address >= 0x0 && address < 0xFF00) {
        *(this->memory + address) = val;
        return;
    }
    if (address >= 0xFF80 && address < 0xFFFF) {
        GEMU_PRINT_HIGHMEM_WRITES("0x%x = 0x%hhx", address, val);
        *(this->highMem + address) = val;
        return;
    }
    if (address == 0xFF01) {
        this->serial->setSB(val);
        return;
    }
    if (address == 0xFF02) {
        this->serial->setSC(val);
        return;
    }
    if (address == 0xFF07) {
        this->timer->setTAC(val);
        return;
    }
    if (address == 0xFF0F) {
        this->interrupts->setIF(val);
        return;
    }
    if (address == 0xFF20) {
        this->audio->setNR41(val);
        return;
    }
    if (address == 0xFF24) {
        this->audio->setNR50(val);
        return;
    }
    if (address == 0xFF25) {
        this->audio->setNR51(val);
        return;
    }
    if (address == 0xFF26) {
        this->audio->setNR52(val);
        return;
    }
    if (address == 0xFF40) {
        this->graphics->setLCDC(val);
        return;
    }
    if (address == 0xFF41) {
        this->graphics->setStat(val);
        return;
    }
    if (address == 0xFF42) {
        this->graphics->setSCY(val);
        return;
    }
    if (address == 0xFF43) {
        this->graphics->setSCX(val);
        return;
    }
    if (address == 0xFF47) {
        this->graphics->setBGP(val);
        return;
    }
    if (address == 0xFF4A) {
        this->graphics->setWY(val);
        return;
    }
    if (address == 0xFF4B) {
        this->graphics->setWX(val);
        return;
    }
    if (address == 0xFFFF) {
        this->interrupts->setIE(val);
        return;
    }
    if (address >= 0xFF00 && address <= 0xFFFF) {
        printf("address is 0x%x\n", address);
        exit_with_error("Found address access for an I/O register");
    }
}
void CPU::modifySP(int amount) { this->sp += amount; }
StackPointer CPU::getSP() { return this->sp; }
void CPU::print() {
    std::cout << "CPU state:\n";
    std::cout << "PC: " << this->pc << "\n";
    std::cout << "SP: " << this->sp << "\n";
    std::cout << "AF: " << this->af << "\n";
    std::cout << "BC: " << this->bc << "\n";
    std::cout << "DE: " << this->de << "\n";
    std::cout << "HL: " << this->hl << "\n";
    std::cout << "Flags: Z: " << this->get_flag(kFlagZ)
              << ", N: " << this->get_flag(kFlagN)
              << ", H: " << this->get_flag(kFlagH)
              << ", C: " << this->get_flag(kFlagC) << "\n";
}
