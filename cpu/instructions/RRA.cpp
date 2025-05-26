#include "../Instruction.h"
#include <ios>
#include <sstream>

int RRA::execute(CPU *cpu) {
    cpu->increasePC(1);
    N8 temp = cpu->get_flag(kFlagC);
    cpu->clearAllFlags();
    if (cpu->get_reg_8(kRegA) & 0x1) {
        cpu->set_flag(kFlagC);
    }
    cpu->set_Reg8(kRegA, (cpu->get_reg_8(kRegA) >> 0x1) | temp << 0x7);
    return 2;
}

RRA::RRA() {
    auto stream = std::stringstream();
    stream << "RRA " ;
    this->text_string = stream.str();
}
