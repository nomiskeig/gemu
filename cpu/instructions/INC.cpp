#include "../Instruction.h"
#include <ios>
#include <sstream>

int INC::execute(CPU *cpu) {
    int cycles = 0;
    cpu->increasePC(1);
    switch (this->action) {
    case kINCR8:
        cpu->set_Reg8(this->reg8, cpu->get_reg_8(this->reg8) + 1);
        cpu->clear_flag(kFlagN);
        if (cpu->get_reg_8(this->reg8) == 0x0) {
            cpu->set_flag(kFlagZ);
        } else {
            cpu->clear_flag(kFlagZ);
        }
        if ((cpu->get_reg_8(this->reg8) & 0xFF) == 0xFF) {
                cpu->set_flag(kFlagH);

        } else {
                cpu->clear_flag(kFlagH);
            }
        break;

    case kINCR16: {
            printf("setting reg %x to %x", this->reg16, cpu->get_reg_16(this->reg16) +1);
        cpu->set_reg16(this->reg16, cpu->get_reg_16(this->reg16) + 1);
        break;
    }
    default:
        exit_with_error("INC action not implemented");
    }
    return 0;
}

INC::INC(Reg16 reg) {
    this->reg16 = reg;
    this->action = kINCR16;
    this->text_string = "INC r16";
}

INC::INC(Reg8 reg) {
    this->reg8 = reg;
    this->action = kINCR8;
    this->text_string = "INC r8";
    auto stream = std::stringstream();
    stream << "INC " << std::hex << reg8_to_str(this->reg8);
    this->text_string = stream.str();
};
