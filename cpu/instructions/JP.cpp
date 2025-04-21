#include "../Instruction.h"
#include <ios>
#include <sstream>

void JP::execute(CPU *cpu) {
    switch (this->action) {
    case kJPPC: {
        cpu->setPC(this->pc);
        break;
    }
    case kJPHL: {
        cpu->setPC(cpu->get_reg_16(kRegHL));
            break;
    }
    default:
        exit_with_error("JP action not implemented");
    }
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
