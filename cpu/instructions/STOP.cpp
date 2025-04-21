#include "../Instruction.h"

void STOP::execute(CPU *cpu) {
    cpu->increasePC(2);

}
STOP::STOP(N8 val) {
    this->val = val;
    this->text_string = "STOP";
}
