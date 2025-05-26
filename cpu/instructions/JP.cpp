#include "../Instruction.h"
#include <ios>
#include <sstream>

int JP::execute(CPU *cpu) {
    int res = 0;
    switch (this->action) {
    case kJPPC: {
        res = 4;
        cpu->setPC(this->pc);
        break;
    }
    case kJPHL: {
        res = 1;
        cpu->setPC(cpu->get_reg_16(kRegHL));
        break;
    }
    default:
        exit_with_error("JP action not implemented");
    }
    return res;
}

JP::JP(ProgramCounter pc) {
    auto stream = std::stringstream();
    stream << "JP 0x" << std::hex << pc;
    this->text_string = stream.str();
    this->action = kJPPC;
    this->pc = pc;
    this->cycles = 3;
}
JP::JP() { this->action = kJPHL; }
