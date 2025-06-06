#include "../Instruction.h"
#include <ios>
#include <sstream>

int DEC::execute(CPU *cpu) {
    int cycles = 0;
    cpu->increasePC(1);
    printf("value of DE is %x, reg8: %x\n", cpu->get_reg_16(kRegDE), this->reg8);
    switch (this->action) {
    case kDECR8: {
            cycles = 1;
        cpu->set_Reg8(this->reg8, cpu->get_reg_8(this->reg8) - 1);
        cpu->set_flag(kFlagN);
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
        printf("value of DE is %x\n", cpu->get_reg_16(kRegDE));
        break;
    }
    case kDECR16: {
            cycles = 2;
        cpu->set_reg16(this->reg16, cpu->get_reg_16(this->reg16) - 1);
        break;
    }
    default:
        exit_with_error("INC action not implemented");
    }
    return cycles;
}

DEC::DEC(Reg16 reg) {
    this->reg16 = reg;
    this->action = kDECR16;
    this->text_string = "DEC r16";
}

DEC::DEC(Reg8 reg) {
    this->reg8 = reg;
    this->action = kDECR8;
    auto stream = std::stringstream();
    stream << "DEC " << std::hex << reg8_to_str(this->reg8);
    this->text_string = stream.str();
};
