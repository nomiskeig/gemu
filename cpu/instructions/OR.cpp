#include "../Instruction.h"

int OR::execute(CPU *cpu) {
    int res = 0;
    switch (this->action) {
    case kORAReg: {
        res = 1;
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
    return res;
}

OR::OR(Reg8 reg) {
    this->reg = reg;
    this->text_string = "OR";
    this->action = kORAReg;
}
