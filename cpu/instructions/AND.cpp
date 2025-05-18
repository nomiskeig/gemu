#include "../Instruction.h"

int AND::execute(CPU *cpu) {
    int cycles = 0;
    switch (this->action) {
    case kANDAN8: {
            cycles = 2;
        cpu->set_Reg8(kRegA, cpu->get_reg_8(kRegA) & this->val);
        cpu->clearAllFlags();
        if (cpu->get_reg_8(kRegA) == 0x0) {
            cpu->set_flag(kFlagZ);
        }
        cpu->set_flag(kFlagH);
        cpu->increasePC(1);
        break;
    }

    default:
        exit_with_error("OR action not implemented");
    }
    return cycles;
}

AND::AND(N8 val) {
    this->val = val;
    this->text_string = "AND";
    this->action = kANDAN8;
}
