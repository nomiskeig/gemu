#include "Disassembler.h"
#include "../main.h"
#include <iostream>
Disassembler::Disassembler(ProgramPointer pointer) {
    this->program_pointer = pointer;
    printf("is isntalled\n");
}

Instruction *Disassembler::getNextInstruction(uint16_t counter) {
    printf("coutner is %hx\n", counter);
    printf("program pointer is %lx\n", (long)program_pointer);
    printf("address is %lx\n", (program_pointer + counter));
    printf("Value is 0x%hhx\n", read_8(program_pointer + counter));
    long address = program_pointer + counter;
    Byte value = read_8(address);
    if (value == 0x0) {
        return new NOP();
    }
    if (value == 0xc3) {
        return new JP(read_16(address + 1));
    }
    if (value == 0xFE) {
        return new CP(read_8(address + 1));
    }
    if (value == 0x28) {
        return new JR(kFlagZ, read_8(address + 1));
    }
    if (value == 0x3e) {
        return new LD(kN8ToR8, kRegA, read_8(address + 1));
    }
    if (value == 0xEA) {
        return new LD(kAToA16, read_16(address + 1));
    }
    exit_with_error("Could not decode instruction");

    return NULL;
}
