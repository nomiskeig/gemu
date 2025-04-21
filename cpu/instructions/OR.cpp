#include "../Instruction.h"

void OR::execute(CPU *cpu) {
    switch (this->action) {
    case kORAReg: {
            printf("got value of A: 0x%x and value of reg: 0x%x", cpu->get_reg_8(kRegA), cpu->get_reg_8(this->reg));
        cpu->set_Reg8(kRegA, cpu->get_reg_8(kRegA) | cpu->get_reg_8(this->reg));
        cpu->clearAllFlags();
        if (cpu->get_reg_8(kRegA) == 0x0) {
            cpu->set_flag(kFlagZ);
        }
        cpu->increasePC(1);
        break;
    }

    default:
        exit_with_error("OR action not implemented");
    }
}


OR::OR(Reg8 reg) {
    this->reg = reg;
    this->text_string=  "OR";
    this->action = kORAReg;
}
