#include "../Instruction.h"

int NOP::execute(CPU *cpu) {
    cpu->increasePC(1);
    return 1;

}

NOP::NOP() {
    this->text_string = "NOP";
    this->cycles = 1;
}
