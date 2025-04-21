#include "../Instruction.h"

void SUB::execute(CPU *cpu) {
    switch (this->action) {
    case kSUBN8ToA: {
        cpu->increasePC(2);
        if (cpu->get_reg_8(kRegA) > this->n8) {
            cpu->set_flag(kFlagC);
        } else {
            cpu->clear_flag(kFlagC);
        }
        if ((cpu->get_reg_8(kRegA) & 0xF) > ((this->n8 & 0xF))) {
            cpu->set_flag(kFlagH);
        } else {
            cpu->clear_flag(kFlagH);
        }
        cpu->set_Reg8(kRegA, cpu->get_reg_8(kRegA) + this->n8);
        cpu->set_flag(kFlagN);
        if (cpu->get_reg_8(kRegA) == 0x0) {
            cpu->set_flag(kFlagZ);
        } else {
            cpu->clear_flag(kFlagZ);
        }
        break;
    }
    default:
        exit_with_error("SUB action not implemented");
    };
}
SUB::SUB(N8 n8) {
    this->n8 = n8;
    this->text_string= "SUB";
    this->action = kSUBN8ToA;

}
