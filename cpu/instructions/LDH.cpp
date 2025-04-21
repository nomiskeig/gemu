#include "../Instruction.h"
#include <sstream>

void LDH::execute(CPU *cpu) {
    switch (this->action) {

    case kLDHAToAddress: {
        Reg8Val val = cpu->get_reg_8(kRegA);

        cpu->write_memory(0xFF00 + this->address, val);
        cpu->increasePC(2);
        break;
    }
    case kLDHAddressToA: {
        cpu->set_Reg8(kRegA, cpu->read_memory(0xFF + this->address));
            cpu->increasePC(2);
            break;
    }
    default:
        exit_with_error("LDH case not implemented");
    }
}
LDH::LDH(LDHAction action, A8 address) {
    this->address = address;
    this->action = action;
    auto stream = std::stringstream();
    stream << "LDH with address " << std::hex << 0xFF00 + address;
    this->text_string = stream.str();
}
