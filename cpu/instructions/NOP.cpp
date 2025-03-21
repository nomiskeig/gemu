#include "../Instruction.h"

void NOP::execute(CPU *cpu) {
    cpu->increasePC(1);

}

NOP::NOP() {
    this->text_string = "NOP";
    this->cycles = 1;
}
