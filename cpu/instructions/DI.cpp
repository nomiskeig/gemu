#include "../Instruction.h"

void DI::execute(CPU *cpu) {
    cpu->disableInterrupts();
    cpu->increasePC(1);

}

DI::DI() {
    this->text_string = "DI";

}
