#include "../Instruction.h"

void ADD::execute(CPU *cpu) {
    switch (this->action) {

    case kADDRegToHL: {
        cpu->increasePC(1);
        cpu->set_reg16(kRegHL,
                       cpu->get_reg_16(kRegHL) + cpu->get_reg_16(this->reg16));
        cpu->clear_flag(kFlagN);
        if (cpu->get_reg_16(kRegHL) + cpu->get_reg_16(this->reg16) > 0xFFFF) {
            cpu->set_flag(kFlagC);
        } else {
            cpu->clear_flag(kFlagC);
        }
        if ((cpu->get_reg_16(kRegHL) & 0xFFF) +
                (cpu->get_reg_16(this->reg16) & 0xFFF) >
            0xFFF) {
            cpu->set_flag(kFlagH);
        } else {
            cpu->clear_flag(kFlagH);
        }
        break;
    }
    case kADDRegToA: {
        cpu->increasePC(1);
        cpu->set_Reg8(kRegA,
                      cpu->get_reg_8(kRegA) + cpu->get_reg_8(this->reg8));
        cpu->clear_flag(kFlagN);
        if (cpu->get_reg_8(kRegA) == 0x0) {
            cpu->set_flag(kFlagZ);
        }
        if (cpu->get_reg_16(kRegHL) + cpu->get_reg_16(this->reg16) > 0xFF) {
            cpu->set_flag(kFlagC);
        }
        if ((cpu->get_reg_16(kRegHL) & 0xF) +
                (cpu->get_reg_16(this->reg16) & 0xF) >
            0xF) {
            cpu->set_flag(kFlagH);
        }
        break;
    }
    case kADDN8ToA: {
        cpu->increasePC(2);
        if (cpu->get_reg_8(kRegA) + this->n8 > 0xFF) {
            cpu->set_flag(kFlagC);
        } else {
            cpu->clear_flag(kFlagC);
        }
        if ((cpu->get_reg_8(kRegA) & 0xF) + ((this->n8 & 0xF)) > 0xF) {
            cpu->set_flag(kFlagH);
        } else {
            cpu->clear_flag(kFlagH);
        }
        cpu->set_Reg8(kRegA, cpu->get_reg_8(kRegA) + this->n8);
        cpu->clear_flag(kFlagN);
        if (cpu->get_reg_8(kRegA) == 0x0) {
            cpu->set_flag(kFlagZ);
        }
        break;
    }
    default:
        exit_with_error("ADD action not implemented");
    };
}

ADD::ADD(Reg16 reg) {
    this->reg16 = reg;
    this->text_string = "ADD to HL";
    this->action = kADDRegToHL;
}

ADD::ADD(Reg8 reg) {
    this->reg8 = reg;
    this->text_string = "ADD reg8 to A";
    this->action = kADDRegToA;
}
ADD::ADD(N8 n8) {
    this->n8 = n8;
    this->text_string = "ADD n8 to A";
    this->action = kADDN8ToA;
}
