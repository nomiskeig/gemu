#include "../Instruction.h"

void ADC::execute(CPU *cpu) {
    Reg8Val other;
    switch (this->action) {

    case kADCRegToA: {
        cpu->increasePC(1);
        other = cpu->get_reg_8(this->reg8);
        break;
    }
    case kADCN8ToA: {
        cpu->increasePC(2);
        other = this->n8;
            break;
    }
    default:
        exit_with_error("ADC action not implemented");
    }
    if (cpu->get_reg_8(kRegA) + other + cpu->get_flag(kFlagC) > 0xFF) {
        cpu->set_flag(kFlagC);
    } else {
        cpu->clear_flag(kFlagC);
    }
    if ((cpu->get_reg_8(kRegA) & 0xF) +
            ((other & 0xF) + cpu->get_flag(kFlagZ)) >
        0xF) {
        cpu->set_flag(kFlagH);
    } else {
        cpu->clear_flag(kFlagH);
    }
    cpu->set_Reg8(kRegA, cpu->get_reg_8(kRegA) + other + cpu->get_flag(kFlagC));
    cpu->clear_flag(kFlagN);
    if (cpu->get_reg_8(kRegA) == 0x0) {
        cpu->set_flag(kFlagZ);
    }
}

ADC::ADC(Reg8 reg8) {
    this->reg8 = reg8;
    this->text_string = "ADC";
    this->action = kADCRegToA;
}

ADC::ADC(N8 n8) {
    this->n8 = n8;
    this->text_string = "ADC n8";
    this->action = kADCN8ToA;
}
