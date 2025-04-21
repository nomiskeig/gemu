#include "../Instruction.h"

void XOR::execute(CPU *cpu) {
    switch (this->action) {

    case kXORReg: {
        cpu->set_Reg8(kRegA, cpu->get_reg_8(kRegA) ^ cpu->get_reg_8(this->reg));
        cpu->clearAllFlags();
        if (cpu->get_reg_8(kRegA) == 0x0) {
            cpu->set_flag(kFlagZ);
        }
        cpu->increasePC(1);
            break;
    default:
        exit_with_error("XOR action not implemented");
    }
    };
}


XOR::XOR(Reg8 reg) {
    this->reg = reg;
    this->text_string = "XOR";
    this->action = kXORReg;
}
