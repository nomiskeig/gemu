#include "../Instruction.h"

void LD::execute(CPU *cpu) {
    cpu->increasePC(2);
    switch (this->action) {
    case kN8ToR8: {
        cpu->set_Reg8(this->reg8, this->valN8);
        break;
    }
    case kAToA16: {
        cpu->write_memory(this->address, cpu->get_reg_8(kRegA));
        break;
    }
    default:
        exit_with_error("Found unsupported LD action");
    }
}

LD::LD(LDAction action, Reg8 reg, N8 value) {
    this->action = action;
    this->text_string = "LD";
    this->reg8 = reg;
    this->valN8 = value;
}

LD::LD(LDAction action, A16 address) {
    this->action = action;
    this->text_string = "LD";
    this->address = address;
};
