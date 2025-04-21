#include "../Instruction.h"

void RLCA::execute(CPU *cpu) {
    cpu->increasePC(1);
    cpu->clearAllFlags();
    int highest = cpu->get_reg_8(kRegA) & 0x80;
    cpu->set_Reg8(kRegA, cpu->get_reg_8(kRegA) << 1 | (highest & 0x1));
    if (highest > 0) {
        cpu->set_flag(kFlagC);
    }

}
