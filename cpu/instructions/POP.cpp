#include "../Instruction.h"

int POP::execute(CPU *cpu) {

    cpu->increasePC(1);
    Reg16Val val = cpu->read_memory(cpu->get_reg_16(kRegSP)) & 0xFF;
    cpu->modifySP(1);
    val |= cpu->read_memory(cpu->get_reg_16(kRegSP)) << 0x08;
    cpu->modifySP(1);
    cpu->set_reg16(this->reg16, val);
    return 3;
}

POP::POP(Reg16 reg) {
    this->text_string = "POP";
    this->reg16 = reg;
}
