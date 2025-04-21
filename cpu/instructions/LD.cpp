#include "../Instruction.h"
#include <ios>
#include <sstream>

void LD::execute(CPU *cpu) {
    switch (this->action) {
    case kN8ToR8: {
        cpu->increasePC(2);
        cpu->set_Reg8(this->reg8, this->valN8);
        break;
    }
    case kN16ToR16: {
        cpu->set_reg16(this->reg16, this->valN16);
        cpu->increasePC(3);

        break;
    }
    case kAToA16: {
        cpu->write_memory(this->address, cpu->get_reg_8(kRegA));

        cpu->increasePC(3);
        break;
    }
    case kA16ToA: {
        cpu->set_Reg8(kRegA, cpu->read_memory(this->address));
        cpu->increasePC(3);
        break;
    }
    case kR16AddrToA: {
        cpu->increasePC(1);
        printf("read value %x from address %x\n",
               cpu->read_memory(cpu->get_reg_16(this->reg16)),
               cpu->get_reg_16(this->reg16));
        cpu->set_Reg8(kRegA, cpu->read_memory(cpu->get_reg_16(this->reg16)));
        break;
    }
    case kAToReg16Addr: {
        cpu->increasePC(1);
        cpu->write_memory(cpu->get_reg_16(this->reg16), cpu->get_reg_8(kRegA));
        break;
    }
    case kRegToReg: {
        cpu->increasePC(1);
        printf("got 0x%hhx as the source value\n",
               cpu->get_reg_8(this->source));
        cpu->set_Reg8(this->dest, cpu->get_reg_8(this->source));
        break;
    }
    case kRegToHL: {
        cpu->increasePC(1);
        cpu->write_memory(cpu->get_reg_16(kRegHL), cpu->get_reg_8(this->reg8));
        break;
    }
    case kHLToReg: {
        cpu->increasePC(1);
        cpu->set_Reg8(this->reg8, cpu->read_memory(cpu->get_reg_16(kRegHL)));
        break;
    }
    case kAToHLInc:
        cpu->increasePC(1);
        cpu->write_memory(cpu->get_reg_16(kRegHL), cpu->get_reg_8(kRegA));
        cpu->set_reg16(kRegHL, cpu->get_reg_16(kRegHL) + 1);
        break;
    case kAToHLDec: {
        cpu->increasePC(1);
        cpu->write_memory(cpu->get_reg_16(kRegHL), cpu->get_reg_8(kRegA));
        cpu->set_reg16(kRegHL, cpu->get_reg_16(kRegHL) - 1);
        break;
    }
    case kHLToAInc: {
        cpu->increasePC(1);
        cpu->set_Reg8(kRegA, cpu->read_memory(cpu->get_reg_16(kRegHL)));
        cpu->set_reg16(kRegHL, cpu->get_reg_16(kRegHL) + 1);
        break;
    }

        /*case kAddr16ToA: {
            cpu->increasePC(3);
        }*/

    default:
        exit_with_error("Found unsupported LD action");
    }
}

LD::LD(LDAction action, Reg8 reg, N8 value) {
    this->action = action;
    auto stream = std::stringstream();
    printf("value is 0x%x\n", value);
    this->valN8 = value + 0x0;
    stream << "LD " << reg8_to_str(reg) << ", 0x" << std::hex << value + 0x0;
    this->text_string = stream.str();
    this->reg8 = reg;
}
LD::LD(LDAction action, Reg16 reg, N16 value) {
    this->action = action;
    auto stream = std::stringstream();
    stream << "LD " << reg16_to_str(reg) << ", 0x" << std::hex << value;
    this->text_string = stream.str();
    this->reg16 = reg;
    this->valN16 = value;
}
LD::LD(LDAction action, Reg8 source, Reg8 dest) {
    this->action = action;
    auto stream = std::stringstream();
    stream << "LD " << reg8_to_str(dest) << ", " << std::hex
           << reg8_to_str(source);
    this->text_string = stream.str();
    this->source = source;
    this->dest = dest;
}

LD::LD(LDAction action, A16 address) {
    this->action = action;
    this->text_string = "LD";
    this->address = address;
};

LD::LD(LDAction action, Reg8 reg) {
    this->action = action;
    this->reg8 = reg;
    this->text_string = "LD to HL";
}

LD::LD(LDAction action) {
    this->action = action;
    switch (this->action) {
    case kHLToAInc:
        this->text_string = "LD A, [HL+]";
        break;
    default:
        break;
    }
}
LD::LD(LDAction action, Reg16 reg) {
    this->action = action;
    this->reg16 = reg;
    switch (action) {
    case kAToReg16Addr: {
        auto stream = std::stringstream();
        stream << "LD [" << reg16_to_str(reg) << "], A";
        this->text_string = stream.str();
        break;
    }
    default:
        break;
    }
}
