#include "Disassembler.h"
#include "../main.h"
#include <iostream>
Disassembler::Disassembler(ProgramPointer pointer) {
    this->program_pointer = pointer;
    printf("is isntalled\n");
}

static Instruction *disassemble_prefix(long address) {
    printf("Second byte for prefix is 0x%hhx\n", read_8(address + 1));
    Byte value = read_8(address + 1);
    if (value == 0x19) {
        return new RR(kRegC);
    }
    if (value == 0x38) {
        return new SRL(kRegB);
    }
    if (value == 0x3F) {
        return new SRL(kRegA);
    }

    exit_with_error("Could not decode prefixed instruction");
}

Instruction *Disassembler::getNextInstruction(uint16_t counter) {
    printf("Counter is %hx\n", counter);
    printf("Address is %lx\n", (program_pointer + counter));
    printf("Value is 0x%hhx\n", read_8(program_pointer + counter));
    long address = program_pointer + counter;
    Byte value = read_8(address);
    if (value == 0x0) {
        return new NOP();
    }
    if (value == 0x01) {
        return new LD(kN16ToR16, kRegBC, read_16(address + 1));
    }
    if (value == 0x03) {
        return new INC(kRegBC);
    }
    if (value == 0x04) {
        return new INC(kRegB);
    }
    if (value == 0x05) {
        return new DEC(kRegB);
    }
    if (value == 0x06) {
        return new LD(kN8ToR8, kRegB, read_8(address+ 1));
    }
    if (value == 0x07) {
        return new RLCA();
    }
    if (value == 0x0A) {
        return new LD(kR16AddrToA, kRegBC);
    }
    if (value == 0xb) {
        return new DEC(kRegBC);
    }
    if (value == 0xC) {
        return new INC(kRegC);
    }
    if (value == 0xD) {
        return new DEC(kRegC);
    }
    if (value == 0xE) {
        printf("raead 0x%x\n", read_8(address + 1));
        return new LD(kN8ToR8, kRegC, read_8(address + 1));
    }
    if (value == 0x10) {
        return new STOP(read_8(address + 1));
    }
    if (value == 0x11) {
        return new LD(kN16ToR16, kRegDE, read_16(address + 1));
    }
    if (value == 0x12) {
        return new LD(kAToReg16Addr, kRegDE);
    }
    if (value == 0x13) {
        return new INC(kRegDE);
    }
    if (value == 0x14) {
        return new INC(kRegD);
    }
    if (value == 0x18) {
        return new JR(read_8(address + 1));
    }
    if (value == 0x19) {
        return new ADD(kRegDE);
    }
    if (value == 0x1A) {
        return new LD(kR16AddrToA, kRegDE);
    }
    if (value == 0x1C) {
        return new INC(kRegE);
    }
    if (value == 0x1F) {
        return new RRA();
    }
    if (value == 0x20) {
        return new JR(kFlagZ, kJRCondNot, read_8(address + 1));
    }
    if (value == 0x21) {
        return new LD(kN16ToR16, kRegHL, read_16(address + 1));
    }
    if (value == 0x22) {
        return new LD(kAToHLInc);
    }
    if (value == 0x23) {
        return new INC(kRegHL);
    }
    if (value == 0x24) {
        return new INC(kRegH);
    }
    if (value == 0x28) {
        return new JR(kFlagZ, kJRCondNormal, read_8(address + 1));
    }
    if (value == 0x2A) {
        return new LD(kHLToAInc);
    }
    if (value == 0x2C) {
        return new INC(kRegL);
    }
    if (value == 0x30) {
        return new JR(kFlagC, kJRCondNot, read_8(address + 1));
    }
    if (value == 0x31) {
        return new LD(kN16ToR16, kRegSP, read_16(address + 1));
    }
    if (value == 0x32) {
        return new LD(kAToHLDec);
    }
    if (value == 0x3C) {
        return new INC(kRegA);
    }
    if (value == 0x3D) {
        return new DEC(kRegA);
    }
    if (value == 0x3e) {
        return new LD(kN8ToR8, kRegA, read_8(address + 1));
    }
    if (value == 0x40) {
        return new LD(kRegToReg, kRegB, kRegB);
    }
    if (value == 0x47) {
        return new LD(kRegToReg,kRegA, kRegB);
    }
    if (value == 0x54) {
        return new LD(kRegToReg, kRegH, kRegD);
    }
    if (value == 0x57) {
        return new LD(kRegToReg, kRegA, kRegD);
    }
    if (value == 0x58) {
        return new LD(kRegToReg, kRegB, kRegE);
    }
    if (value == 0x5D) {
        return new LD(kRegToReg, kRegL, kRegE);
    }
    if (value == 0x5F) {
        return new LD(kRegToReg, kRegA, kRegE);
    }
    if (value == 0x63) {
        return new LD(kRegToReg, kRegE, kRegH);
    }
    if (value == 0x67) {
        return new LD(kRegToReg, kRegA, kRegH);
    }
    if (value == 0x69) {
        return new LD(kRegToReg, kRegC, kRegL);
    }
    if (value == 0x6E) {
        return new LD(kHLToReg, kRegL);

    }
    if (value == 0x6F) {
        return new LD(kRegToReg, kRegA, kRegL);
    }
    if (value == 0x70) {
        return new LD(kRegToHL, kRegB);
    }
    if (value == 0x71) {
        return new LD(kRegToHL, kRegC);
    }
    if (value == 0x72) {
        return new LD(kRegToHL, kRegD);
    }
    if (value == 0x73) {
        return new LD(kRegToHL, kRegE);
    }
    if (value == 0x74) {
        return new LD(kRegToHL, kRegH);
    }
    if (value == 0x75) {
        return new LD(kRegToHL, kRegL);
    }
    if (value == 0x77) {
        return new LD(kRegToHL, kRegA);
    }
    if (value == 0x78) {
        return new LD(kRegToReg, kRegB, kRegA);
    }
    if (value == 0x7A) {
        return new LD(kRegToReg, kRegD, kRegA);
    }
    if (value == 0x7C) {
        return new LD(kRegToReg, kRegH, kRegA);
    }
    if (value == 0x7D) {
        return new LD(kRegToReg, kRegL, kRegA);
    }
    if (value == 0x80) {
        return new ADD(kRegB);
    }
    if (value == 0x8D) {
        return new ADC(kRegL);
    }
    if (value == 0xA9) {
        return new XOR(kRegC);
    }
    if (value == 0xAF) {
        return new XOR(kRegA);
    }
    if (value == 0xB0) {
        return new OR(kRegB);
    }
    if (value == 0xB1) {
        return new OR(kRegC);
    }
    if (value == 0xC0) {

        return new RET(kFlagZ, kRETCondNot);
    }
    if (value == 0xC1) {
        return new POP(kRegBC);
    }
    if (value == 0xc3) {
        return new JP(read_16(address + 1));
    }
    if (value == 0xC5) {
        return new PUSH(kRegBC);
    }
    if (value == 0xC6) {
        return new ADD(read_8(address + 1));
    }
    if (value == 0xC8) {
        return new RET(kFlagZ, kRETCondNormal);
    }
    if (value == 0xC9) {
        return new RET();
    }
    if (value == 0xCB) {
        return disassemble_prefix(address);
    }
    if (value == 0xCD) {
        printf("got call at address 0x%lx\n", address);
        return new CALL(read_16(address + 1), counter + 3);
    }
    if (value == 0xCE) {
        return new ADC(read_8(address + 1));
    }

    if (value == 0xCF) {
        return new CALL(0x08, counter + 1);
    }
    if (value == 0xD0) {
        return new RET(kFlagC, kRETCondNot);
    }
    if (value == 0xD1) {
        return new POP(kRegDE);
    }
    if (value == 0xD5) {
        return new PUSH(kRegDE);
    }
    if (value == 0xD6) {
        return new SUB(read_8(address + 1));
    }
    if (value == 0xE0) {
        return new LDH(kLDHAToAddress, read_8(address + 1));
    }
    if (value == 0xE1) {
        return new POP(kRegHL);
    }
    if (value == 0xE5) {
        return new PUSH(kRegHL);
    }
    if (value == 0xE6) {
        return new AND(read_8(address + 1));
    }
    if (value == 0xE9) {
        return new JP();
    }
    if (value == 0xEA) {
        return new LD(kAToA16, read_16(address + 1));
    }
    if (value == 0xEF) {
        return new CALL(0x28, counter + 1);
    }
    if (value == 0xF0) {
        return new LDH(kLDHAddressToA, read_8(address + 1));
    }
    if (value == 0xF1) {
        return new POP(kRegAF);
    }
    if (value == 0xF3) {
        return new DI();
    }
    if (value == 0xF5) {
        return new PUSH(kRegAF);
    }
    if (value == 0xF7) {
        return new CALL(0x30, counter + 1);
    }
    if (value == 0xFA) {
        return new LD(kA16ToA, read_16(address + 1));
    }
    if (value == 0xFE) {
        return new CP(read_8(address + 1));
    }
    if (value == 0xFF) {
        return new CALL(0x38, counter + 1);
    }
    exit_with_error("Could not decode instruction");

    return NULL;
}
