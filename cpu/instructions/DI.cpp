#include "../Instruction.h"

int DI::execute(CPU *cpu) {
    cpu->disableInterrupts();
    cpu->increasePC(1);
    return 1;

}

DI::DI() {
    this->text_string = "DI";

}
