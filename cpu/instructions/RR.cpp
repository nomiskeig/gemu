#include "../Instruction.h"
#include <ios>
#include <sstream>

int RR::execute(CPU *cpu) {
    cpu->increasePC(2);
    N8 temp = cpu->get_flag(kFlagC);
    cpu->clearAllFlags();
    if (cpu->get_reg_8(this->reg) & 0x1) {
        cpu->set_flag(kFlagC);
    }
    cpu->set_Reg8(this->reg, (cpu->get_reg_8(this->reg) >> 0x1) | temp << 0x7);
    if (cpu->get_reg_8(this->reg) == 0x0) {
        cpu->set_flag(kFlagZ);
    }
    return 2;
}

RR::RR(Reg8 reg) {
    this->reg = reg;
    auto stream = std::stringstream();
    stream << "RR " << std::hex << reg8_to_str(this->reg);
    this->text_string = stream.str();
}
