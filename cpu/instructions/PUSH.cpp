#include "../Instruction.h"

void PUSH::execute(CPU *cpu) {
    cpu->increasePC(1);
    switch (this->action) {

    case kStackAddress: {
        cpu->modifySP(-1);
        cpu->write_memory(cpu->getSP(), this->address >> 0x8);
        cpu->modifySP(-1);
        cpu->write_memory(cpu->getSP(), this->address & 0xFF);
        break;
    }
    case kStackRegister: {
        cpu->modifySP(-1);
        cpu->write_memory(cpu->getSP(), cpu->get_reg_16(this->reg16) >> 0x8);
        cpu->modifySP(-1);
        cpu->write_memory(cpu->getSP(), cpu->get_reg_16(this->reg16) & 0xFF);
        break;
    }
    default:
        exit_with_error("PUSH case not implemented");
    }
}

PUSH::PUSH(A16 address) {
    this->text_string = "Push address";
    this->address = address;
    this->action = kStackAddress;
}

PUSH::PUSH(Reg16 reg) {
    this->text_string = "Push register";
    this->reg16 = reg;
    this->action = kStackRegister;

}
