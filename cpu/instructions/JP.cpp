#include "../Instruction.h"

void JP::execute(CPU *cpu) {
    cpu->setPC(this->pc);
}

JP::JP(ProgramCounter pc) {
    this->text_string = "JP";
    this->pc = pc;
    this->cycles = 3;
}
