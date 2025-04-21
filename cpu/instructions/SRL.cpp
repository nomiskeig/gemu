
#include "../Instruction.h"
#include <ios>
#include <sstream>

void SRL::execute(CPU *cpu) {
    cpu->increasePC(2);
    cpu->clearAllFlags();
    if (cpu->get_reg_8(this->reg) & 0x1) {
        cpu->set_flag(kFlagC);
    }
    cpu->set_Reg8(this->reg, cpu->get_reg_8(this->reg) >> 0x1);
    if (cpu->get_reg_8(this->reg) == 0x0) {
        cpu->set_flag(kFlagZ);
    }
}

SRL::SRL(Reg8 reg) {
    this->reg = reg;
    auto stream = std::stringstream();
    stream << "SRL " << std::hex << reg8_to_str(this->reg);
    this->text_string = stream.str();
}
